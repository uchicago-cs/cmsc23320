Syllabus
========

.. admonition:: What happened to CMSC 23300 Networks and Distributed Systems?

   This class was offered for many years under a different code and name, *CMSC 23300 Networks and Distributed Systems*, despite
   the fact that it only covered Networks topics (with Distributed Systems topics covered in *CMSC 23310 Advanced Distributed
   Systems*). So, in 2020, we renamed CMSC 23300 to better reflect its contents and scope. However, other than the change in
   code and name, CMSC 23320 covers the same topics and uses the same projects as CMSC 23300.

Course description
------------------

.. include:: description.txt

**Prerequisites**: This class assumes fluency in C programming, including low-level aspects of C such as bit-level
operations. Students must complete either CMSC 15400 Introduction to Computer Systems or CMSC 14400 Systems Programming II
before taking this class.


Course organization
-------------------

The development of three programming projects accounts for the majority
of the work in this course. To successfully complete these projects,
students must master fundamental concepts and skills in networking. The
class meets two times a week for lectures that provide a conceptual
scaffolding for the projects, but will also cover material that is not
directly applied in the projects. Some lectures will also be dedicated to
in-depth discussion of the projects.

Besides the projects, students must demonstrate mastery of the material covered
in lectures and in the projects via a series of short *checkpoint exams* that take place
throughout the quarter. If a student does not pass a checkpoint exam, they will
have a chance to make up for it at the final exam.

The course calendar, including the contents of
each lecture and project deadlines, is shown in the `Course Calendar <calendar.html>`__ page.

Projects
~~~~~~~~

Throughout the quarter, students will develop three projects:

#. **chirc**: Implementing an Internet Relay Protocol (IRC)
   server (partially compliant with RFC 2810, 2811, 2812, and 2813)
   using POSIX sockets and pthreads.

#. **chiTCP**: Implementing the Transmission Control Protocol.

#. **chirouter**: Implementing an Internet router using the `Mininet network emulator <https://github.com/mininet/mininet>`_

Each project is independent from the others. Students will develop these 
projects in pairs; project groups must be formed by Monday of the
second week of the quarter.

Groups can be changed from one project to another. If your partner drops out of
the course or you feel they are not contributing to the group’s effort,
you should make the instructor aware of this.

Checkpoint Exams (and Final Exam)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There will be ten checkpoint exams throughout the quarter, each with a duration between
10 and 20 minutes. Each exam will be graded on a pass/fail basis:

- If you pass a checkpoint exam, you have demonstrated mastery of the topic covered in
  that exam, and will be exempted from that topic in the final exam.
- If you do not pass a checkpoint exam, you will get feedback on the exam, and will have
  another chance to demonstrate your mastery of that topic at the final exam.

In other words, the final exam serves **only** to provide a second chance to pass a
checkpoint exam you did not pass earlier in the quarter. This means that, if you
pass all the checkpoint exams, you will not have to take the final exam.

To get the most out of the checkpoint exams, you should treat them like **practice exams**.
While some mild preparation is fine, you should not stress out about them, and should
use them as a way to **checkpoint** your knowledge of the material (and an opportunity
to get feedback on your level of mastery). If you happen to already master the material,
there is a reward involved (you won't be "re-tested" on that material at the final),
but always remember that, if you don't pass a checkpoint exam, you will have another chance
to pass it at the final exam.

Lectures
~~~~~~~~

The course meets twice a week for lectures. In most weeks, one
of the lectures will introduce material that will be expanded upon in
pre-recorded lectures that are made available that week, and the other
lecture will focus on the course projects.

In the project-focused lectures, we will (1)
provide suggestions on how to approach the projects, (2) provide general
feedback on submitted projects, and (3) provide a general forum to
answer questions about the projects.

Discussion Sessions
~~~~~~~~~~~~~~~~~~~

Most discussion sessions will be used to hold checkpoint exams, but a
few discussion sessions will also be allocated to cover material relevant
to the projects.


Books
-----

This course has two *suggested* texts:

-  *Computer Networks: A Systems Approach*, 6th edition, Larry L.
   Peterson and Bruce S. Davie, Morgan Kaufmann 2021.

-  *TCP/IP Illustrated, Volume 1: The Protocols*, 2nd Edition, Kevin
   Fall and W. Richard Stevens, Addison-Wesley 2011.

These texts are *not* required, and most students are able to complete the
class successfully without them. However, they can be a good complement
to the lectures and projects.

Please note that *Computer Networks: A Systems Approach* is freely available
here: https://book.systemsapproach.org/

Grading
-------

.. note::

    This course uses a *specifications grading* approach. If you have gone through the
    CS 140s sequence, you are likely already familiar with what this entails. If you
    are unfamiliar with specifications grading, please read through our `Specifications Grading <specs_grading.html>`__
    page. The rest of this syllabus assumes familiarity with specifications grading.

SNU Scale
~~~~~~~~~

All work in this course will be evaluated using a S/N/U scale:

- **Satisfactory** (S): The student demonstrates sufficient mastery of the material.
- **Needs Improvement** (N): The student has put in a good-faith effort to complete the work, but revealed a lack of mastery in the material that can be addressed via concrete feedback. The work could become Satisfactory with revisions.
- **Unsatisfactory** (U): The student did not submit any work, or did not complete a sufficient portion of the work (e.g., completed less than half the work that was assigned).

Specific assignments/exams will provide concrete guidance on what is required to achieve each score.

Bundles
~~~~~~~

There are a total of 20 SNU scores in this class:

- **Projects**: There are five project submissions (1A, 1B, 2A, 2B, and 3), and each contributes two SNU
  scores: one for Completeness and one for Code Quality.
- **Checkpoint Exams**: There are ten checkpoint exams, each contributing one SNU score.

These scores are distributed into 10 bundles:

1. **Basic Network Programming**
    - Project 1A (Completeness)
    - Project 1A (Code Quality)

2. **Advanced Network Programming**
    - Project 1B (Completeness)
    - Project 1B (Code Quality)
    - Checkpoint Exam: Project 1

3. **Basic TCP**
    - Project 2A (Completeness)
    - Project 2A (Code Quality)

4. **Intermediate TCP**
    - Project 2B (Completeness)
    - Project 2B (Code Quality)
    - Checkpoint Exam: Project 2

5. **Advanced TCP**
    - Checkpoint Exam: TCP

6. **Basic Data Link / Network Layer**
    - Checkpoint Exam: Data Link Layer
    - Checkpoint Exam: Network Layer

7. **Advanced Data Link / Network Layer**
    - Project 3 (Completeness)
    - Project 3 (Code Quality)
    - Exam: Project 3

8. **DNS**
    - Checkpoint Exam: DNS

9. **Other Topics**
    - Checkpoint Exam: Wireless Networks
    - Checkpoint Exam: Other Topics

10. **Mastery of Networks**

    - Checkpoint Exam: Challenge Questions


For each bundle, there are three possible outcomes:

- **Completed**: You earned an S on every component of the bundle.
- **Attempted**: You did not earn an S on every component of the bundle,
  but earned at least an N on every component of the bundle.
- **Not Completed**: You do not meet either of the conditions above.

Final Grade
~~~~~~~~~~~

Your final grade will be based on the number of bundles you complete and attempt:

.. cssclass:: table-bordered

+-------+-----------------------+-----------------------------------------------------------------------------+
|       | Bundles               |                                                                             |
| Grade +-----------+-----------+ Additional Constraints                                                      |
|       | Attempted | Completed |                                                                             |
+=======+===========+===========+=============================================================================+
| A     | 10        | 9         | None                                                                        |
+-------+           +-----------+                                                                             |
| A-    |           | 7         |                                                                             |
+-------+-----------+-----------+                                                                             |
| B+    | 8         | 8         |                                                                             |
+-------+           +-----------+                                                                             |
| B     |           | 7         |                                                                             |
+-------+           +-----------+-----------------------------------------------------------------------------+
| B-    |           | 6         | - Must complete at least two bundles with a project components.             |
+-------+-----------+-----------+ - Must complete either the “All Together” bundle, or two exam-only bundles. |
| C+    | 6         | 6         |                                                                             |
+-------+           +-----------+                                                                             |
| C     |           | 5         |                                                                             |
+-------+           +-----------+                                                                             |
| C-    |           | 4         |                                                                             |
+-------+-----------+-----------+-----------------------------------------------------------------------------+

Your grade is meant to reflect the level of mastery you have achieved in the class:

- A-level: Mastery of all/most of the topics covered in the class
- B-level: Solid understanding of many core network concepts and their application.
- C-level: Baseline understanding of core network concepts and their application.

The grade for students whose performance does not fit into any of the rows in the above table will
be determined on a case-by-case basis.

Resubmissions
~~~~~~~~~~~~~

After a piece of work has been graded and returned to you, you will be allowed to resubmit your
work to address any feedback we have given you, and to improve your score on that work.

Project resubmissions in this class will follow these guidelines:

- Resubmissions for Project 1 will open after Project 1B is graded. i.e., there won't be two
  separate resubmissions for Projects 1A and 1B. You will have roughly one week to make your
  resubmission after Project 1B is returned to you.
- Same as above, but for Project 2.
- Project 3 is due on the last week of classes, which means there will not be enough time
  for us to grade it *and* allow resubmissions before grades are due. You will, however, be
  allowed to make resubmissions to improve your score on the Completeness score (i.e., the automated tests).

Individual projects will include specific instructions and a concrete timeline for resubmissions
in that project.

Checkpoint Exams are effectively "resubmitted" at the Final Exam.
For avoidance of doubt, the Final Exam will not involve the exact same questions as the Checkpoint Exams
(but will generally test the same concepts/skills).


Asking questions
----------------

The preferred form of support for this course is through `Ed Discussion <https://edstem.org/>`__
, an on-line discussion service which can be
used to ask questions and share useful information with your classmates.
Students will be added to an Ed Discussion site at the start of the quarter,
and you will be able to access it through Canvas.

All questions regarding assignments or material covered in class must be
sent to Ed Discussion, and not directly to the instructors or TAs, as this
allows your classmates to join in the discussion and benefit from the
replies to your question. If you send a message directly to the
instructor or the TAs, you will get a gentle reminder that your question
should be asked on Ed Discussion.

Please see the `Asking Questions <https://uchicago-cs.github.io/student-resource-guide/getting-help/questions.html>`__
page in the `UChicago CS Student Resource Guide <https://uchicago-cs.github.io/student-resource-guide/>`__
for guidelines and policies related to asking questions on Ed Discussion.

Please note that all course announcements will be made through Ed Discussion. It
is your responsibility to check Ed Discussion often to see if there are any
announcements.


Commit Messages
---------------

Commit messages in your repository should be descriptive and to the point. For example:

- ``Implemented JOIN command``
- ``Fixed bug in handling of FIN when send buffer is not empty``
- ``Final style updates before submission``

Bear in mind that, in an actual project in industry, your commit messages will be seen by everyone
involved in the project, and are an important part of your documentation (as the describe exactly
how your code changed in each commit).

That said, a long-standing tradition in this class has been to collect the best and funniest
commit messages we see throughout the quarter, so we can share those (anonymized) messages with the rest of the class, to
the point that many students will write intentionally funny messages to make it into that "best of"
presentation (past presentations can be found `here <https://www.slideshare.net/bsotomay>`__).

If you do not want your commit messages included in this presentation, please let the instructor know
(or, even better, simply take care to write commit messages that are descriptive and to the point, as
shown above).


Policies
--------

Project Late Policy
~~~~~~~~~~~~~~~~~~~

Late submissions will not be accepted in this class, except under extraordinary circumstances. Please bear in mind that the grading scheme is set up to absorb a reasonable amount of subpar work, and also allows you to resubmit almost all the work in this class.

To get the most out of this class, you should not treat the initial deadline for
a project as the date by which you must submit a perfectly polished version of your work (although
you should still aim to do so!) In other words, it is ok to submit a less-than-ideal piece of work by the
deadline, as you will have an opportunity to revise it later on.

That said, to be clear: **if you encounter some sort of emergency (medical, family, etc.) please reach out to us as soon as you are able to do so**. We are more than happy to find ways to provide additional flexibility in these situations. Ideally, you should notify us of these circumstances before the work is due so we can discuss options with you.

In other words, our late submission policy applies to *ordinary* circumstances: if you are having a busy week, if your RSO has an event that overlaps with a deadline, etc., then you should rely on the resubmission policy to give you some extra flexibility. Instead of trying to argue for a few extra days to work on an assignment, you should just submit the work you have completed by the deadline, so you can get feedback on that work and use that feedback to improve your work.

Missing Checkpoint Exams
~~~~~~~~~~~~~~~~~~~~~~~~

While we understand that some students may have legitimate reasons to miss a checkpoint exam
(illness, travel to academic events, etc.), it is unfortunately not logistically feasible
for us to schedule make-up exams for every checkpoint exam.

As such, except for approved SDS accommodations, **you can only take a checkpoint exam at its
scheduled time**. If you are unable to take the exam at that time, the mechanism to make up
for that missing exam is to complete the corresponding portion of the final exam. Additionally,
we will share the exam questions (and solutions) with the class after each exam is graded,
so you will still be able to use those to prepare for the final exam.

Please remember that these checkpoint exams are effectively optional: if you do not pass
a checkpoint exam (or are unable to take it), you get a "do-over" at the final exam.

To be clear, we will be more flexible at the final exam if someone has a legitimate reason
for not being able to take the final exam at the time scheduled by the Registrar.

Grade Disputes
~~~~~~~~~~~~~~

Except in very specific cases (described below), you cannot dispute
the score assigned to you on a piece of work. The score you receive on
a piece of work is meant to convey feedback on your level of mastery,
and you should take it as an opportunity to understand the areas of
improvement in your work. You are more than welcome to ask us for
concrete advice on how to improve your work; we are always more
than happy to have those kind of conversations with students,
including going over your code. On the other hand, we will not
entertain requests to change your score just because you feel your
work deserved a higher score.

There is one exception to this: if a grader made a factual mistake in
your grading. Please note that this only includes cases where a grader
makes an erroneous statement about your code in their feedback. It
does not include cases where you simply disagree with whether
something deserves to be flagged as incorrect.

For example, suppose you receive a piece of feedback that says
“Incorrect: Function X did not check that parameter Y is greater than
zero”. If function X in your code did perform this check, and the
grader missed this fact (and erroneously gave you that feedback), you
can ask us to review this decision. Please note that, even if the
feedback is amended, it may not affect your actual SNU score.

We ask that you keep these requests brief and to the point: no more
than a few sentences identifying the exact statement that the grader
made and the reasons you believe the statement was mistaken, including
references to specific parts of your code (e.g., “I did check the
value of the parameter in line 107”). Focus on laying out the facts,
and nothing else.

Finally, it is also your responsibility to make these requests in a
timely manner. Requests to review grading mistakes must be submitted
no later than one week after a graded piece of work is returned to
you. After that time, we will not consider any such requests,
regardless of whether the request is reasonable and justified.


Policy on Academic Honesty
~~~~~~~~~~~~~~~~~~~~~~~~~~

We take academic honesty very seriously in this class. The
University of Chicago has a `formal policy on academic honesty
<http://college.uchicago.edu/advising/academic-integrity-student-conduct>`_
that you are expected to adhere to.

Our `Academic Honesty <honesty.html>`__ page provides specific policies
for this course.  Please make sure to read it! Please also pay
special attention to the `Policy on Generative AI <honesty.html#policy-on-generative-ai>`__.

Please note: if you are found in violation of our `academic honesty
policy <honesty.html>`__, either through sharing or through copying,
the effect on your grade will be severe. At minimum, your final course
grade will drop one full step (letter). At maximum, you will receive
an F in the course.  Furthermore, please note that the instructors are
required to report all infractions to the College. If you violate our
academic honesty policy, you may be subject to further penalty or
disciplinary action by the College.

Code of Conduct for Course Staff
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This class has a `Code of Conduct for Course Staff <code-of-conduct.html>`__.
We share this code of conduct with you (the students) so you know the
expectations we have set for our staff and, while we expect and hope they
will scrupulously follow this code of conduct, you should let us know if
you witness or experience a code of conduct violation. This will allow us
to continue to improve the student experience in this class, and to prevent
any issues from reoccurring.


Accessibility Statement
~~~~~~~~~~~~~~~~~~~~~~~

The University of Chicago is committed to ensuring equitable access to our academic
programs and services. Students with disabilities who have been approved for the use of
academic accommodations by `Student Disability Services <https://disabilities.uchicago.edu/>`__ (SDS) and need a reasonable
accommodation(s) to participate fully in this course should follow the procedures
established by SDS for using accommodations. Timely notifications are required in order to
ensure that your accommodations can be implemented. Please contact Víctor Almaraz Argueta, the Course Coordinator, to discuss
your access needs in this class after you have completed the SDS procedures for
requesting accommodations.

- Phone: (773) 702-6000
- Email: disabilities@uchicago.edu

Acknowledgements
----------------

This syllabus is based on previous CMSC 23300/33300 syllabi developed by
Prof. Anne Rogers and Prof. Ian Foster from the University of Chicago.

A number of policies in this class are based on similar policies from
CMSC 12100 and CMSC 14200, authored by a variety of instructors throughout the years.


.. toctree::
   :maxdepth: 2
   :hidden:

   grading.rst
   academic-honesty.rst
   code-of-conduct.rst

