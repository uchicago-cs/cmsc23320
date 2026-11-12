Project 3 Rubric
================

The grading of this project follows a specifications grading approach. If you have not already
done so, make sure to read our `Grading <../syllabus.html#grading>`__ section of
the syllabus for more details.

This project has a single submission, for which you will receive two SNU scores:

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

Furthermore, you will complete a Pre-submission Code Review as part of this project
(see `Code Reviews`_ below).

Project Timeline
----------------

The exact timeline for the project will be the following:

.. include:: project3_timeline.txt

Unlike Projects 1 and 2, the resubmission can only be used to improve your Completeness score
(i.e., the score on the automated tests). Since Project 3 is due at the end of the quarter,
there is not enough time to do a full resubmission-regrading cycle (see `Resubmission`_ below).

Completeness
------------

The Completeness component will be determined by running the chirouter `automated tests <http://chi.cs.uchicago.edu/chirouter/automated-tests.html>`__.
Since the automated tests cannot be run on Gradescope (see the `Submission <project3.html#submission>`__ instructions),
the graders will run them manually.

Take into account that Gradescope will only fetch the files listed in the
`Submission <project3.html#submission>`__ instructions. Any changes you make
to other files will be ignored, and your code will be tested with the original
version of those files.

**NOTE**: In Project 3, you will be relying on manual testing to a greater extent
than in Projects 1 and 2. The automated tests provide a convenient way to run all
the tests and get a test score but, in general, if your code works when testing it
manually, and fails the corresponding automated test, you should consider the test
to have passed (you should make a note in the ``DOCUMENTATION.md`` file so the graders are aware
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
  router functionality, but where the functions are empty or filled with "TODO"s, etc.)

That said, while the issues listed below are the main things we care about in this project,
it is not possible for us to give you an exhaustive list of every single thing that could
affect your code quality score. If you get a comment pointing out an issue in your
code that we did not list below, take it as an opportunity to improve your work.

**Note**: We use a Claude-based tool to help identify the rubric items that likely need
attention in any given submission. While this helps ensure that no rubric items slip
through the cracks when grading your work, the grading is ultimately done by human
graders (who verify any suggestions made by this tool).

Correctness
~~~~~~~~~~~

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
- **Removing pending requests from the pending ARP request list in** ``chirouter_arp_process_pending_req`` **, instead of returning ARP_REQ_REMOVE**
- **Removing pending requests from the pending ARP request list before the request has been sent 5 times**
- **Not removing a pending ARP request when an ARP reply is received, or when it has been sent 5 times already**
- **Unconditionally sending a Time Exceeded reply if a forwardable IP datagram arrives with TTL=1**.  The correct approach is to first determine whether it is a Host Unreachable and, if it is not, then send a Time Exceeded (meaning that forwardable datagrams with TTL=1 must linger in the withheld frames list so we can determine whether there is actually a host with that IP).

Design
~~~~~~

When assessing the design of your code, we will be paying special attention
to the following:

- [Major issue] **Putting all your code in chirouter_process_ethernet_frame without dividing it into multiple functions**.
- **Writing a single massive "Process IP datagram" function, without dividing it into multiple functions.**
- **Repeating ICMP message creation logic in multiple places in your code, instead of writing a general-purpose "create an ICMP message" function**

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

Your submission must include a ``DOCUMENTATION.md`` file in the ``chirouter/`` directory of your repository
with some specific documentation about the code you have written. If you do not
include this file, your submission will automatically receive a score of Needs Improvement. If you do
include it, but the file does not provide the information we request below, this will
be treated as a major issue in your submission.

The ``DOCUMENTATION.md`` file **must** follow the template below
(the exact sections are explained further below):

.. code-block:: markdown

    Project 3
    =========

    Team members:
    - TEAM MEMBER 1 (CNETID1)
    - TEAM MEMBER 2 (CNETID2)

    Test score: XXX / YYY

    Additional functions
    --------------------
    - function1() in utils.c
    - function2() in arp.c

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
  on your computer. This will allow us to ensure that, when we run the tests, we are
  getting the same score.

- **Additional functions**: If you added new functions to ``arp.c`` or ``utils.c``,
  please list them here. You *do not* need to list every function you add to ``router.c``

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

In this project, you will have to complete a Pre-submission Code Review. You must schedule
and complete this code review no later than the due date specified in the
“Project Timeline” above (see `Code Review Scheduling Instructions <code-review-scheduling.html>`__
for instructions on how to schedule your code review). Unlike Projects 1 and 2, there is
no Feedback Code Review in Project 3.

Pre-submission Code Review
~~~~~~~~~~~~~~~~~~~~~~~~~~

The purpose of this code review is to go over your code before Project 3 is due,
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

**You do not need to wait until you have a near-complete version of Project 3 to
request this code review.** Since you will not be able to make a resubmission to improve your
Code Quality score in this project, this code review is your main opportunity to get feedback
on your code before it is graded, so we recommend you schedule it as soon as you have a
reasonably complete draft of the ICMP and ARP parts of the project.

Scoring and Other Requirements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Code reviews are graded on completion only; for the purposes of the grading Bundles
listed in the syllabus, completing a code review earns a Satisfactory, and not
completing a code review earns a Needs Improvement.

Code reviews are conducted in-person, and both students in a team must attend and
participate. Since we will ask you to walk us through your code, you may want to have
a quick conversation beforehand to decide who will explain what portions of the code.

Finally, we reserve the right to ask individual students or teams of students to
undergo additional code reviews if there are any concerns with their understanding
of their code.

Resubmission
------------

After you submit Project 3, you can make a resubmission to improve your Completeness score
(i.e., the score on the automated tests). Your Code Quality score will not change
(unless your initial submission was not a good-faith submission, as described below).

**NOTE**: To make a resubmission, you must make a "good-faith" submission by the project
deadline. A good-faith submission is any submission where it is clear you have put in
a substantial amount of effort to complete the project. Please note that scoring an N
in Completeness is a sufficient (but not necessary) requirement for a submission to
be considered a good-faith submission.

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

Required Documentation
~~~~~~~~~~~~~~~~~~~~~~

If you decide to make a resubmission, you **MUST** add a ``RESUBMISSION.md`` file
in the ``chirouter/`` directory of your repository using the following template: (the exact sections
are explained below)

.. code-block:: markdown

    Project 3 Resubmission
    ======================

    Team members:
    - TEAM MEMBER 1 (CNETID1)
    - TEAM MEMBER 2 (CNETID2)

    Original test score: XXX / YYY

    New test score: XXX / YYY

    Changes made to pass additional tests
    -------------------------------------
    <COMPLETE THIS SECTION>

Below you can find more details on each of the sections:

- **Team members**: Ordinarily, this would be the same two team members who made the original submission.
  However, if you worked individually on the resubmission (because your teammate was happy with the
  original submission, and didn't want to work further on it), please make sure to note this here.

- **Original test score** and **New test score**: Please include the test score you got in your
  original submission, and the test score you are seeing when running the tests on your computer
  with your resubmitted code.

- **Changes made to pass additional tests**: If your work only involved a few minor bug fixes,
  please let us know you did this (but you do not need to specify the exact changes you made).
  If you have written substantial new code (e.g., if your original submission did not implement
  IP forwarding), please specify the affected files and functions, as well as the new
  functionality that is added by the new code.

If you do not include a ``RESUBMISSION.md`` file with the above information,
your resubmission **will not be graded**.

Submitting
~~~~~~~~~~

You will submit your code through the "Project 3 (Resubmission)" assignment on Gradescope.
Other than that, you should follow the same submission instructions as in the original submission.
