.. _grading:

Grading
=======

This year (2022), we have overhauled the grading scheme in CMSC 23320, and are following a *specifications grading* approach. Many of you have likely not encountered specifications grading before, so we encourage you to carefully read this page to make sure you understand how it works.

Coursework Grading Scale
------------------------

Specifications grading is a learning-focused approach that prioritizes student learning over scores or grades. A key aspect of specifications grading is to provide opportunities for students to learn from their mistakes and demonstrate growth and
improvement throughout the quarter.

However, the traditional 0-100 grading scale makes it challenging for a student to understand
if their work needs improvement (and how much improvement). For example, getting 85 points out of 100 on a project could be considered an excellent
performance in one class, but a dismal score in a different class. Providing medians and quartiles may not be helpful,
as it only tells you how you performed relative to the rest of the class; again, 85 points might be an excellent score
in an absolute sense, but may lead you to believe it's a poor score because everyone else in the class happened to
do much better than you.

So, this year, your work on the projects will receive one of four discrete scores:

- **Excellent** (E): The work is either perfect, or has only very minor flaws.
- **Satisfactory** (S): While the work has some room for improvement, the student has put in a good-faith effort to complete all the work and demonstrated sufficient mastery of the material. Only minor revisions would be needed for the work to be Excellent.
- **Needs Improvement** (N): The student has put in a good-faith effort to complete the work, but revealed a lack of mastery in the material that can be addressed via concrete feedback. The work could become Satisfactory or Excellent with some major revisions.
- **Ungradable** (U): The student did not make a good-faith effort to complete the work. This includes not submitting the work at all, but also situations like submitting only placeholder code, work that barely passes any tests, etc.

This is often referred to as the ESNU scale. It is important that you avoid thinking of these scores in terms of how they map to an A, B, C, etc. (the manner in which we compute your final grade is described below). The ESNU scale is intended to help you understand your mastery of the material, so you can identify areas for improvement as the quarter progresses. Each project will include a more precise description of what is required for an E, S, N, or U.

The homeworks and the final exam will use a slightly simplified SNU scale: an answer to an individual question will be assessed as either Satisfactory (completely correct), Needs Improvement (partially correct), or Ungradable (blank or completely off-base).

Resubmissions
-------------

Another key aspect of specifications grading is lowering the stakes of any individual assignment. In other words,
a poor performance in one assignment should not tank your grade for the entire quarter, and (as noted earlier)
there should be an opportunity for you to demonstrate you've learned from those mistakes and are able to
improve your work.

One way of accomplishing this is by allowing students to submit a revised version of their work after
they've gotten feedback from the graders. This year, you will be allowed to do this for practically all
your coursework, following these general guidelines:

- After work is returned to you, you will typically have one week to submit a revised version.
- To get an E on a project, you must have made an initial good-faith submission for that project
  (i.e., work that would score an N or above). If you do not, your score on the resubmission
  will be capped at an S. In other words, you are technically allowed to treat resubmissions as, effectively,
  a weeks-long extension on the project deadline but, if you do so, you forfeit getting an E
  on the project.
- Project 3 is due on the last week of classes, which means there will not be enough time
  for us to grade it *and* allow resubmissions before grades are due. You will, however, be
  allowed to make resubmissions to improve your score on the automated tests.
- The final exam cannot be resubmitted.

Individual projects/homeworks will include specific instructions and a concrete timeline for resubmissions
in that piece of work.

Late Submissions
----------------

Late submissions will not be accepted in this class, except under extraordinary circumstances. Please bear in mind
that, given that you can resubmit almost all work in this class, you should not treat the initial deadline for
a project/homework as the date by which you must submit a perfectly polished version of your work (although
you should still aim to do so!) In other words, it is ok to submit a less-than-ideal piece of work by the
deadline, as you will have an opportunity to revise it later on.

That said, to be clear: **if you encounter some sort of emergency (medical, family, etc.) please reach out to us as soon as you are able to do so**. We are more than happy to find ways to provide additional flexibility in these situations. Ideally, you should notify us of these circumstances before the work is due so we can discuss options with you.

In other words, our late submission policy applies to *ordinary* circumstances: if you are having a busy week, if your RSO has an event that overlaps with a deadline, etc., then you should rely on the resubmission policy to give you some extra flexibility: instead of trying to argue for a few extra days to work on an assignment, you should just submit the work you have completed by the deadline, so you can get feedback on that work and use that feedback to improve your work.


Final Grade
-----------

Your final grade will be computed based on the ESNU scores you earn on the projects, homeworks, and final exam.

Your scores on the projects and homeworks will be used to compute a **base grade**, up to a maximum of a **B**.
Your scores on the final exam will then allow you to earn a +1, +2, or +3 **grade level-up**. For example, if your base
grade on the projects/homeworks is a B- and you earn a +2 grade level-up on the exam, your final grade
in the class will be a B+.

Please note that this means the final exam is optional. If you do not take the final exam, your base grade
will be your final grade in the class.

Base grade
~~~~~~~~~~

Each project contributes
two ESNU scores (one based on the automated tests for the project, and one based on manual grading of your code),
for a total of six ESNU scores for the projects. Each homework has 15 questions, each of which contributes one
SNU score, for a total of 30 SNU scores for the homeworks.

You should avoid thinking of these scores as making up some percent of your base grade. For example, the fact that
there are 30 scores for the homeworks, and 6 scores for the projects, does not mean that the homeworks are worth
83.33% of your base grade.

Instead, your base grade will be determined based on the table below, where each row specifies the minimum number of scores that you must achieve to earn that grade. You will earn the highest grade for which you meet *all* requirements.

.. cssclass:: table-bordered

+-------+-----------------+--+-----------+
|       | Projects        |  | Homeworks |
+=======+=======+=====+===+==+===========+
| Grade | N+S+E | S+E | E |  | S         |
+-------+-------+-----+---+--+-----------+
| B     | 6     | 6   | 5 |  | 27        |
+-------+-------+-----+---+--+-----------+
| B-    | 6     | 5   | 3 |  | 24        |
+-------+-------+-----+---+--+-----------+
| C+    | 6     | 4   | 0 |  | 21        |
+-------+-------+-----+---+--+-----------+
| C     | 4     | 4   | 0 |  | 18        |
+-------+-------+-----+---+--+-----------+
| C-    | 4     | 4   | 0 |  | 15        |
+-------+-------+-----+---+--+-----------+

In this table, the project columns represent the following:

- **N + S + E**: The minimum number of non-Ungradeable scores (i.e., N's, S's, and E's) achieved by the student. This represents the amount of work the student has done in good faith.
- **S + E**: The minimum number of scores that are, at least, Satisfactory. This represents the amount of work that the student has done in good faith, and which has room for only moderate/minor improvement.
- **E**: The minimum number of Excellent scores. This represents the amount of work done by the student that is of superior quality.

For the homeworks, the **S** column is the minimum number of Satisfactory scores (remember that homeworks do not use the E score, and an S represents a question that has been answered correctly).

Grade Level-up
~~~~~~~~~~~~~~

The final exam will be closed-book, closed-notes exam composed 
of 30 questions, graded on a SNU scale:

- To earn a +1 grade level-up, you must earn at least 15 S scores.
- To earn a +2 grade level-up, you must earn at least 21 S scores.
- To earn a +3 grade level-up, you must earn at least 27 S scores.

The exam will be divided into three sections:

- **"Trust but Verify"** [10 questions]. The intent of these questions is to 
  verify that you actually worked on the course projects. They should be trivial or almost
  trivial to answer for any student who has completed the projects.
- **Networks Concepts** [14 questions]. These questions will test basic mastery 
  of network concepts, and will be similar to questions found in the homework assignments.
- **Challenge Questions** [6 questions]. These questions will require a solid and 
  deep understanding of network concepts, including how different concepts relate to each other.

Of all the topics covered throughout the quarter, some of the topics will be guaranteed
to *not* appear in the Networks Concepts section, but *may* appear in the Challenge
Questions section. The exact list of topics will be announced roughly a week before the exam.

While there are many paths to reach each score threshold, we expect the most
common paths to be the following

- *+1 grade level up*: Students who have worked on the projects and have an adequate understanding
  of the concepts covered in class. For example, you could reach this level by answering 8 of the 10
  Trust but Verify questions, 7 of the 14 Networks Concepts questions, and none of the Challenge Questions. Alternatively, if you only did an adequate job on the projects (and possibly skipped some parts of them), but have a more solid understanding of network concepts, you could also reach this level by answering 4 of the 10 Trust but Verify questions, 11 of the 14 Networks Concepts questions, and none of the Challenge Questions.
- *+2 grade level up*: Students who have worked on the projects and have a solid understanding of
  most (but not necessarily all) of the concepts covered in the class. For example, you could reach this level by answering 9 of the 10 Trust but Verify Questions, 12 of the 14 Networks Concepts questions, and none of the Challenge Questions.
- *+3 grade level up*: Students who have worked on the projects, and have a thorough understanding of practically all the concepts covered in the class. To reach this level, you must correctly answer nearly all the questions in each section, with a bit of flexibility to get up to three questions wrong in the entire exam.


Pass/Fail Grading
~~~~~~~~~~~~~~~~~

You are allowed to take this class for a P, but please note that it is your responsibility to check whether
a P will confer graduating credit towards your degree. To earn a P, you must earn a base grade of C+ or above,
and at least a +1 grade level-up on the final exam. You cannot earn a P based on the projects and homework alone.

This threshold is set at this level because we expect anyone who earns a P to have submitted work for all the
projects, and to demonstrate their knowledge on a closed-book exam. The lowest threshold for doing so is a C+
base grade with a +1 grade level-up.

Grading Disputes
----------------

Except in very specific cases (described below), you cannot dispute the score assigned to you on a piece of work. The score you receive on a piece of work is meant to convey feedback on your level of mastery, and you should take it as an opportunity to understand the areas of improvement in your work. You are more than welcome to ask us for concrete advice on how to improve your work, and we are always more than happy to have those kind of conversations with students, including going over your code. On the other hand, we will not entertain requests to change your score just because you feel your work deserved a higher score.

There is one exception to this: if a grader made a factual mistake in your grading.
Please note that this only includes cases where a grader makes an erroneous
statement about your code in their feedback. It does not include cases where
you simply disagree with whether something deserves to be flagged as incorrect.

For example, suppose you receive a piece of feedback that says
"Incorrect: Function X did not check that parameter Y is greater than zero".
If function X in your code *did* perform this check, and the grader
missed this fact (and erroneously gave you that feedback), you can ask
us to review this decision. Please note that, even
if the feedback is amended, it may not affect your actual ESNU score.

We ask that you keep
these requests brief and to the point: no more than a few sentences identifying
the exact statement that the grader made and the reasons you believe the statement was mistaken, including
references to specific parts of your code (e.g., "I did check the value of the
parameter in line 107"). Focus on laying out the facts, and nothing else.

Finally, it is also your responsibility to make
these requests in a timely manner. Requests to review grading mistakes must be submitted
no later than **one week** after a graded piece of work is returned to you.
After that time, we will not consider any such requests,
*regardless of whether the request is reasonable and justified*.

Acknowledgements
----------------

This grading scheme is based on a similar scheme designed for the Autumn 2021
offering of CMSC 12100, and written by Tim Black, Hannah Morgan, Anne Rogers,
Borja Sotomayor, and Zhao Wang.