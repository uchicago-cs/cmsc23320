Project 1 Tips
==============

.. warning::
   This page has not yet been updated for Autumn 2024.

Before you get started
----------------------

When writing the socket code for your chirc server, make sure you take a look at the
`socket samples <https://github.com/uchicago-cs/cmsc23320/tree/master/samples/sockets>`_ covered
in the lecture on socket programming. They can provide a good starting point for writing a multi-threaded
server (note: you won't have to write a multi-threaded server for Assignment 1 of chirc)

Make sure you also read through the chirc project documentation, but
*don’t be intimidated by the length of the project specification*.
The main reason the specification is long is to carve out
exactly what part of the IRC specification you have to focus on. You
will actually be implementing a fairly small subset of the IRC
specification.

You should also take a moment to look through the provided starter
code. We suggest starting at the ``main.c`` file, and then gaining
some familiarity with the data structures specified in ``chirc.h``.
We suggest focusing on the server context (``chirc_ctx_t``), the
connections (``chirc_connection_t``), the users (``chirc_user_t``) and the messages
(``chirc_message_t``) since those will be the most relevant at the
start of the project. You should also look at the functions provided
for those data structures (in ``ctx.h``, ``connection.h``, ``user.h``, and ``message.h``).

Next, the chirc server uses the following libraries:

- The `uthash <https://troydhanson.github.io/uthash/>`__ library
  for hash tables. The chirc code is written to abstract away most uses of that library
  (e.g., to add a new connection to the server context, you would use
  the ``chirc_ctx_add_connection`` function instead of manipulating
  the hash table yourself).
   
- The `SDS <https://github.com/antirez/sds>`__  library to manipulate strings.
  SDS strings can be manipulated (i.e., C string functions will
  work with SDS strings), but the SDS library provides functions
  that makes certain tasks easier. That said, you should not need
  to do much string manipulation, since most of that is handled
  by the provided code.

Project 1 Warm-up
-----------------

For the warm-up exercise, we suggest you do the following:

- Update ``chirc_run`` in ``main.c`` to create a passive socket and listen for new connections.
- When a connection is accepted, initialize a ``chirc_connection_t`` struct. This includes creating
  a ``chirc_user_t`` struct to place in the ``peer.user`` field of the ``chirc_connection_t`` struct.
- When a message arrives through the connection, use the functions in ``message.h`` to parse the message.
- Once a ``NICK`` and ``USER`` message have arrived, send a ``001`` reply (once again using functions in ``message.h`` to create the reply).

While you can implement all this inside ``chirc_run``, it will also pay off to do the following:

- Implement the ``chirc_connection_send_message`` function in ``connection.c``. This function
  will provide an abstraction over "sending a message through a connection".ç
- Start looking at the ``handlers.c`` module. Once you have a basic implementation
  in ``chirc_run``, you should look into implementing a ``NICK`` and ``USER`` handler
  in the ``handlers.c`` module.

Resolving IRC Ambiguities
-------------------------

The IRC protocol is, in some cases, not as well-specified and clear as one would hope (this is,
unfortunately, a common attribute of many network specifications). If you’re unclear about how your server is meant to behave in some cases (specially the more obscure corner cases of IRC, or the points where the IRC specification is ambiguous), you should take the following steps:

#. Check whether it makes any of our tests fail. If it doesn't, your interpretation of the IRC protocol is probably fine. This includes the lack of features: if you're not implementing some feature/command/reply/corner case/etc. and it isn't covered by our tests, then you probably don't need to implement it. The only exception is cases that are explicitly specified in the chirc specification (there are a few that are not covered by our tests).

#. Take into account that there are literally hundreds of production IRC servers on the Internet that you can log into to test how they’ve interpreted the IRC specification. We suggest using `Libera.Chat <https://libera.chat/>`__ servers, which you can log into simply by running::

    telnet irc.libera.chat 6667

   In general, if you replicate the behaviour of a production IRC server, that's good enough for us.

#. You can also test the command on our reference implementation::

    telnet frost.cs.uchicago.edu 6666 

Note: if that server is unresponsive, we are also running reference implementations on ports 6661-6665.

Like a production IRC server, if you replicate the behaviour of our reference implementation, that's good enough for us.

..
    Resolving IRC Ambiguities (in IRC networks)
    -------------------------------------------

    In Project 1c, you will not be able to rely on the reference servers, as you would end up getting relay traffic from every other server that successfully connects to a reference server. Instead, we suggest you run a real IRC server to observe how it behaves when it connects to another IRC server. We suggest using `ngIRCd <https://ngircd.barton.de/>`__. Please note that you cannot use pre-built binaries because they will compress messages between servers, making it harder to sniff the traffic. Instead, download the sources for release 25 and build it like this::

        ./configure --without-zlib --enable-strict-rfc --disable-ircplus
        make

    The `ngircd` binary will be located in the `src/ngircd/` directory.

    We will be running two servers, so we need two separate configuration files. Take the `sample configuration file <https://github.com/ngircd/ngircd/blob/master/doc/sample-ngircd.conf.tmpl>`__ and set the following options::

        [Global]
            AdminEMail = admin@irc.server
            MotdPhrase = "Hello world!"
            Network = chircnet

        [Options]
            DNS = no
            Ident = no
            PAM = no

        [Operator]
            Name = IRCop
            Password = thepassword


    Now, create two copies of this file (`server1.conf` and `server2.conf`). In the first one, set these options::

        [Global]
            Name = irc-1.example.net
            Ports = 6667
            Network = chircnet

        [Server]
            Name = irc-2.example.net
            MyPassword = pass1
            PeerPassword = pass2
            Passive = yes

    And in the second one::

        [Global]
            Name = irc-2.example.net
            Ports = 6668
            Network = chircnet

        [Server]
            Name = irc-1.example.net
            Host = 127.0.0.1
            Port = 6667
            MyPassword = pass2
            PeerPassword = pass1
            Passive = yes

    Note that the second server is the one that will be connecting to the first server.

    Now, run the servers on separate terminals like this::

        ngircd -f server1.conf -n
        ngircd -f server2.conf -n

    To capture the traffic between both servers, run Wireshark with the following display filter::

        tcp.port in {6667 6668}

    Connect to the second server with telnet or with an IRC client. To make the second server connect to the first one, send this command::

        CONNECT irc-1.example.net

    You can also connect to the first server via telnet and send the ``PASS`` and ``SERVER`` commands to observe the replies from the server.

Common Issues in chirc Assignment 1
-----------------------------------

Error handling in sockets
~~~~~~~~~~~~~~~~~~~~~~~~~

Don't forget to check the return value of the socket functions: your code is likely to behave strangely if you don't react appropriately to certain error conditions (e.g., a return code of 0 from recv means that the client has disconnected; in chirc Assignment 4 you will need to "log out" the user from the IRC server when that happens).

General socket confusion
~~~~~~~~~~~~~~~~~~~~~~~~

If you're confused about how to use sockets, we recommend you read `Beej's Guide to Network Programming <http://beej.us/guide/bgnet/>`_ for a more thorough review of sockets.


Common Issues in chirc Assignment 4
-----------------------------------

Inadequate locking
~~~~~~~~~~~~~~~~~~

In chirc Assigmnent 4, you now have multiple clients connecting to your server, with one thread
per client. So remember: shared data structures have to be protected by locks, and this includes 
any socket that multiple threads could write to. POSIX requires system calls to be thread-safe (i.e., the OS itself should guarantee that send() is done atomically). However, even though a call to send() can be thread-safe, you have to account for the fact that send() might not send all your data in one go. So, you still need to gain exclusive access to the socket until a full message has been sent; otherwise, you could see partial messages interleaved by multiple threads.

Beej's Guide actually provides a handy `sendall <https://beej.us/guide/bgnet/html/#sendall>`__ function that you can use to ensure that send() sends all the data you want it to send. You would still need to update this `sendall` function to lock/unlock the socket's lock.

Common C Issues
---------------

Bad memory management
~~~~~~~~~~~~~~~~~~~~~

- Make sure that any block of code you malloc() is also free()'d.

- Don't return pointers to stack-allocated variables (i.e., local function variables). Remember:
  stack-allocated variables become invalid after the function returns. Stack-allocated data should
  only be used during the lifetime of a function. So, for example, calling function B from function
  A, and giving B a pointer to a local variable of A is fine. Returning a pointer to a local
  variable of A, on the other hand, is not.

- If you initialize pointers to NULL (e.g., to indicate the absence of something), make sure you
  always check whether that pointer is NULL before using it.

- C has a wonderful function called ``strdup`` that will create a copy of a string and malloc 
  the exact amount of memory needed for it. You should use this function any time you want to make a
  copy of a string. Take into account that using assignment (=) will create a shallow copy, meaning
  that if the original string is modified (or free()'d) it will affect the copy too.

Arbitrary sizes
~~~~~~~~~~~~~~~

Whenever the amount of needed memory is unknown, a common approach is to allocate an arbitrary amount of memory. This is fine, but you should be a little more methodical than just allocating several kilobytes of memory as an arbitrarily large amount. Whenever you allocate an arbitrary amount of memory, you should specify what your assumptions are (e.g., are you assuming that each line of the MOTD file won't have more than X characters?) and, ideally, a note on what conditions would make your program crash given that arbitrary limit.

