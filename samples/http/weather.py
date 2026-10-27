#!/usr/bin/env python3
"""
weather.py - Print the weather forecast for a location in the terminal.

This program is a small example of a client for two REST APIs. It asks the
user for a location (e.g., "Hyde Park, Chicago"), and then:

  1. Uses the Nominatim API (OpenStreetMap's geocoding service) to convert
     that location name into a latitude and longitude.
       https://nominatim.org/release-docs/latest/api/Search/

  2. Uses the National Weather Service (NWS) API at api.weather.gov to find
     the forecast "grid" that covers that latitude and longitude.
       https://www.weather.gov/documentation/services-web-api

  3. Uses the NWS API again to get the forecast for that grid, and prints it.

Every interaction with a REST API is an HTTP request on a *resource*
identified by a URI, and every result comes back as an HTTP response whose
body contains a *representation* of that resource (here, always JSON). The
places in the code where this happens are marked with comments that start
with "REST:".

We use the requests library (https://requests.readthedocs.io/) to send the
HTTP requests ourselves, instead of a library that wraps the weather API, so
that every request and response is visible in the code.

To run it:

    pip install requests
    python3 weather.py

By default, it just prints the forecast. Two flags make it print more:

    python3 weather.py -v     # also print what each step found
    python3 weather.py -vv    # ...and every HTTP request and response, in full

It needs Python 3.10 or later (for the "X | None" type annotations).

The NWS only provides forecasts for the United States and its territories,
so locations elsewhere will not have a forecast.

Note: This sample program was generated with assistance from Claude Opus 5.5
"""

import argparse
import sys
import urllib.parse
from typing import Any

import requests


# The JSON in API responses is parsed into nested Python dictionaries and
# lists, whose values can be of any type, so we describe a parsed JSON
# object with this type alias.
JSONObject = dict[str, Any]


# Both APIs ask clients to identify themselves with the User-Agent header,
# which is part of every HTTP request. Nominatim's usage policy requires a
# User-Agent that identifies the application (requests sent with a generic
# one may be blocked), and the NWS asks for one that includes a way to
# contact the developer. If you adapt this program, change it to describe
# your own application.
USER_AGENT = "cmsc23320-weather-example (https://uchicago-cs.github.io/cmsc23320/)"

# The base URIs of the two APIs. Each API exposes many resources, all of
# them identified by URIs that start with these.
NOMINATIM_API = "https://nominatim.openstreetmap.org"
NWS_API = "https://api.weather.gov"

# How long (in seconds) to wait for a server to respond before giving up.
TIMEOUT = 5

# How much to print. This is set from the command line in main(): 0 prints
# just the forecast, 1 (-v) also prints what each step found, and 2 (-vv)
# also prints every HTTP request and response in full.
verbosity: int = 0


def http_get(url: str,
             params: dict[str, str | int] | None = None,
             headers: dict[str, str] | None = None) -> requests.Response:
    """
    Sends an HTTP GET request and returns the HTTP response.

    This is a thin wrapper around requests.get(), so every call to it is one
    request/response exchange with an API. The only thing it adds is that,
    with the -vv flag, it prints the full request and response.

    Parameters:
        url (str): The URI of the resource
        params (dict): Query parameters to add to the URI (optional)
        headers (dict): HTTP headers to include in the request (optional)

    Returns:
        A requests.Response object
    """
    response = requests.get(url, params=params, headers=headers,
                            timeout=TIMEOUT)

    if verbosity >= 2:
        # If the server had replied with a redirect (a 3xx status code),
        # requests would have followed it automatically, sending a second
        # request. The responses that led to the final one are kept in
        # response.history, so we print those exchanges too.
        for r in response.history + [response]:
            print_http_exchange(r)

    return response


def print_http_exchange(response: requests.Response) -> None:
    """
    Prints an HTTP request and its response, as they would look on the wire
    in HTTP/1.1 (the version requests uses).

    Parameters:
        response (requests.Response): The response; the request that
          produced it is in response.request

    Returns: nothing
    """
    request = response.request

    # The type annotations in requests allow a request's URL to be None, but
    # that only happens for a request that hasn't been prepared to be sent.
    # A request that got a response always has one.
    assert request.url is not None
    url = urllib.parse.urlsplit(request.url)

    # The request line: method, target (path plus query string), version
    target = url.path
    if url.query:
        target += "?" + url.query
    print(">>>>>>>>>> HTTP request")
    print(f"{request.method} {target} HTTP/1.1")

    # The Host header is added by urllib3 (the lower-level library requests
    # uses to send requests), so it is not in request.headers, but it is
    # sent, and it is mandatory in HTTP/1.1. Notice how requests also adds
    # headers of its own, like Accept-Encoding.
    print(f"Host: {url.netloc}")
    for name, value in request.headers.items():
        print(f"{name}: {value}")
    print()

    # A GET request has no body, but other methods (like POST) would.
    if request.body:
        print(request.body)

    # The status line: version, status code, reason phrase
    print("<<<<<<<<<< HTTP response")
    print(f"HTTP/1.1 {response.status_code} {response.reason}")
    for name, value in response.headers.items():
        print(f"{name}: {value}")
    print()

    # If the response has a "Content-Encoding: gzip" header, the body was
    # sent compressed. requests decompresses it for us, so what we print
    # here is the body after decompression.
    print(response.text)
    print()


def geocode(location: str) -> tuple[float, float, str, str] | None:
    """
    Converts a location name into coordinates, using the Nominatim API.

    Parameters:
        location (str): A place name, like "Hyde Park, Chicago" or "Boston"

    Returns:
        A (latitude, longitude, short_name, full_name) tuple describing the
        place Nominatim found (see short_place_name() for short_name), or
        None if no place matches.
    """

    # REST: The resource we want is the result of a *search*. In Nominatim,
    # the search resource is identified by the URI /search, and the search
    # itself is described with query parameters, which requests appends to
    # the URI for us. For example, if location is "Hyde Park, Chicago",
    # the full URI will be:
    #
    #   https://nominatim.openstreetmap.org/search?q=Hyde+Park%2C+Chicago
    #             &format=jsonv2&limit=1&countrycodes=us&addressdetails=1
    #
    #   - q: the text to search for
    #   - format: which representation of the results we want (JSON)
    #   - limit: we only want the best match
    #   - countrycodes: restrict the search to the US, since the NWS only
    #     covers the US
    #   - addressdetails: also include the place's address, broken down
    #     into parts (city, state, etc.)
    params: dict[str, str | int] = {
        "q": location,
        "format": "jsonv2",
        "limit": 1,
        "countrycodes": "us",
        "addressdetails": 1,
    }

    # REST: We send a GET request, since we only want to *retrieve* a
    # representation of the resource (GET never modifies anything on the
    # server). The User-Agent header goes along with the request.
    response = http_get(f"{NOMINATIM_API}/search",
                        params=params,
                        headers={"User-Agent": USER_AGENT})

    # REST: The status code in the HTTP response tells us whether the request
    # succeeded. raise_for_status() raises an exception for any error code
    # (4xx client errors, 5xx server errors), and does nothing for 200 OK.
    response.raise_for_status()

    # REST: The body of the response is the representation of the resource:
    # a JSON list of matching places. response.json() parses it into Python
    # lists and dictionaries. Each place looks something like this (trimmed):
    #
    #   {"lat": "41.7944464", "lon": "-87.5939244", "name": "Hyde Park",
    #    "display_name": "Hyde Park, Chicago, ..., United States",
    #    "address": {"suburb": "Hyde Park", "city": "Chicago",
    #                "state": "Illinois", ...}, ...}
    #
    # Notice how the coordinates are sent as strings, not numbers.
    places: list[JSONObject] = response.json()

    if len(places) == 0:
        return None

    place = places[0]
    return (float(place["lat"]), float(place["lon"]),
            short_place_name(place), place["display_name"])


def short_place_name(place: JSONObject) -> str:
    """
    Builds a short name for a place found by Nominatim, like "Hyde Park,
    Chicago, Illinois", from the place's own name, its city (or town, or
    village), and its state.

    Nominatim's display_name is much longer ("Hyde Park, Chicago, Hyde Park
    Township, Cook County, Illinois, 60615, United States"), and not every
    place has a city in its address, so we pick out the parts we want and
    skip any that are missing or that repeat the place's own name.

    Parameters:
        place (JSONObject): A place, as returned by Nominatim's /search with
          addressdetails=1

    Returns:
        The short name
    """
    address: JSONObject = place.get("address", {})

    # Some places, like street addresses, have no name of their own, so we
    # fall back on the first part of the display name.
    name: str = place.get("name") or place["display_name"].split(",")[0]
    city: str | None = (address.get("city") or address.get("town")
                        or address.get("village"))
    state: str | None = address.get("state")

    parts = [name]
    for part in (city, state):
        if part is not None and part not in parts:
            parts.append(part)
    return ", ".join(parts)


def get_forecast_url(latitude: float,
                     longitude: float) -> tuple[str, str, str] | None:
    """
    Finds the URI of the forecast for a latitude and longitude, using the
    /points resource of the NWS API.

    The NWS does not produce forecasts for arbitrary coordinates. Instead,
    each NWS forecast office (e.g., LOT, the Chicago office) divides its area
    into a grid of 2.5km squares, and produces a forecast for each square.
    So, before we can get a forecast, we have to ask which office and grid
    square cover our coordinates.

    Parameters:
        latitude, longitude (float): The coordinates of the location

    Returns:
        A (forecast_url, city, state) tuple, where city and state describe
        the nearest city the NWS knows about, or None if the NWS has no
        forecast for these coordinates (e.g., because they are outside the
        US).
    """

    # REST: Here, the coordinates are part of the URI path itself:
    #
    #   https://api.weather.gov/points/41.7944,-87.5939
    #
    # In other words, every point on the map is its own resource. The NWS
    # only accepts up to four decimal places (about 10 meters). If we sent
    # more, it would respond with a "301 Moved Permanently" redirect to the
    # rounded URI, which requests would follow automatically (see http_get),
    # but rounding ourselves saves a round trip.
    url = f"{NWS_API}/points/{latitude:.4f},{longitude:.4f}"

    # REST: The Accept header tells the server which representation we
    # would like. The NWS API can return several formats; GeoJSON (a JSON
    # format for geographic data) is its default.
    response = http_get(url,
                        headers={"User-Agent": USER_AGENT,
                                 "Accept": "application/geo+json"})

    # REST: For a point the NWS does not cover, the server responds with
    # "404 Not Found": that resource does not exist. Unlike other errors,
    # this is an answer we expect, so we check for it before calling
    # raise_for_status().
    if response.status_code == 404:
        return None

    response.raise_for_status()

    # REST: The representation of a point includes the forecast office and
    # grid square that cover it ("gridId", "gridX" and "gridY") but, more
    # usefully, it also includes the URIs of related resources, such as the
    # point's forecast:
    #
    #   "forecast": "https://api.weather.gov/gridpoints/LOT/77,69/forecast"
    #
    # So, instead of building the forecast URI ourselves, we just follow the
    # link the server gave us. This is a common pattern in REST APIs: the
    # server tells the client where to go next, so the client doesn't need
    # to know how the server organizes its URIs.
    properties: JSONObject = response.json()["properties"]

    location: JSONObject = properties["relativeLocation"]["properties"]
    return properties["forecast"], location["city"], location["state"]


def get_forecast(forecast_url: str) -> list[JSONObject]:
    """
    Gets the forecast from a forecast URI returned by get_forecast_url().

    Parameters:
        forecast_url (str): The URI of a forecast resource

    Returns:
        A list of dictionaries, one per forecast period ("Tonight",
        "Wednesday", "Wednesday Night", etc.), covering about a week.
    """

    # REST: Another GET request, this time on the forecast resource, e.g.:
    #
    #   https://api.weather.gov/gridpoints/LOT/77,69/forecast
    #
    # This resource is never a static file: every time we GET it, the server
    # returns its current representation, so the same URI will give us a
    # different forecast tomorrow.
    response = http_get(forecast_url,
                        headers={"User-Agent": USER_AGENT,
                                 "Accept": "application/geo+json"})
    response.raise_for_status()

    # REST: The forecast is a list of "periods", each of which looks
    # something like this (trimmed):
    #
    #   {"name": "Today", "temperature": 66, "temperatureUnit": "F",
    #    "windSpeed": "5 to 10 mph", "windDirection": "SE",
    #    "shortForecast": "Mostly Cloudy",
    #    "detailedForecast": "Mostly cloudy. High near 66, ...", ...}
    periods: list[JSONObject] = response.json()["properties"]["periods"]
    return periods


def print_forecast(periods: list[JSONObject]) -> None:
    """
    Prints a forecast in the terminal, one line per period.

    Parameters:
        periods (list): The forecast periods returned by get_forecast()

    Returns: nothing
    """

    # This function doesn't interact with any API: by this point, the
    # forecast is just Python data.
    for period in periods:
        temperature = f"{period['temperature']}°{period['temperatureUnit']}"
        wind = f"wind {period['windDirection']} {period['windSpeed']}"
        print(f"{period['name']:>18}: {temperature:>5}  "
              f"{period['shortForecast']} ({wind})")


def main() -> None:
    global verbosity

    parser = argparse.ArgumentParser(
        description="Print the weather forecast for a location in the US.")
    parser.add_argument("-v", "--verbose", action="count", default=0,
                        help="print what each step found (-v), and also "
                             "every HTTP request and response (-vv)")
    args = parser.parse_args()
    verbosity = args.verbose

    location = input("Enter a location in the US: ")
    location = location.strip()
    if location == "":
        print("No location entered.")
        sys.exit(1)

    if verbosity >= 1:
        print()

    # Any of the requests below can fail without reaching a server at all
    # (e.g., if we're offline, or the server takes too long to answer), or
    # get an error status code back. requests reports all of these as
    # exceptions derived from requests.RequestException.
    try:
        # Step 1: location name -> coordinates (Nominatim)
        place = geocode(location)
        if place is None:
            print(f"Could not find a location in the US matching '{location}'.")
            sys.exit(1)
        latitude, longitude, short_name, full_name = place
        if verbosity >= 1:
            print(f"Found: {full_name}")
            print(f"Coordinates: {latitude:.4f}, {longitude:.4f}")

        # Step 2: coordinates -> forecast URI (NWS /points)
        point = get_forecast_url(latitude, longitude)
        if point is None:
            print("The National Weather Service has no forecast for this "
                  "location.")
            sys.exit(1)
        forecast_url, city, state = point
        if verbosity >= 1:
            print(f"Forecast from: {forecast_url}")
            print(f"(nearest NWS location: {city}, {state})")

        # Step 3: forecast URI -> forecast (NWS /gridpoints/.../forecast)
        periods = get_forecast(forecast_url)
        print()
        print(f"Forecast for {short_name}:")
        print()
        print_forecast(periods)

    except requests.RequestException as e:
        print(f"Error while contacting the API: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
