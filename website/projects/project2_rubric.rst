Project 2 Rubric
================

The grading of this project follows a specifications grading approach. If you have not already
done so, make sure to read our `Grading <../syllabus.html#grading>`__ section of
the syllabus for more details.

This project has two submissions: Project 2A and Project 2B. You will receive two SNU scores
for each submission:

- **Completeness score**: This score will be determined solely by the result of running
  the automated tests, as these give a measure of how *complete* your implementation
  is (i.e., how much of the assignment you implemented).
- **Code Quality score**: This score is determined by a review of your code done by
  the course staff, and is based on four aspects of your code:

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
  - *Documentation*: You will be required to submit certain documentation on
    your code (the exact documentation is described below)

Furthermore, you will complete one or two code reviews as part of this project
(see `Code Reviews`_ below).

Project Timeline
----------------

The exact timeline for the project will be the following:

.. include:: project2_timeline.txt

You will receive some early feedback from Project 2A before Project 2B is due.

Once Project 2B is graded,
you will have an opportunity to make a resubmission for Project 2A and/or 2B (and, at that point,
you will have feedback for both Project 2A and 2B).

Completeness
------------

The Completeness component will be determined by running the following command::

    make grade

(see `Producing a grade report <http://chi.cs.uchicago.edu/chitcp/testing.html#producing-a-grade-report>`__
in the chiTCP documentation for more details)

Take into account that Gradescope will only fetch the files listed in the
`Submission <project2.html#submission>`__ instructions. Any changes you make
to other files will be ignored, and your code will be tested with the original
version of those files.

Your SNU score will then be determined as follows:

+---------------------+------------------------+--------------------------+
|                     | Project 2A             | Project 2B               |
+                     +------------------------+--------------------------+
| Grade               | chiTCP Assignment 1    | chiTCP Assignments 1+2   |
+=====================+========================+==========================+
| Satisfactory        | at least 90            | at least 180             |
+---------------------+------------------------+--------------------------+
| Needs Improvement   | at least 60            | at least 120             |
+---------------------+------------------------+--------------------------+
| Unsatisfactory      | less than 60           | less than 120            |
+---------------------+------------------------+--------------------------+


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
  only placeholder code (e.g., code that includes handlers for all the required
  TCP states and events, but where the handlers are empty or filled with "TODO"s, etc.)

That said, while the issues listed below are the main things we care about in this project,
it is not possible for us to give you an exhaustive list of every single thing that could
affect your code quality score. If you get a comment pointing out an issue in your
code that we did not list below, take it as an opportunity to improve your work
(and remember that you'll have a chance to revise your work!)

**Note**: We use a Claude-based tool to help identify the rubric items that likely need
attention in any given submission. While this helps ensure that no rubric items slip
through the cracks when grading your work, the grading is ultimately done by human
graders (who verify any suggestions made by this tool).

Correctness
~~~~~~~~~~~

When assessing the correctness of your code, we will be paying special attention
to the following issues:

General
^^^^^^^

- **Not setting a correct value for SEG.WND**
- **Not updating SND.WND when a segment arrives**
- **Not locking the pending segment mutex before accessing the list of pending segments**
- **Not freeing segments once you're done with them**
- **Sending a segment that doesn't conform to the RFC** (even if it happens to pass the tests). This can include setting incorrect flags, such as setting the SYN flag after the three-way handshake is done.
- **Making a state transition inconsistent with the RFC**
- **Incorrect code for checking a condition specified in the RFC**. For example, when comparing values, using ``<`` even when the RFC says to check for ``<=``. This rubric item also encompasses coding mistakes that result in a condition ultimately being checked incorrectly (e.g., writing something like ``a < b < c`` instead of ``a<b && b<c``).


[Project 2A] 3-way Handshake
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- **Acknowledging the final ACK in the 3-way handshake**. Remember that acknowledgements are not acknowledged in TCP.
- **Not checking that the SYN was acknowledged before sending the ACK and changing state to ESTABLISHED**.
- **3-way Handshake: Setting the ISS to a constant value, instead of using a random number.**
- [Major issue] **Writing a 3-way handshake by rote that doesn't check the TCP header values, and assumes that the first three messages exchanged must be a SYN, SYN/ACK, and ACK**. For example, you could technically pass the three-way handshake tests by making TCP go into an ESTABLISHED state after receiving two segments (without checking whether the first one is a SYN segment, and whether the second one contains a valid ACK).

[Project 2A] Data Transfer
^^^^^^^^^^^^^^^^^^^^^^^^^^

- **Not checking if the value of SEG.ACK and SEG.SEQ is correct**. In some cases, no action needs to be taken when a value is incorrect, but we still recommend (but not require) that you chilog() any such cases.
- **Not setting the ACK flag and including a valid acknowledgement number in every segment after the 3-way handshake**. Remember that, even if you haven't received any new data, you still have to send a valid acknowledgement number in every segment.
- **Not updating SND.UNA and SND.WND with SEG.ACK and SEG.WND for every incoming segment with a valid SEG.ACK**
- [Major issue] **Unconditionally sending an ACK segment in reply to every segment that is received**.
- **Not updating the value of RCV.WND in the APPLICATION_RECEIVE event**
- [Major issue] **Not taking SND.WND into account when processing the send buffer**. You should make sure to never send more bytes than allowed by the effective window (remember this won't be just SND.WND, but is computed based on SND.WND).
- **Not segmenting the data in the send buffer into MSS-sized segments (536 bytes), or segmenting it incorrectly**

[Project 2A] Connection teardown
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- **Not handling the APPLICATION_CLOSE event in both ESTABLISHED and CLOSE_WAIT**. In both cases, you should only send a FIN segment if there is no data left in the send buffer, but you should transition to FIN-WAIT-1 / LAST-ACK (respectively) right away.
- **Not delaying the FIN segment until all outstanding data has been sent and acknowledged**.
- **Not handling the APPLICATION_RECEIVE event in FIN_WAIT_1 and FIN_WAIT_2**. TCP can still receive data in those states, which means the application may still call `recv`.

[Project 2B] Managing the Retransmission Queue
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- **Adding pure ACK segments (i.e., not SYN or FIN segments, nor segments with a payload) to the retransmission queue**. ACK segments are not retransmitted.
- **Adding segments with a payload to the retransmission queue, but not adding SYN or FIN segments**
- **Not removing acknowledged segments from the retransmission queue**. Take into account that multiple segments could be removed because of a cumulative ack. However, you should not automatically remove all the segments from the retransmission queue whenever you receive an ACK, because you could have segments 1-10 in the queue, and receive an acknowledgement only for 1-5.
- **Unnecessarily locking the retransmission queue**. The retransmission queue is only ever accessed by the socket thread, so there is no possibility of concurrent access by multiple threads. So, it does not need to be protected by a mutex.

[Project 2B] Managing the Timer Thread
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- **Unconditionally setting the timer every time a segment is sent**. You should set the timer only if you are sending a segment with data (or a SYN or FIN) *and* the timer is not already active. If the timer is already active, then sending new data doesn't affect the timer in any way.
- **Not cancelling the timer when all outstanding data has been acknowledged**
- **Unconditionally restarting the timer when any ACK is received**. The timer should only be restarted when the ACK acknowledges outstanding data.
- **Not restarting the timer at all when an ACK (that acknowledges new data) is received**.

[Project 2B] Handling the retransmission timeout
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- **Not doing Go-back-N**. When a TIMEOUT event happens, you should be doing go-back-N: find the earliest unacknowledged segment in the retransmission queue, and retransmit that segment and all subsequent segments. It is not enough to only retransmit the first segment (without checking whether there are subsequent segments)
- **Not backing off the RTO each time a timeout happens**.

[Project 2B] RTT estimation
^^^^^^^^^^^^^^^^^^^^^^^^^^^
- [Major issue] **Not doing any RTT estimation**. The RTT estimation tests don't count towards your test score (see `The RTT tests <project2_tips.html#the-rtt-tests>`__), and they can't check whether you implemented RTT estimation correctly (at most, they may alert you to failures that arise as a result of an incorrect RTT estimation), so the graders will be manually checking that you implemented RTT estimation correctly.
- **Doing RTT estimation, but making a minor mistake in computing the RTT**
- **Doing RTT estimation, but not excluding retransmitted segments from the RTT estimation**

[Project 2B] Persist timer
^^^^^^^^^^^^^^^^^^^^^^^^^^
- **Did not actually implement the persist timer.** (this rubric item is only applied if you are somehow passing all the persist timer tests, despite not implementing the persist timer)
- **Not updating SND.NXT when sending a probe segment.**

[Project 2B] Out-of-order
^^^^^^^^^^^^^^^^^^^^^^^^^
- **Did not actually implement out-of-order delivery.** (this rubric item is only applied if you are somehow passing all out-of-order tests, despite not implementing out-of-order delivery)
- **Not placing out-of-order segments in the out-of-order list**
- **Inserting duplicate segments in the out-of-order list**


Design
~~~~~~

When assessing the design of your code, we will be paying special attention
to the following:

- [Major issue] **Not writing a segment arrival handler**. You should structure your code so that you have a single `segment arrival handler <http://chi.cs.uchicago.edu/chitcp/implementing.html#implementing-the-tcp-c-file>`__ that gets called from any state where a segment arrives.
- [Major issue] **Writing a segment arrival handler that does not follow the exact SEGMENT ARRIVES logic in the RFC.** Most notably, you should not try to reverse-engineer the logic in ``SEGMENT ARRIVES`` to figure out the steps to follow based on the current TCP state (the RFC does indicate a number of steps that will depend on the TCP state, but you should check for the value of the TCP state when the RFC tells you to, instead of combing through the logic and trying to extract the steps that only apply to a given state).
- **Writing a segment arrival handler, but still having some of the segment arrival handler logic in the state handling functions**. That said, we will allow some of the segment arrival handling logic to appear in the CLOSED, LISTEN, and SYN-SENT states (and the rest in a segment arrival handler), given that the RFC specifies a specific treatment for those three states, whereas the rest of the states are lumped together.
- **Not writing a function to process the send buffer**. Based on the TCP variables, this function should decide whether to send any segments or not. This function should be called when handling APPLICATION_SEND, and whenever SND.UNA or SND.WND changes (since that may open up the window, allowing more data to be sent).
- **Destroying the multitimer thread each time a single timer expires**. Your multitimer should have a single thread that should not be stopped/re-recreated at any point (it should just be stopped when calling mt_free, once we're completely done using the multitimer). Most notably, you should not destroy the thread when a single timer expires (to then create a thread when setting the next timer)
- **Inefficient access to the next expiring timer**. It should be possible to determine the next expiring timer in O(1) time. It is ok to have a data structure that requires more than O(1) time to add/remove an active timer.
- **Inefficient access to a timer by ID**. It should be possible to access a timer by ID in O(1) time.
- [Major issue] **Implementing the multitimer with busy waiting instead of using condition variables**
- **Complicated callback functions for the retransmission timer or the persist timer**. These callback functions should be little more than a call to chitcpd_timeout, and should include little (if any) retransmission/persist logic.
- **Repeating retransmission logic in multiple places**. Your code should be structured in such a way that you only need to add segments to the retransmission queue in a single point in your code (e.g., by having a "send segment" function that also takes care of adding the segment to the retransmission queue if necessary).


Style
~~~~~

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


Documentation
~~~~~~~~~~~~~

Your submission must include a ``DOCUMENTATION.md`` file in the ``chitcp/`` directory of your repository
with some specific documentation about the code you have written. If you do not
include this file, Gradescope will not run the tests on your submission (it will show a score of zero), and your
submission will automatically receive a score of Needs Improvement. If you do
include it, but the file does not provide the information we request below, this will
be treated as a major issue in your submission.

The ``DOCUMENTATION.md`` file **must** follow the template below
(the exact sections are explained further below):

.. code-block:: markdown

    Project 2
    =========

    Team members:
    - TEAM MEMBER 1 (CNETID1)
    - TEAM MEMBER 2 (CNETID2)

    Test score: XXX / YYY

    New/modified functions (in existing files)
    ------------------------------------------
    - function1() in tcp.c
    - function2() in multitimer.c

    Other code details / requests for feedback
    ------------------------------------------
    <COMPLETE THIS SECTION>

    Known omissions
    ---------------
    <COMPLETE THIS SECTION>

    Citations
    ---------
    <COMPLETE THIS SECTION>

Below you can find more details on each of the sections. If you are not providing any
information in a given section, please do not remove the section. Instead, just write
``N/A`` below it.

- **Team members**: Include the names and CNetIDs of both team members.

- **Test score**: Please include the test score you are seeing when running the tests
  on your computer. This will allow us to look into situations where the Gradescope autograder
  reports a different score (in these cases, we will run the tests manually to verify we
  can get the same score you are getting)

- **New/modified functions (in existing files)**: If you added new functions to ``tcp.c`` or ``multitimer.c``,
  or if you modified any existing function, please list them here.
  Note: this does **not** include the functions we asked you to implement (the TCP state
  handler functions in ``tcp.c``, and the multitimer functions in ``multitimer.c``).
  You do not need to list those functions.

- **Other code details / requests for feedback**: Use this section to provide any other
  information that may be relevant to the graders as they read through your code.
  If you would like us to provide feedback on any specific aspect of your work,
  you can also let us know in this section.

- **Known omissions**: If you intentionally skipped any part of the project, or intentionally
  did not address any rubric items, please list them here. If we can provide any feedback that
  would help you address these rubric items, please let us know here as well.

- **Citations**: If you used AI tools, describe at a high level how you used these tools.
  Additionally, if you had any high-level discussions about the project with other students
  in the class, please list their names here.


Other Code Quality Issues
~~~~~~~~~~~~~~~~~~~~~~~~~

There are a couple of other issues that we care about across all projects:

.. include:: additional_penalties.txt

Code Reviews
------------

In this project, you will have to complete a Pre-submission Code Review and, depending
on your Project 2B scores, a Feedback Code Review. You must schedule
and complete these code reviews no later than the due date specified in the
“Project Timeline” above (see `Code Review Scheduling Instructions <code-review-scheduling.html>`__
for instructions on how to schedule your code review).

Pre-submission Code Review
~~~~~~~~~~~~~~~~~~~~~~~~~~

The purpose of this code review is to go over your code before Project 2B is due,
so we can identify issues and other opportunities for improvement. In general,
this code review will be structured as follows:

- We will ask you to walk us through the code you’ve written so far. We will use
  this walkthrough to identify aspects of your code that may need improvement. You
  should not approach this as a line-by-line explanation of your code; instead,
  give us a high-level sense of what you implemented, while showing us the code
  that implements each part of the project.
- We will ask you if you have any questions about the work that remains to be done
  in the project.
- Finally, we will go over any issues we identified.

**You do not need to wait until you have a near-complete version of Project 2B to
request this code review.** We recommend you schedule this code review as soon as you have
a reasonably complete draft of Project 2A, so you can both get feedback on your 2A
implementation, and also ask questions about what remains to be done in Project 2B.

Feedback Code Review
~~~~~~~~~~~~~~~~~~~~

This code review is only required if you did not score two S's (Completeness and Code Quality)
in Project 2B. In that case, you must schedule your Feedback Code Review to take place after
Project 2B grading has been released, and no later than the due date specified in the
“Project Timeline” above.

If you scored two S's in Project 2B, you will automatically receive an S in the
Project 2 Feedback Code Review. You are still welcome to request a Feedback Code Review
to receive additional feedback on your project, but it must take place after the
Project 2 Resubmission deadline.

The purpose of this code review is to go over the grading of your Projects 2A and 2B
submissions, and deliver additional feedback on your submissions. If you did not score
a *Satisfactory* in Code Quality, we will also go over the items that we would expect
you to fix in your resubmission (to be able to score a Satisfactory on the resubmission).

If you are planning to make a resubmission, it is important that you schedule your
code review as soon as possible after the grading is released, so you have enough
time to work on a resubmission.

Finally, you should not need to prepare for this code review, but bear in mind that
we may ask you questions about your code, so we can provide you with clear feedback
and guidance on how to improve your code.

Scoring and Other Requirements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Code reviews are graded on completion only; for the purposes of the grading Bundles
listed in the syllabus, completing a code review earns a Satisfactory, and not
completing a code review earns a Needs Improvement. If you score two S's in
Project 2B, you will automatically receive a Satisfactory in the Feedback Code Review.

Code reviews are conducted in-person, and both students in a team must attend and
participate. In the Pre-submission Code Review, where we will ask you to walk us
through your code, you may want to have a quick conversation beforehand to decide
who will explain what portions of the code.

Finally, we reserve the right to ask individual students or teams of students to
undergo additional code reviews if there are any concerns with their understanding
of their code.

Resubmission
------------

After you receive your graded Project 2B, you can make a resubmission to address
any feedback you received in Projects 2A and/or 2B (and on the Feedback Code Review).
This may increase your scores in those projects.

While the project is divided into two parts (2A and 2B), remember that Project 2B
builds on Project 2A. As such, you should think about your
resubmission as a final cumulative submission that addresses any remaining issues
in your Project 2B submission (i.e., you should not think in terms
of making two separate resubmissions, one for 2A and another for 2B, with different
code for each submission).

.. note::

    If you scored two S's in your initial submission for Project 2B, but not in your initial Project 2A
    submission, you do not need to make any further changes to your Project 2B
    code to bump your 2A scores up to two S's. However, we do still need you
    to make an (abbreviated) resubmission. If you are in this situation, please
    skip to "Project 2B Submissions with two S's" below.

Required Documentation
~~~~~~~~~~~~~~~~~~~~~~

Making a resubmission involves not just addressing the feedback we gave you, but
also preparing some documentation explaining the changes you made to your code.
You should consider this documentation as important as the changes you are making
to your code: **resubmissions that do not include the information requested below
WILL NOT BE GRADED**.

If you decide to make a resubmission, you **MUST** add a ``RESUBMISSION.md`` file
in the ``chitcp/`` directory of your repository using the following template: (the exact sections
are explained below)

.. code-block:: markdown

    Project 2 Resubmission
    ======================

    Team members:
    - TEAM MEMBER 1 (CNETID1)
    - TEAM MEMBER 2 (CNETID2)

    Rubric items you have addressed
    -------------------------------
    <COMPLETE THIS SECTION>

    Rubric items you have NOT addressed
    -----------------------------------
    <COMPLETE THIS SECTION>

    Substantial new code added to your submission
    ---------------------------------------------
    <COMPLETE THIS SECTION>

    Changes made to pass additional tests
    -------------------------------------
    <COMPLETE THIS SECTION>

    Other changes
    -------------
    <COMPLETE THIS SECTION>

Below you can find more details on each of the sections. If you are not providing any
information in a given section, please do not remove the section. Instead, just write
``N/A`` below it.

- **Team members**: Ordinarily, this would be the same two team members who made the original submission.
  However, if you worked individually on the resubmission (because your teammate was happy with the
  original submission, and didn't want to work further on it), please make sure to note this here.

- **Rubric items you have addressed**: Rubric items that appear selected on Gradescope (under "Manual Grading")
  represent issues that had an impact on your Code Quality score. To facilitate the work of the
  graders, you must list each rubric item you have addressed, with the following information:

  - The rubric item description, exactly as it appears on Gradescope.
  - 1-2 sentences explaining how you addressed the rubric item.
  - If the work you did on the rubric item is limited to a few lines of code, specify the filename and line number(s),
    If your work on this rubric item involved deeper changes to your code, you do not need to list every single line
    of code you changed, but you should try to give the graders a general sense of where you made the changes, including
    a few examples if possible
    (e.g., "I combed through the code to make sure I was using descriptive variable names; for example, I changed ``p`` to
    ``segment`` in several functions", "I reorganized functions ``foo()``, ``bar()``, and ``baz()`` as requested", etc.)

  Bear in mind that the Project 2A rubric items are a subset of the Project 2B rubric items. This means that...

  - If your initial Project 2B submission already addressed a rubric item from Project 2A (and the rubric
    item was no longer selected in your graded Project 2B), it is enough to say "This rubric item was addressed
    in Project 2B"
  - If you scored an N in Code Quality in Project 2A, but then scored an S in Code Quality
    in Project 2B, you do not need to explain how you addressed each individual rubric item.
    Instead, please include the following text in this section: "We earned an S in Code Quality
    in Project 2B"

- **Rubric items you have NOT addressed**: It is also important that you let us know what rubric items you
  decided not to address, as this will expedite the work of the graders. For these rubric items, it is enough
  to provide a list of the rubric item descriptions (exactly as they appear on Gradescope)

- **Substantial new code added to your submission**: If you added substantial new code that was not present in your
  original submission (e.g., if your original submission did not implement several commands, and you have now included
  new code to implement those commands), you must specify the affected files, as well as the new functionality that
  is added by the new code. For example, you could include something like this::

    Modified files: tcp.c, tcp.h

    Fleshed out function X() to get retransmissions to work.

    Added functions X(), Y(), and Z() to implement out-of-order delivery.

- **Changes made to pass additional tests**: If you made changes to your code with the goal of passing more tests,
  please specify your original test score, and the new test score. If your work only involved a few minor bug fixes,
  please let us know you did this (but you do not need to specify the exact changes you made). On the other hand,
  if you skipped parts of Project 2B in your original submission, and have written entirely new code, please make
  sure you have specified this as part of the "substantial new code", and that you also specify that doing so
  allowed you to pass additional tests.
- **Other changes**: If you made other changes to your code, such as refactoring large parts of your code, make
  sure to specify this too.

Once again, if you do not include a ``RESUBMISSION.md`` file with the above information,
your resubmission **will not be graded**.

Project 2B Submissions with two S's
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you scored two S's in your initial submission for Project 2B, but not in your
original Project 2A submission, you do not need to submit all the documentation
requested above. However, we do still need you to make a resubmission so we know
you want us to revise your Project 2A submission.

In this resubmission, you do not need to make any changes to your Project 2B
code, and can simply resubmit the exact same code you submitted in our original
Project 2B submission. All you need to do is add a ``RESUBMISSION.md`` file
with the following contents::

    Project 2 Resubmission
    ======================

    Team members:
    - TEAM MEMBER 1 (CNETID1)
    - TEAM MEMBER 2 (CNETID2)

    We earned two S's in Project 2B, but not Project 2A.

Note: If you already earned two S's in both Project 2A and 2B, do not make a resubmission
(it will be ignored). If you have questions about any of the feedback you received,
please post a question on Ed.

Submitting
~~~~~~~~~~

You will submit your code through the "Project 2 (Resubmission)" assignment on Gradescope.
Other than that, you should follow the same submission instructions as in the original submissions.

Resubmission Grading
~~~~~~~~~~~~~~~~~~~~

In general, if you are making a resubmission that only involved addressing rubric items, without adding substantial
new code to your submission, there is a very high likelihood that addressing all the rubric items will bump your Code
Quality score to an S. You may leave up to two non-major rubric items unaddressed.

On the other hand, if you are making a resubmission that involves adding substantial new code, please bear in mind
that the graders could identify issues in that new code that will impact your Code Quality score. Please
make sure to carefully review the `Project 2 Rubric <project2_rubric.html>`__ so you know what the graders will be looking at.




