Project 2 Tips
==============

.. warning::

   This page has not yet been updated for Spring 2024.

Before you get started, make sure you've read through the `Projects - Getting Started <../projects/started.html>`__ page.

Suggested Order of Implementation
---------------------------------

At first glance, it may seem like Project 2 requires coming up with an effectively complete implementation of TCP before you can test your code. This is a common pitfall in Project 2, that often leads some teams to write huge amounts of code without doing any testing, to then find that nothing is working when they finally start testing their TCP implementation.

So, as you move on to Project 2, we suggest you set the following intermediate goals in Assignment 1 of chiTCP:

- **Pass the Connection Establishment tests**. You can do so by implement the handling of APPLICATION_CONNECT in the CLOSED state (Hint: remember we showed you some basic code for this in the Project 2 lecture), and just enough of the packet arrival handler to implement the three-way handshake (this means you can skip everything related to processing data, FIN segments, etc.). This will ensure you are comfortable with the basics of chiTCP moving forward.
- **Pass some half-duplex tests with <= 536 bytes**. Write a function that processes the send buffer (and sends its contents) and flesh out enough of the packet arrival handler for you to pass some of the simpler tests. This will ensure the basic aspects of data transfer are working, as you do not yet need to worry about segmenting the send buffer (which means you can write your code under the assumption that everything in the send buffer gets sent in a single packet).
- **Move on to half-duplex tests with > 536 bytes**. This will involve segmenting the send buffer correctly.
- **Move on to the echo tests**. A lot of moving pieces have to be working correctly for data to transfer correctly in both directions.
- **Finally, pass the connection termination tests.**

Dividing up the work in Assignment 1 of chiTCP is a bit tricky, since most of your work will involve writing the packet arrival handler (which can't easily be broken down into pieces). We suggest you approach your collaboration on Project 2 as follows:

- **Work together on the threeway handshake**. This will ensure you are both comfortable with the basics of chiTCP before moving on to more complex parts of the project.
- **Be careful about dividing up the packet arrival handler**. You can break it up into sections, but you should agree on a general structure first, and will need to coordinate very carefully as you make progress on it.
- **Avoid giving one person sole responsibility over a core aspect of the code**. For example, don't ask your project partner to write the function that processes the send buffer, and to report back in a few days. If that function doesn't work, it will have a major impact on the rest of your code. It is better to work together on these or, at least, have joint ownership over that code (and make sure it gets done as early as possible)
- **In general, avoid a “there are N functions, let’s split them up” mentality**. A team member can also be responsible for debugging tests, polishing the code, writing documentation, etc.

In Assignment 2 of chiTCP, we suggest you follow this implementation order:

- Start by working together on the multitimer. You will not be able to implement retransmissions or the persist timer without it (you can implement out-of-order delivery without the multitimer, but it's still better if you focus on implementing a solid multitimer first)
- Next, take into account that Retransmissions, the Persist Timer, and Out-of-Order can be implemented in parallel (for the most part, you can pass the tests for each task before you implement the others)

  - That said, implementing retransmissions involves more work than the other two.
  - It can make sense for the two of you to take joint ownership of retransmissions, and have one person work on the persist timer and the other on out-of-order delivery.

- Approach the tests *incrementally*

  - Make sure you're passing all the multitimer tests before you move on to retransmissions or the persist timer. Otherwise, if a retransmission/persist test fails, it will be hard to tell whether the error originates in your retransmission/persist code, or whether its a spurious error that originates in something incorrect in the multitimer.
  - When you move on to retransmissions, there are several simple tests that involve dropping a single packet. Focus on those first, as they will be easier to debug.
  - Then, move onto the connection establishment/termination drop tests.
  - Finally, see if you can pass the tests with multiple drops.
  - Note: You should only attempt to debug the “random” tests if every other test (including from Assignment 1) is working correctly.

Interpreting RFC 793
--------------------

In this project, you will be implementing TCP, which is specified in `RFC 793 <http://tools.ietf.org/html/rfc793>`_.
Like many network protocols, certain aspects of the specification may be unclear. When you run into such an issue,
you should first check `RFC 1122 <http://tools.ietf.org/html/rfc1122>`_: it provides corrections and clarifications 
on RFC 793. If you are still unclear on how to proceed, then ask on Ed Discussion: we will provide an ex cathedra ruling
on how you should interpret the RFC.

That said, there are parts of the RFC that *do* provide unambiguous formulas.
Sometimes, students will tweak this formulas as they try to debug their code
(e.g., using <= instead of <). This may make your code work for the issue you
are trying to resolve, but will probably cause issues down the road.

Finally, it is important that you implement TCP as specified in the RFC, not your
interpretation of TCP (based on class notes and examples online). Replicating the
behaviour of simple examples (like the 3-way handshake) may work for simple
operations, but is not a good strategy for implementing all of TCP.

Selecting Initial Sequence Numbers
----------------------------------

It is your responsibility to generate the initial sequence number (ISN) for a connection,
but you are not required to implement the ISS/IRS selection exactly as specified in the RFC. It is enough
to choose a random number and, for ease of debugging, you may want to choose a random number ending in ``00000`` so you can more easily debug the sequence numbers in your transmissions.

Writing the Packet Arrival Handler
----------------------------------

Writing the "packet arrival handler" (i.e., how TCP reacts when a packet arrives) is actually
pretty simple: you just have to translate pages 64-75 of the RFC into code. A common pitfall
is to write this handler as a gigantic if-else statement (with each branch corresponding to a
TCP state) where you implement your interpretation of what should happen in each state when
a packet arrives. Pages 64-75 methodically describe how to process a packet. Although some
parts of it do involve branching by state, you should not write a gigantic if-else as the
main structure of your packet arrival handler. As noted above, it is important that you
follow the RFC, not your high-level understanding of how TCP must work.


Freeing packets
---------------

Take into account that:

- You're responsible for freeing any packets you create (i.e., any memory you allocate for
  a ``tcp_packet_t`` struct).
- You're also responsible for freeing any packets you remove from the pending packets list.

In both cases, besides freeing the pointer to the ``tcp_packet_t`` struct, you also need to call
``chitcp_tcp_packet_free`` to free other memory associated with the memory (and you should do
this before freeing the pointer to the tcp_packet_t struct).

Also, take into account that ``chitcpd_send_tcp_packet`` records all the information necessary
to send the packet. In other words, it is safe to free the packet after ``chitcpd_send_tcp_packet``
returns (doing so will not interfere with the packet being correctly sent).

Tests that sometimes pass, but sometimes don't
----------------------------------------------

You may sometimes run a test multiple times, and find that the test passes some times,
but not others. Frequently, you may find that your tests pass consistently when run
at a particular log level, but some (but not all) of them fail when run at a different
log level. The reason this can happen is because the sequence of events in a multithreaded
application (like chitcp) can change from one run to another. This is specially
apparent when changing logging levels, since the more verbose logging levels (like DEBUG
and TRACE) effectively inject substantial delays when a thread has to print logs.

For example, suppose you've established a connection, and peer A has to send 5 TCP
packets to peer B, and that peer B sends an ACK packet for each of those packets.
If you are running with no logging, B will probably send those packets right away so,
from peer A's perspective, the sequence of events could be something like this::

    SEND packet 1
    SEND packet 2
    SEND packet 3
    RECEIVE ACK of packet 1
    SEND packet 4
    RECEIVE ACK of packet 2
    SEND packet 5
    RECEIVE ACK of packet 3
    RECEIVE ACK of packet 4
    RECEIVE ACK of packet 5

On the other hand, if you're running with heavy logging, B may take slightly longer to send back
the acknowledgements (because it's spending CPU time printing out logs), so the sequence
of events could instead look like this::

    SEND packet 1
    SEND packet 2
    SEND packet 3
    SEND packet 4
    SEND packet 5
    RECEIVE ACK of packet 1
    RECEIVE ACK of packet 2
    RECEIVE ACK of packet 3
    RECEIVE ACK of packet 4
    RECEIVE ACK of packet 5

Notice how the events still happen in the correct order (the delays introduced by logging will
not result in packets being delivered *out of order*, which is something that would happen
at the network level), but the *interleaving* of the events is different. A correct implementation
of TCP should be able to handle either sequence of events, but
your code could have a subtle bug that only manifests itself when events happen in a particular
order.

When this happens, you should ideally try to identify the bug. Try to find the simplest possible
test where this issue manifests itself, and analyze why the test fails. Of course, this may
be challenging because your code may pass with DEBUG logging, but not with INFO logging (which
provides fewer clues on what could be wrong). This leads us to our next point...


Pick your battles (a.k.a.: "it is ok to not pass 100% of the tests")
--------------------------------------------------------------------

Achieving a perfect implementation that can pass all the tests under every possible sequencing
of events is very challenging. It is very likely that many of you will end up passing nearly
all the tests (and certainly enough to get an E score on Completeness), with a few stubborn
tests that sometimes pass but sometimes don't. More often than
not, this is due to bugs that are very hard to track down, because they only manifest themselves
under a specific ordering of events, and which typically require a very deep debugging session
to resolve.

We encourage you to pick your battles, and to consider whether going down a debugging
rabbit hole for several hours is a sensible use of your time for just a few testing points,
particularly given that you'll have a chance to review your submission. That is time that
could be spent on polishing up your code, documenting it, etc. which is likely to have a bigger
impact on your Code Quality score for this project.

That said, if you are in a situation where you consistently get a high score on the tests
under a specific logging level, you are allowed to mention this in the README file in the root of
your repository, requesting
that the graders run the tests under that logging level (you may *not* request that they run
some tests under one logging level, and other tests under a different logging level). Please
make sure to also include the output of ``make grade``, so the graders can ensure they're
observing the same scores you're seeing.


Dealing with Zero Windows
-------------------------

Until you get to Assignment 2, your code will have no way of dealing with a host that is advertising a window
of zero bytes (a common way of dealing with this is by sending
`probe segments <http://www.tcpipguide.com/free/t_TCPWindowManagementIssues-3.htm>`_). So, if a host does advertise
a window with zero bytes, your TCP may get stuck. The tests are designed to avoid, as much as possible, this situation,
but it may still arise (and will do so sporadically, since it requires a specific sequence of events to happen). We
suggest you add something like this wherever you update the ``SND_WND`` variable::

    if(tcp_data->SND_WND == 0)
        chilog(CRITICAL, "Zero window received. TCP may become stuck.");

If you run a test, and it sporadically times out because of this (but works most of the times), you should not worry
about this, and should consider the test passed.

Note that this situation is different from the *effective window* being equal to zero: this can happen when the sender
has sent enough data to fill the window, but the receiving host may open the window by acknowledging the data or
by advertising a new window size. It may not be uncommon for the effective window to be zero at times, and what
you need to check for is whether the *advertised window* ever becomes zero.


Origin of log messages
----------------------

``tcp-socket-N`` log messages originate in your TCP thread (where ``N`` is the socket number)
 
``socket-layer-N`` log messages originate in the socket layer of the protocol stack (the one that
handles send(), recv(), connect(), etc.). The socket layer is the one that calls your ``tcp_data_init``
function so, in the second part of the project, your timer thread will inherit the same name unless
you specifically set a new name for the timer thread. To make your logs clearer, you can do so by
setting the name of the timer thread with this code (at the start of the timer thread function)::
 
    char thread_name[17];
    snprintf (thread_name, 16, "timer-%d", ptr_to_fd(si, entry));
    pthread_setname_np(pthread_self(), thread_name);
 
That should make the logs a bit easier to interpret, because you'll know when a message is coming
from the socket layer and when it's coming from the timer thread.

The random tests
----------------

In the second part of the project, the random tests are *pretty difficult* to debug, because a
lot ends up happening in them (much more than in any of the other tests). They should be the
very last tests you try to pass, and you should not approach them until all the other tests
are passing *including all the tests from the first part of the project* (if you are failing
any of the other tests, it is likely you will also fail the random tests). Please note that
it will be hard to help you with the random tests if you are not already passing all the other
tests; when this happens, please ask for help on those (non-random) tests first.

Please note that the random tests are actually deterministic, because they use the same random
seed every time. However, the packets are dropped according to a random number generator, not
according to a specific well-defined situation (unlike the other unreliability tests, which
test specific situations like "dropping the SYN/ACK in the three-way handshake", "dropping
only one packet during the data transfer", etc.). Basically, if you can pass all the random
tests, that probably means your implementation is pretty solid.

The RTT tests
-------------

The RTT estimation tests do not contribute to your test grade (the one you get when running ``make grade``).
The reason for this is that these tests are trivial to pass if you just estimate the RTT to be zero
(ensuring your tests never time out). However, the graders will be running these tests and,
if you are not doing any RTT estimation (or if they find issues with the RTT estimation) this
will have an impact on your Code Quality score.


Common Pitfalls
---------------

* **Calling tcp_data_init or tcp_data_free**: You should never call ``tcp_data_init`` or ``tcp_data_free``
  from your code. These functions are called by the socket layer (when a socket is created or destroyed),
  and calling either of them a second time can produce unexpected results.

* **Worrying about functionality that is handled in the socket or network layers**: Since you are writing a TCP implementation that interacts with both a socket layer and a network layer, it can sometimes be challenging to tell what is the responsibility of each layer. In the past, some students have spent a considerable amount of effort worrying about things that were actually already handled for them in other layers, most notably:

  * *The source/destination ports*: You should not set or modify these fields of the TCP header. These
    fields are actually set by ``chitcpd_tcp_packet_create``, which will look at the ports associated with the socket,
    and will fill in the correct ports in the TCP header. Additionally, none of your code should depend on the
    value of the source/destination ports; the socket layer is in charge of delivering data to the correct process 
    (based on the destination port), and is also in charge of assigning
    source ports (either because the port is specified in a call to ``chisocket_bind`` or because one is selected by
    the socket layer in ``chisocket_connect`` when creating an active socket).

    Take into account that, even if you don't explicitly manipulate the port fields of the TCP header,
    you will destroy that information if you zero out a TCP header *after* calling ``chitcpd_tcp_packet_create``.
    If you do this, you will likely get the following error in the chitcpd logs: ``"No socket listening on port 0"``
  * *Reporting errors back to the application layer*: RFC 793 specifies, at various points, that certain errors should
    be returned to the application layer. For example, under the ``SEND Call`` specification (corresponding to chiTCP's
    ``APPLICATION_SEND`` event), the RFC specifies the following::

        FIN-WAIT-1 STATE
        FIN-WAIT-2 STATE
        CLOSING STATE
        LAST-ACK STATE
        TIME-WAIT STATE

          Return "error:  connection closing" and do not service request.

    This does not mean that your handling of ``APPLICATION_SEND`` in those states should implement some error-handling
    logic. For the most part, these kind of errors are handled either in the socket layer or the network layer. For
    example, in the above case, if an application called ``chisocket_send`` on a socket that was in any of the
    above states, the socket layer would return an error (and this event would never propagate to your state handling
    functions).
  * *Passive sockets*: The setup and management of passive sockets is handled by the socket layer, including the
    creation of a new active socket when a passive socket receives a SYN packet. The sockets you will deal will
    in your implementation will always be active sockets, resulting either from an ``APPLICATION_CONNECT`` event or
    from a passive socket spawning an active socket after receiving a SYN packet.


* **Not initializing the sequence number in the buffer**: You need to initialize the initial sequence number of
  the buffers with ``circular_buffer_set_seq_initial``. If you do not, functions ``circular_buffer_first`` and
  ``circular_buffer_next`` will return incoherent values.

  Take into account that the initial sequence number of the buffers should be the same as the first sequence
  number of sendable/received *data*. So, it would not be exactly ISS/IRS, because those are actually the
  first "byte" used by the SYN (but which do not represent any actual data). So, you would initialize
  them to ISS+1 and IRS+1.

* **Implementing stop-and-wait instead of sliding window, or ignoring the window size**: In sliding window,
  you send as much data as allowed by the receiver's window (after accounting for any data that may already
  be in flight). If you send one packet and wait for an ACK before sending the next one, you're implementing
  stop-and-wait, not sliding window. If, on the other hand, you do send multiple packets at once, but send
  more data than allowed by the window, this will likely result in undefined behaviour. An easy way to
  check this is to see whether, at the start of the tests that send more than 4KB, your code send only
  4KB and doesn't send more data until it receives a first ACK. If you send (for example) 32KB all at
  once, then you're ignoring the windows size.

* **Sending only one packet when segmentizing**: Whenever you process the send buffer, you should always
  send as many packets as possible without exceeding the receiver's advertised window. A common pitfall
  is to correctly identify that the send buffer contains more than one MSS of data, but then sending
  only that first MSS, instead of sending as many packets allowed by SND.WND.

* **Sending only when the APPLICATION_SEND event happens**: The ``APPLICATION_SEND`` event simply
  informs TCP that the application has called ``send()``, which means there is likely new data to
  send, and you should send it if possible. However, this is *not* the only time you'll want to
  process the send buffer to send data. If the values of SND.UNA or SND.WND change (in general,
  if the window shifts or grows), it may be possible for you to send more data to the other peer.
  It is a good strategy to write a separate function that handles this task ("check the send
  buffer and determine whether any data can be sent and, if so, send it"), and call it not just
  from the ``APPLICATION_SEND`` handler but also whenever SND.UNA or SND.WND change.

* **Not setting/reading the window variables**: Every TCP packet you send must include a valid
  value for SEG.WND. This is true regardless of whether the size of the receive buffer has
  changed since the last TCP packet, and regardless of whether the packet carries a payload
  or not. The value of SEG.WND is always set to the available space in the receive buffer.

  Similarly, the value of SND.WND is always updated when you receive a valid TCP packet.

* **Not delaying the FIN packet**: When an ``APPLICATION_CLOSE`` event happens, you *only*
  send a FIN packet if the send buffer is empty. If the send buffer still has
  unacknowledged/unsent data, you don't send the FIN packet until the send buffer is empty.

  Similarly, it is not enough to simply process your send buffer from ``APPLICATION_CLOSE``
  to clear the buffer, because the receiver's window may not allow you to do this at that
  point. So, you have to take into account that the send buffer may not become empty
  until *after* you've processed the ``APPLICATION_CLOSE`` event.

* **Not checking the return value of pthread_cond_timed_wait**: ``pthread_cond_timed_wait``
  will return ``EINVAL`` under certain circumstances that you can easily find yourself in.
  The most common one is providing an invalid value for ``abstime``, usually by
  setting the ``tv_nsec`` field to a value less than 0 or greater than 1,000,000,000.
  So, make sure to, at the very least, ``chilog`` any time ``pthread_cond_timed_wait``
  returns a value other than ``0`` or ``ETIMEDOUT``, as that may alert you to issues
  with your code that can make your multitimer fail.