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
operations. The specific course prerequisites are:

- Undergraduate students: CMSC 15400 Introduction to Computer Systems
- MPCS students: MPCS 51040 C Programming or 51100 Advanced Programming.

Course organization
-------------------

The development of three programming projects accounts for the majority
of the grade in this course. To successfully complete these projects,
students must master fundamental concepts and skills in networking. The
class meets two times a week for lectures that provide a conceptual
scaffolding for the projects, but will also cover material that is not
directly applied in the projects. Some lectures will also be dedicated to
in-depth discussion of the projects.

Besides the projects, students will also be evaluated with
two homeworks and a final exam. The course calendar, including the contents of
each lecture and project deadlines, is shown in the `Course Calendar <calendar.html>`_ page.

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

Homeworks
~~~~~~~~~

Many of the lectures (both live and pre-recorded) will cover material that is
not directly applied in the projects. Your mastery of this material will be
tested via two homework assignments where you will have to answer questions that involve
reasoning about the material covered in the lectures (e.g., exercises where
you must apply the concepts covered in the lectures, as opposed to questions
that ask you to repeat facts).

Exam
~~~~

During Finals Week, we will hold a closed-book exam that will test students'
knowledge of the material covered in the lectures, as well as the course projects.

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

Please see the `Grading <grading.html>`__ page.


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

Academic Honesty
~~~~~~~~~~~~~~~~

We take academic honesty **very** seriously in this class. Please make sure to
read our `Academic Honesty <academic-honesty.html>`__ page.


Code of Conduct for Course Staff
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This class has a `Code of Conduct for Course Staff <code-of-conduct.html>`__.
We share this code of conduct with you (the students) so you know the
expectations we have set for our staff and, while we expect and hope they
will scrupulously follow this code of conduct, you should let us know if
you witness or experience a code of conduct violation. This will allow us
to continue to improve the student experience in this class, and to prevent
any issues from reocurring.


Diversity statement
~~~~~~~~~~~~~~~~~~~

The University of Chicago is committed to diversity and rigorous inquiry that arises from multiple
perspectives. We concur with that commitment and also believe that we have the highest quality
interactions and can creatively solve more problems when we recognize and share our diversity. We thus
expect to maintain a productive learning environment based upon open communication, mutual respect,
and non-discrimination. We view the diversity that students bring to this class as a resource, strength and
benefit. It is our intent to present materials and activities that are respectful of diversity: gender,
sexuality, disability, socioeconomic status, ethnicity, race, religious background, and immigration status.
Any suggestions as to how to further such a positive and open environment in the class will be
appreciated and given serious consideration.

If you have a preferred name different from what appears on the class roster, or preferred gender pronouns
you would like us to use, please let us know.

Accessibility statement
~~~~~~~~~~~~~~~~~~~~~~~

The University of Chicago is committed to ensuring equitable access to our academic
programs and services. Students with disabilities who have been approved for the use of
academic accommodations by `Student Disability Services <https://disabilities.uchicago.edu/>`__ (SDS) and need a reasonable
accommodation(s) to participate fully in this course should follow the procedures
established by SDS for using accommodations. Timely notifications are required in order to
ensure that your accommodations can be implemented. Please meet with me to discuss
your access needs in this class after you have completed the SDS procedures for
requesting accommodations.

Phone: (773) 702-6000
Email: disabilities@uchicago.edu


Acknowledgements
----------------

This syllabus is based on previous CMSC 23300/33300 syllabi developed by
Prof. Anne Rogers and Prof. Ian Foster from the University of Chicago.

A number of policies in this class are based on similar policies from
CMSC 12100, authored by a variety of instructors throughout the years.


.. toctree::
   :maxdepth: 2
   :hidden:

   grading.rst
   academic-honesty.rst
   code-of-conduct.rst

