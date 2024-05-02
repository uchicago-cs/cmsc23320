Project 3 Rubric
----------------

The grading of this project follows a specifications grading approach. If you have not already
done so, make sure to read our `Grading <../syllabus.html#grading>`__ section of
the syllabus for more details.

You will receive two SNU scores for this project:

- **Completeness score**: This score will be determined solely by the result of running
  the automated tests, as these give a measure of how *complete* your implementation
  is (i.e., how much of the assignment you implemented).
- **Code Quality score**: This score is determined by a review of your code done by
  the course staff, and is based on three aspects of your code:

  - *Correctness*: This encompasses issues with your code
    that, while not explicitly captured by the tests, could lead to
    incorrect or inefficient behaviour in your code. This can include
    small mistakes in your code, as well as larger issues that reveal
    a lack of mastery in the material.
  - *Design*: This encompasses
    "qualities, many of which are intangible, that don't have to do with (and exist
    to some extent independently of) the correct operation of your code." (thanks to
    Adam Shaw for this concise phrasing).
  - *Style*: This encompasses your adherence
    to our `Style Guide <https://uchicago-cs.github.io/student-resource-guide/style-guide/c.html>`__.

Submission Timeline
-------------------

The exact timeline of submissions will be the following:

.. include:: project3_timeline.txt

Unlike Projects 1 and 2, the resubmission can only be used to improve your Completeness score
(i.e., the score on the automated tests). Since Project 3 is due by the end of the quarter,
there is not enough to do a full resubmission-regrading cycle.

**NOTE**: To make a resubmission, you must make a "good-faith" submission by the project
deadline. A good-faith submission is any submission where it is clear you have put it
a substantial amount of effort to complete the project. Please note that we will consider
any submission that scores an N in Completeness to meet the bar for a good-faith submission.

This means that, if you want to make a resubmission, you cannot skip the initial
submission, or submit an effectively empty submission. The reason for this is that
such a submission could score an S in Code Quality purely because most of the rubric
items are moot (because there is little/no code to grade). Your resubmission could
then score an S in Completeness, but then have major Code Quality issues.

In practical terms, this means the following:

- If you are scoring an N on the tests in your initial submission, you have nothing to
  worry about. You can make a resubmission to raise your test score to an S.
- If you skip the initial submission, or score a U in the tests, we reserve the right
  to regrade your code for Code Quality in the resubmission.

Completeness
------------

The Completeness component will be determined by running the following commands::

    make tests
    make grade

(see `Automated tests <http://chi.cs.uchicago.edu/chirouter/automated-tests.html>`__
in the chirouter documentation for more details)

**NOTE**: In Project 3, you will be relying on manual testing to a greater extent
than in Projects 1 and 2. The automated tests provide a convenient way to run all
the tests and get a test score but, in general, if your code works when testing it
manually, and fails the corresponding automated test, you should consider the test
to have passed (you should make a note in the README file so the graders are aware
of this)

Your SNU score will then be determined as follows:

+---------------------+----------------------+
| Grade               | Points on tests      |
+=====================+======================+
| Satisfactory        | at least 90          |
+---------------------+----------------------+
| Needs Improvement   | at least 60          |
+---------------------+----------------------+
| Unsatisfactory      | less than 60         |
+---------------------+----------------------+

Code Quality
------------

When assessing your code quality, there are a number of things we will be paying
close attention to, and which we describe in the sections below (including major
issues, labelled "[Major Issue]" that you should be particularly mindful of).

In general, your SNU score will be determined as follows:

- **Satisfactory**: Your submission has a few of the issues described below (but no
  major issues).
- **Needs Improvement**: Your submission has several of the issues described below,
  or at least one major issue. In general, major revisions are typically required to
  get up to an S.
- **Unsatisfactory**: Your submission does not constitute a good-faith effort to complete
  the work. This includes not submitting any work at all, as well as submitting
  only placeholder code (e.g., code that includes functions for all the required
  IRC commands, but where the functions are empty or filled with "TODO"s, etc.)

That said, while the issues listed below are the main things we care about in this project,
it is not possible for us to give you an exhaustive list of every single thing that could
affect your code quality score. If you get a comment pointing out an issue in your
code that we did not list below, take it as an opportunity to improve your work
(and remember that you'll have a chance to revise your work!)

Correctness
-----------

In this project, an incorrect implementation will almost always lead to some of the tests
failing, so there are fewer things that we will be looking at when checking the correctness
of your code. Nonetheless, we will be paying special attention to the following issues
which would not be caught by the tests:

- **Automatically sending an ARP reply for any ARP request, without checking that the requested IP address matches the router interface's IP address**. Because the destination MAC address of ARP requests is set to the broadcast address, you will receive ARP requests that may not be intended for the router. You need to check the IP address in the ARP request itself to determine whether to reply to the ARP request.
- **Sending ARP replies with a broadcast destination address**. ARP replies should be sent only to the host that originally sent the ARP request.
- **ICMP Port Unreachable: Checking for UDP or TCP payloads, but not both**
- **Not checking the ARP cache before deciding whether to send an ARP request**. If there is already a cached entry for a given IP address, there is no need to send an ARP request.
- [Major issue] **Not implementing IP forwarding at all, and instead forwarding all IP datagrams on all ports**
- [Major issue] **Hardcoding any forwarding logic, instead of using the provided routing table**
- **Writing IP forwarding, but processing the routing table incorrectly**
- **Not locking/unlocking the ARP mutex when accessing the ARP cache or the list of pending ARP requests**. Note: our code already locks the ARP mutex before calling the ``chirouter_arp_process_pending_req`` function, and unlocks it after it returns. No locking is necessary inside that function.
- **Managing Pending ARP Requests: Unconditionally creating new pending requests**. If there is already an entry for IP address *X* in the pending ARP request list, and the router receives a new IP datagram with destination *X*, that datagram should be added to the list of withheld frames in the existing pending request. You should not create an entirely new pending request.
- **Removing pending requests from the pending ARP request list, instead of returning ARP_REQ_REMOVE**
- **Removing pending requests from the pending ARP request list before the request has been sent 5 times**
- **Not removing a pending ARP request when an ARP reply is received, or when it has been sent 5 times already**
- **Unconditionally sending a Time Exceeded reply if a forwardeable IP datagram arrives with TTL=1**.  The correct approach is to first determine whether it is a Host Unreachable and, if it is not, then send a Time Exceeded (meaning that forwardeable datagrams with TTL=1 must linger in the withheld frames list so we can determine whether there is actually a host with that IP).

Design
------

When assessing the design of your code, we will be paying special attention
to the following:

- [Major issue] **Putting all your code in chirouter_process_ethernet_frame without dividing it into multiple functions**.
- **Writing a single massive "Process IP datagram" function, without dividing it into multiple functions.**
- **Repeating ICMP message creation logic in multiple places in your code, instead of writing a general-purpose "create an ICMP message" function**

Style
-----

We will be checking your general adherence to
our `Style Guide <https://uchicago-cs.github.io/student-resource-guide/style-guide/c.html>`__
and, while we will not be checking that you follow every minute aspect of our
style guide, we do expect you to follow a *consistent* style that
asymptotically approaches the one specified in our style guide.
That said, there *are* certain aspects we will be paying more
attention to:

- **Documenting functions**: Every function written by you must have
  a `function comment <https://uchicago-cs.github.io/student-resource-guide/style-guide/c.html#function-comments>`__ with a brief description
  of what the function does, and a description of the parameters and the
  return value. Please note that not documenting your functions at all
  (as opposed to doing so inconsistently or not following the style guide)
  is considered a major issue.
- **Consistent indentation**: Your code must follow one of the
  `allowed indentation styles <https://uchicago-cs.github.io/student-resource-guide/style-guide/c.html#indentation>`__ consistently.
- **Clarity**: Your code must be easy to read and understand. This
  is a fairly subjective aspect, but remember that things like using
  variable names without descriptive names or using magic numbers will
  usually make your code harder to read.
- [Major Issue] **Using global variables**, except when defining
  compile-time constants.
- [Major Issue] **Using goto statements**, except in the very limited cases
  described in the style guide.

Other Code Quality Issues
-------------------------

There are a couple of other issues that we care about across all projects:

.. include:: additional_penalties.txt