Project 1 Tips
==============

Before you get started
----------------------

- Make sure you've read through the `Projects - Getting Started <../projects/started.html>`__ page.
- To help you get started, we are providing you with a `trivial solution <https://github.com/uchicago-cs/cmsc23320/blob/master/samples/chirc/project1a-trivial.c>`_
  to Project 1a that will pass nearly half of the tests. While this can be a good starting point,
  please note that you will still have to make major modifications to that solution
  (in particular, your solution cannot manually create the socket; you must
  use ``getaddrinfo`` instead).
- When writing the socket code for your chirc server, make sure you take a look at the 
  `socket samples <https://github.com/uchicago-cs/cmsc23320/tree/master/samples/sockets>`_ covered
  in the pre-recorded lecture on socket programming. They can provide a good starting point for writing a multi-threaded
  server in Project 1b.

General Tips
------------

-  *Don’t be intimidated by the length of the project specification*.
   The main reason the specification is long is to carve out
   exactly what part of the IRC specification you have to focus on. You
   will actually be implementing a fairly small subset of the IRC
   specification.

-  Your implementation will require using data structures to store
   collections of users, channels, etc. Do not implement these
   data structures from scratch! (in fact, you will be penalized if you do)
   You should use existing data structure
   implementations; we suggest you specifically
   use libraries like `utlist <https://troydhanson.github.io/uthash/utlist.html>`_
   and `uthash <https://troydhanson.github.io/uthash/>`_.
   
-  Working with strings (specially parsing and tokenizing them) in C can be
   a pain. Using a library like `SDS <https://github.com/antirez/sds>`_
   can ease that pain.

-  As you read the project specification and the IRC specification
   itself, you’ll notice that the same patterns come up over and over.
   In a sense, your server is just a piece of software that transforms
   IRC messages into other IRC messages (altering the state of the
   server in the process). So, before you start tackling individual
   tests, we suggest you read through the whole document and design your
   server in such a way that it is easy for you to (1) parse incoming
   messages, (2) add support for new messages, (3) manipulate the state
   of the server (e.g., “create a new channel”, “add a new user to this
   channel”, etc.), and (4) construct outgoing messages. Doing so can
   pay off handsomely later on, even if you spend the first few days
   feeling like you’re not making any progress towards passing any tests.
   
-  When processing multiple commands (starting in Project 1b), a data 
   structure that can come in handy is a `dispatch table <http://en.wikipedia.org/wiki/Dispatch_table>`_ 
   or `branch table <http://en.wikipedia.org/wiki/Branch_table>`_. You can find some 
   sample code `here <https://github.com/uchicago-cs/cmsc23320/tree/master/samples/dispatch_table>`_.

Resolving IRC Ambiguities
-------------------------

The IRC protocol is, in some cases, not as well-specified and clear as one would hope (this is,
unfortunately, a common attribute of many network specifications). If you’re unclear about how your server is meant to behave in some cases (specially the more obscure corner cases of IRC, or the points where the IRC specification is ambiguous), you should take the following steps:

#. Check whether it makes any of our tests fail. If it doesn't, your interpretation of the IRC protocol is probably fine. This includes the lack of features: if you're not implementing some feature/command/reply/corner case/etc. and it isn't covered by our tests, then you probably don't need to implement it. The only exception is cases that are explicitly specified in the chirc specification (there are a few that are not covered by our tests).

#. Take into account that there are literally hundreds of production IRC servers on the Internet that you can log into to test how they’ve interpreted the IRC specification. We suggest using Freenode servers, which you can log into simply by running::

    telnet irc.freenode.net 6667 

   In general, if you replicate the behaviour of a production IRC server, that's good enough for us.

#. You can also test the command on our reference implementation::

    telnet frost.cs.uchicago.edu 6666 
    
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

Common Issues in Project 1a
---------------------------

``strtok``
----------

A common approach to tokenizing IRC commands is to use the standard ``strtok`` function. This is a good approach, but you should take into account that ``strtok`` is not thread-safe and will be the source of inexplicable bugs and race conditions once you start supporting multiple clients. You should use ``strtok_r`` instead (the reentrant version of ``strtok``).

Additionally, a common pitfall when using ``strtok`` is to (incorrectly) assume that ``strtok`` returns a fresh new string with each call. That is not the case. Given a string like this::

    USER user * * :User\0
    
Successive calls to strtok will transform the string in place into this::

    USER\0user\0*\0*\0:User\0
    
What strtok returns is pointers into that transformed string, not fresh new strings. That means that if you overwrite the original string (e.g., if you wipe out a buffer), the tokens will also be wiped out. Depending on how you've written your solution, you may need to ``strdup`` the tokens.

For more details, please read the ``strtok`` man page, which explains ``strtok``'s internal behavior in detail.

Error handling in sockets
~~~~~~~~~~~~~~~~~~~~~~~~~

Don't forget to check the return value of the socket functions: your code is likely to behave strangely if you don't react appropriately to certain error conditions (e.g., a return code of 0 from recv means that the client has disconnected; in Project 1b you will need to "log out" the user from the IRC server when that happens).

General socket confusion
~~~~~~~~~~~~~~~~~~~~~~~~

If you're confused about how to use sockets, we recommend you read `Beej's Guide to Network Programming <http://beej.us/guide/bgnet/>`_ for a more thorough review of sockets.


Common Issues in Project 1b
---------------------------

Poor code organization
~~~~~~~~~~~~~~~~~~~~~~

In project 1b, your server starts getting more complex. Do not cram all your code into
a single main.c file: you should think about separating your C code into multiple C files, each responsible for a specific part of the program.

Inadequate locking
~~~~~~~~~~~~~~~~~~

In project 1b, you now have multiple clients connecting to your server, with one thread
per client. So remember: shared data structures have to be protected by locks, and this includes 
any socket that multiple threads could write to. POSIX requires system calls to be thread-safe (i.e., the OS itself should guarantee that send() is done atomically). However, even though a call to send() can be thread-safe, you have to account for the fact that send() might not send all your data in one go. So, you still need to gain exclusive access to the socket until a full message has been sent; otherwise, you could see partial messages interleaved by multiple threads.


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

``strcat`` vs ``sprintf``
~~~~~~~~~~~~~~~~~~~~~~~~~

In some languages, creating a new string from multiple other substrings is as easy as doing this::

    s = ""
    s += "USER "
    s += username
    s += " * * "
    s += ":" + user_fullname

Some students tend to translate this pattern directly into C by using the ``strcat`` function
(creating messages and replies by making successive calls to strcat, starting from an empty string).
Resist the urge to do this: this is very hard to read, and will not scale well once you have to
build more complex messages.

Consider using ``sprintf`` instead to create messages and replies.
