Project 2 Rubric
----------------

The grading of this project follows a specifications grading approach. If you have not already
done so, make sure to read our `Grading <../syllabus.html#grading>`__ section of
the syllabus for more details.

This project has two submissions: Project 2A and Project 2B. You will receive two SNU scores
for each submission:

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

.. include:: project2_timeline.txt

Project 2A will likely not be graded until after Project 2B is due. Once Project 2B is graded,
you will have an opportunity to make a resubmission for Project 2A and/or 2B (and, at that point,
you will have feedback for both Project 2A and 2B). We will
post more details about the resubmission process at a later time.


Completeness
------------

The Completeness component will be determined by running the following command::

    make grade

(see `Automated tests <http://chi.cs.uchicago.edu/chitcp/testing.html#automated-tests>`__
in the chiTCP documentation and, specifically, the "Producing a grade report" section
for more details)

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

Please note that, since Project 2B builds on Project 2A, all rubric items in
Project 2A also apply on Project 2B.

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

When assessing the correctness of your code, we will be paying special attention
to the following issues:

General
~~~~~~~

- **Not setting a correct value for SEG.WND**
- **Not updating SND.WND when a packet arrives**
- **Not locking the pending packet mutex before accessing the list of pending packets**
- **Not freeing packets once you're done with them**
- **Sending a packet that doesn't conform to the RFC** (even if it happens to pass the tests). This can include setting incorrect flags, such as setting the SYN flag after the three-way handshake is done.
- **Making a state transition inconsistent with the RFC**
- **Incorrect code for checking a condition specified in the RFC**. For example, when comparing values, using ``<`` even when the RFC says to check for ``<=``. This rubric item also encompasses coding mistakes that result in a condition ultimately being checked incorrectly (e.g., writing something like ``a < b < c`` instead of ``a<b && b<c``).
- **Not locking the pending packets mutex before accessing the pending packets list.**


[Project 2A] 3-way Handshake
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- **Acknowledging the final ACK in the 3-way handshake**. Remember that acknowledgements are not acknowledged in TCP.
- **Not checking that the SYN was acknowledged before sending the ACK and changing state to ESTABLISHED**.
- **3-way Handshake: Setting the ISS to a constant value, instead of using a random number.**
- [Major issue] **Writing a 3-way handshake by rote that doesn't check the TCP header values, and assumes that the first three messages exchanged must be a SYN, SYN/ACK, and ACK**. For example, you could technically pass the three-way handshake tests by making TCP go into an ESTABLISHED state after receiving two packets (without checking whether the first one is a SYN packet, and whether the second one contains a valid ACK).

[Project 2A] Data Transfer
~~~~~~~~~~~~~~~~~~~~~~~~~~

- **Not checking if the value of SEG.ACK and SEG.SEQ is correct**. In some cases, no action needs to be taken when a value is incorrect, but we still recommend (but not require) that you chilog() any such cases.
- **Not setting the ACK flag and including a valid acknowledgement number in every packet after the 3-way handshake**. Remember that, even if you haven't received any new data, you still have to send a valid acknowledgement number in every segment.
- **Not updating SND.UNA and SND.WND with SEG.ACK and SEG.WND for every incoming packet with a valid SEG.ACK**
- [Major issue] **Unconditionally sending an ACK segment in reply to every segment that is received**.
- **Not updating the value of RCV.WND in the APPLICATION_RECEIVE event**
- [Major issue] **Not taking SND.WND into account when processing the send buffer**. You should make sure to never send more bytes than allowed by the effective window (remember this won't be just SND.WND, but is computed based on SND.WND).
- **Not segmenting the data in the send buffer into MSS-sized packets (536 bytes), or segmenting it incorrectly**

[Project 2A] Connection teardown
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- **Not handling the APPLICATION_CLOSE event in both ESTABLISHED and CLOSE_WAIT**. In both cases, you should only send a FIN packet if there is no data left in the send buffer, but you should transition to FIN-WAIT-1 / LAST-ACK (respectively) right away.
- **Not delaying the FIN packet until all outstanding data has been sent and acknowledged**.
- **Not handling the APPLICATION_RECEIVE event in FIN_WAIT_1 and FIN_WAIT_2**. TCP can still receive data in those states, which means the application may still call `recv`.

[Project 2B] Managing the Retransmission Queue
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- **Adding pure ACK packets (i.e., not SYN or FIN segments, nor segments with a payload) to the retransmission queue**. ACK packets are not retransmitted.
- **Adding segments with a payload to the retransmission queue, but not adding SYN or FIN segments**
- **Not removing acknowledged packets from the retransmission queue**. Take into account that multiple packets could be removed because of a cumulative ack. However, you should not automatically remove all the packets from the retransmission queue whenever you receive an ACK, because you could have packets 1-10 in the queue, and receive an acknowledgement only for 1-5.
- **Unnecessarily locking the retransmission queue**. The retransmission queue is only ever accessed by the socket thread, so there is no possibility of concurrent access by multiple threads. So, it does not need to be protected by a mutex.

[Project 2B] Managing the Timer Thread
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- **Unconditionally setting the timer every time a packet is sent**. You should set the timer only if you are sending a packet with data (or a SYN or FIN) *and* the timer is not already active. If the timer is already active, then sending new data doesn't affect the timer in any way.
- **Not cancelling the timer when all outstanding data has been acknowledged**
- **Unconditionally restarting the timer when any ACK is received**. The timer should only be restarted when the ACK acknowledges outstanding data.
- **Not restarting the timer at all when an ACK (that acknowledges new data) is received**.

[Project 2B] Handling the retransmission timeout
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- **Not doing Go-back-N**. When a TIMEOUT event happens, you should be doing go-back-N: find the earliest unacknowledged segment in the retransmission queue, and retransmit that segment and all subsequent segments. It is not enough to only retransmit the first segment (without checking whether there are subsequent packets)
- **Not backing off the RTO each time a timeout happens**.

[Project 2B] RTT estimation
~~~~~~~~~~~~~~~~~~~~~~~~~~~
- [Major issue] **Not doing any RTT estimation**. The RTT estimation tests can't check whether you implemented RTT estimation correctly (at most, they may alert you to failures that arise as a result of an incorrect RTT estimation), so the graders will be manually checking that you implemented RTT estimation correctly.
- **Doing RTT estimation, but making a minor mistake in computing the RTT**
- **Doing RTT estimation, but not excluding retransmitted segments from the RTT estimation**

[Project 2B] Persist timer
~~~~~~~~~~~~~~~~~~~~~~~~~~
- **Did not actually implement the persist timer.** (this rubric item is only applied if you are somehow passing all the persist timer tests, despite not implementing the persist timer)
- **Not updating SND.NXT when sending a probe segment.**

[Project 2B] Out-of-order
~~~~~~~~~~~~~~~~~~~~~~~~~
- **Did not actually implement out-of-order delivery.** (this rubric item is only applied if you are somehow passing all out-of-order tests, despite not implementing out-of-order delivery)
- **Not placing out-of-order segments in the out-of-order list**
- **Inserting duplicate segments in the out-of-order list**


Design
------

When assessing the design of your code, we will be paying special attention
to the following:

- [Major issue] **Not writing a packet arrival handler**. You should structure your code so that you have a single `packet arrival handler <project2_tips.html#writing-the-packet-arrival-handler>`__ that gets called from any state where a packet arrives.
- [Major issue] **Writing a packet arrival handler that does not follow the exact SEGMENT ARRIVES logic in the RFC.** Most notably, you should not try to reverse-engineer the logic in ``SEGMENT ARRIVES`` to figure our the steps to follow based on the current TCP state (the RFC does indicate a number of steps that will depend on the TCP state, but you should check for the value of the TCP state when the RFC tells you to, instead of combing through the logic and trying to extract the steps that only apply to a given state).
- **Writing a packet arrival handler, but still having some of the packet arrival handler logic in the state handling functions**. That said, we will allow some of the packet arrival handling logic to appear in the CLOSED, LISTEN, and SYN-SENT states (and the rest in a packer arrival handler), given that the RFC specifies a specific treatment for those three states, whereas the rest of the states are lumped together.
- **Not writing a function to process the send buffer**. Based on the TCP variables, this function should decide whether to send any packets or not. This function should be called when handling APPLICATION_SEND, and whenever SND.UNA or SND.WND changes (since that may open up the window, allowing more data to be sent).
- **Destroying the multitimer thread each time a single timer expires**. Your multitimer should have a single thread that should not be stopped/re-recreated at any point (it should just be stopped when calling mt_free, once we're completely done using the multitimer). Most notably, you should not destroy the thread when a single timer expires (to then create a thread when setting the next timer)
- **Inefficient access to the next expiring timer**. It should be possible to determine the next expiring timer in O(1) time. It is ok to have a data structure that requires more than O(1) time to add/remove an active timer.
- **Inefficient access to a timer by ID**. It should be possible to access a timer by ID in O(1) time.
- [Major issue] **Implementing the multitimer with busy waiting instead of using condition variables**
- **Complicated callback functions for the retransmission timer or the persist timer**. These callback functions should be little more than a call to chitcpd_timeout, and should include little (if any) retransmission/persist logic.
- **Repeating retransmission logic in multiple places**. Your code should be structured in such a way that you only need to add segments to the retransmission queue in a single point in your code (e.g., by having a "send packet" function that also takes care of adding the packet to the retransmission queue if necessary).


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


..
    Optional Resubmission
    ---------------------

    When you receive your graded Project 2, you have two options:

    #. If you are satisfied with the scores you have received, no action is necessary on your end.
       Your scores on Project 2 will be used to compute your `Base Grade <../grading.html#base-grade>`__.
    #. You may make an *optional* resubmission to address any feedback you received in Project 2,
       which may increase your scores in the project.

    Note: You *cannot* make a resubmission if you got E's on both Completeness and Code Quality. If you
    are in this situation and want additional feedback on your grading, please ask on Ed.

    If you decide to make a resubmission, you **MUST** edit the ``README`` file in the root of
    the repository to include the following information:

    - **Rubric items you have addressed**: Rubric items that appear selected on Gradescope (under "Manual Grading")
      represent issues that had an impact on your Code Quality score. To facilitate the work of the
      graders, you must list each rubric item you have addressed, with the following information:

      - The rubric item description, exactly as it appears on Gradescope.
      - 1-2 sentences explaining how you addressed the rubric item.
      - If the work you did on the rubric item is limited to a few lines of code, specify the filename and line number(s),
        If your work on this rubric item involved deeper changes to your code, you do not need to list every single line
        of code you changed, but you should try to give the graders a general sense of where you made the changes, including
        a few examples if possible
        (e.g., "I combed through the code to make sure I was using descriptive variable names; for example, I changed ``c`` to
        ``channel`` in several functions", "I reorganized functions ``foo()``, ``bar()``, and ``baz()`` as requested", etc.)

    - **Rubric items you have NOT addressed**: It is also important that you let us know what rubric items you
      decided not to address, as this will expedite the work of the graders. For these rubric items, it is enough
      to provide a list of the rubric item descriptions (exactly as they appear on Gradescope)

    - **Substantial new code added to your submission**: If you added substantial new code that was not present in your
      original submission (e.g., if your original submission did not implement certain features, and you have now included
      new code to implement those features), you must specify the functions you added or modified in either tcp.c or multitimer.c. For example you could include something like this::

        Modified function: handle_packet_arrival (tcp.c)
        New functions: add_to_out_of_order, process_out_of_order (tcp.c)

        Our original submission did not implement out-of-order delivery,
        but we implemented it in the above functions.

    - **Changes made to pass additional tests**: If you made changes to your code with the goal of passing more tests,
      please specify your original test score, and the new test score. If your work only involved a few minor bug fixes,
      please let us know you did this (but you do not need to specify the exact changes you made). On the other hand,
      if you skipped parts of Assignment 2 in your original submission, and have written entirely new code, please make
      sure you have specified this as part of the "substantial new code", and that you also specify that doing so
      allowed you to pass additional tests.
    - **Other changes**: If you made other changes to your code, such as refactoring large parts of your code, make
      sure to specify this too.

    You should consider the ``README`` file as important as the changes you are making to your code: **resubmissions
    that do not include the information requested above may not be graded at all**.

    In general, if you are making a resubmission that only involved addressing rubric items, without adding substantial
    new code to your submission, there is a high likelihood that addressing all the rubric items will bump your Code
    Quality score to at least the next score.

    On the other hand, if you are making a resubmission that involves adding substantial new code, please bear in mind
    that the graders could identify issues in that new code that will impact your Code Quality score. That said,
    once you receive the resubmission grading, you will be given the option to revert back to your original Project 2
    score if you prefer.



