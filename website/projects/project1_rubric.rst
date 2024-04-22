Project 1 Rubric
================

The grading of this project follows a specifications grading approach. If you have not already
done so, make sure to read our `Grading <../syllabus.html#grading>`__ section of
the syllabus for more details.

This project has two submissions: Project 1A and Project 1B. You will receive two SNU scores
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

This project also has a "Warm-up" submission. This submission does not contribute
to your final grade but, if you complete it, you will be more likely to get an S in Project 1A.
To complete the "Warm-up" submission, you must score at least 90/100 points on the autograder
for that submission.

Submission Timeline
-------------------

The exact timeline of submissions will be the following:

.. include:: project1_timeline.txt

You will receive some early feedback from the Project 1 Warm-up before Project 1A is due.

Project 1A will likely not be graded until after Project 1B is due. Once Project 1B is graded,
you will have an opportunity to make a resubmission for Project 1A and/or 1B (and, at that point,
you will have feedback for both Project 1A and 1B). We will
post more details about the resubmission process at a later time.

Completeness
------------

The Completeness components will be determined by running the following commands:

- Project 1 Warm-up::

    make assignment-1

- Project 1A::

    make assignment-1+4

- Project 1B::

    make assignment-5

(see `Using the automated tests <http://chi.cs.uchicago.edu/chirc/testing.html#using-the-automated-tests>`_
in the chirc documentation for more details on these commands)

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
~~~~~~~~~~~

When assessing the correctness of your code, we will be paying special attention
to the following:

**All Submissions (including Warm-up)**

- **Not checking the return value of send()**: send is not guaranteed to send the entire buffer you provide, which you can only tell by looking at the return value (Beej's Guide for Socket Programming provides a `ready-to-use solution to this <https://beej.us/guide/bgnet/html/#sendall>`__, which you're welcome to use). Of course, send could also fail, and you need to check its return value for this too.
- [Major Issue] **Not checking the return value of any socket function**.
- **Not using getaddrinfo to create the server socket**. Please note that some of the socket examples we provide (most notably the first server example, ``oneshot-single.c``) manually create the ``sockaddr`` struct for the sake of highlighting what that struct looks like, but that is not the usual way to create a server socket. You can see an example of how to create a server socket with ``getaddrinfo`` in the `server-pthreads.c <https://github.com/uchicago-cs/cmsc23320/blob/master/samples/sockets/server-pthreads.c>`__ example.
- **Not using safe string functions (strncpy vs strcpy)**: Most C string functions (strcpy, strcat, etc.) have an equivalent "safe" version (strncpy, strncat, etc.) where you can specify the maximum number of characters to copy/concatenate/etc. Use these instead to protect against accidental (or malicious) buffer overflows. Alternatively, consider using a string library like `sds <https://github.com/antirez/sds>`__
- **Treating the return of recv() as a C-string**: recv() returns the raw bytes received through the network. In a protocol like IRC, this happens to be human-readable commands, but recv() won't return a C-string (i.e., an array of characters terminated by a NULL character). It is your responsibility to add that NULL terminator if you want to manipulate the bytes returned by recv() as a C-string.
- **Hardcoding reply values that happen to make some tests pass**, but which would fail
  under reasonable use cases. Take into account that the chirc specification does allow you to
  hardcode certain replies as a stop-gap measure (e.g., hardcoding the LUSERS replies during
  connection registration, so you can make progress on those tests before you properly implement
  the LUSERS command). However, you must ultimately remove those
  hardcoded replies with a more general implementation. Finally, for avoidance of doubt,
  there are also a few spots where the specification allows you to unconditionally hardcode
  certain values; those can be left hardcoded.
- **Memory accesses that could lead to segfaults under reasonable use cases**. The graders won't be
  trying to make your code fail with bizarre corner cases but, for example, if there is a very evident
  buffer overrun in your code, that will need to be fixed.
- **Not implementing something that is clearly specified in the project**, even if
  the tests don't test for it (e.g., implementing a command almost completely,
  but not implementing one of the replies).

**Project 1A and 1B**

- [Major issue] **Not protecting access to shared data structures (channels hash table, users hash table, etc.) with a mutex**
- **Using mutexes to protect access to data structures, but doing so inconsistently** (e.g., locking the mutex only when writing to a data structure, and not when reading).
- **Using mutexes to protect access to data structures, but not to socket accesses**. See `Inadequate locking <project1_tips.html#inadequate-locking>`__ in the Project 1 tips for more details.
- [Major issue] **Using a Big Fat Lock** (i.e., using a single mutex lock for the entire server).

Design
~~~~~~

When assessing the design of your code, we will be paying special attention
to the following:

**All Submissions (including Warm-up)**

* **How you reassemble incoming messages**: You should have some sort of array
  for assembling the next message that will be processed, separate from the buffer
  you pass to the ``recv()`` function (which cannot be a 1-byte array; using a 1-byte
  array when calling ``recv()`` is considered a major issue).

**Project 1A and 1B**

* **How you parse IRC commands**: You should use the provided ``message.c`` module,
  instead of rolling out your own parsing code.
* **How you process IRC commands**: You should use the provided ``handlers.c`` module,
  instead of reinventing a message dispatching mechanism.
* **Implementing modules or structs that are already provided to you**: Make sure you
  don't reinvent the wheel: we provide a lot of scaffolding code, and you should make
  sure to use the data structures and functions provided to you.
* **Not implementing the chirc_connection_send_message function**
* **Implementing the chirc_connection_send_message function, but using it inconsistently**
  e.g., making direct calls to send() from elsewhere in your code. Your code should be
  written in such a way that `chirc_connection_send_message` is the only function
  in your entire code to call the `send` function (or some sort of `sendall` helper function)
* [Major issue] **Putting all your code inside the chirc_run function**: This is fine
  for the Project 1 Warm-up, but not once you move on to Project 1A

**Project 1B only**

* [Major issue] Using two separate thread functions to handle connections
  (one for users and another for servers), instead of having a general-purpose
  thread function that handles commands that arrive on a connection
  (regardless of whether it's a user or server connection).

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

  Note: The chirc code uses `Doxygen-style function comments <https://www.doxygen.nl/manual/docblocks.html>`__.
  These are different from the ones in the style guide, but we will also accept
  them if you want to follow that style instead.
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
~~~~~~~~~~~~~~~~~~~~~~~~~

There are a couple of other issues that we care about across all projects:

.. include:: additional_penalties.txt


Resubmission
------------

When you receive your graded Project 1B, you can make a resubmission to address
any feedback you received in Projects 1A and/or 1B. This may increase your scores
in those projects.

Note: You *cannot* make a resubmission if you got S's on both Completeness and Code Quality. If you
are in this situation and want additional feedback on your grading, please ask on Ed.

While the project is divided into two parts (1A and 1B), remember that Project 1B
builds on Project 1A, As such, you should think about your
resubmission as a final cumulative submission that addresses any remaining issues
in your Project 1A and/or 1B submissions (i.e., you should not think in terms
of making two separate resubmissions, one for 1A and another for 1B, with different
code for each submission).

Making a resubmission involves not just addressing the feedback we gave you, but
also preparing some documentation explaining the changes you made to your code.
You should consider this documentation as important as the changes you are making
to your code: **resubmissions that do not include the information requested below
WILL NOT BE GRADED**.

If you decide to make a resubmission, you **MUST** add a ``RESUBMISSION.md`` file
in the root of your repository using the following template: (the exact sections
are explained below)

.. code-block:: markdown

    Project 1 Resubmission
    ======================

    Team members:
    - TEAM MEMBER 1 (CNETID1)
    - TEAM MEMBER 2 (CNETID2)

    Resubmission for:
    [ ] Project 1A
    [ ] Project 1B

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

- **Resubmission for...**: Indicate what submission(s) should be regraded based on this code
  (see the "Submission" section below for more details).

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

  Bear in mind that the Project 1A rubric items are a subset of the Project 1B rubric items. This means that...

  - If your initial Project 1B submission already addressed a rubric item from Project 1A (and the rubric
    item was no longer selected in your graded Project 1B), it is enough to say "This rubric item was addressed
    in Project 1B"
  - If you scored an N in Code Quality in Project 1A, but then scored an S in Code Quality
    in Project 1B, you do not need to explain how you addressed each individual rubric item.
    Instead, please include the following text in this section: "We earned an S in Code Quality
    in Project 1B"

- **Rubric items you have NOT addressed**: It is also important that you let us know what rubric items you
  decided not to address, as this will expedite the work of the graders. For these rubric items, it is enough
  to provide a list of the rubric item descriptions (exactly as they appear on Gradescope)

- **Substantial new code added to your submission**: If you added substantial new code that was not present in your
  original submission (e.g., if your original submission did not implement several commands, and you have now included
  new code to implement those commands), you must specify the affected files, as well as the new functionality that
  is added by the new code. For example, you could include something like this::

    Modified files: ctx.h, handlers.c

    Locks: Added locks X, Y, and Z in chirc_ctx_t

    JOIN and PART: Implemented the handlers for these commands in handlers.c

    QUIT: Updated the QUIT handler to relay the QUIT to users on the same channel as the user.

- **Changes made to pass additional tests**: If you made changes to your code with the goal of passing more tests,
  please specify your original test score, and the new test score. If your work only involved a few minor bug fixes,
  please let us know you did this (but you do not need to specify the exact changes you made). On the other hand,
  if you skipped parts of Project 1B in your original submission, and have written entirely new code, please make
  sure you have specified this as part of the "substantial new code", and that you also specify that doing so
  allowed you to pass additional tests.
- **Other changes**: If you made other changes to your code, such as refactoring large parts of your code, make
  sure to specify this too.

Once again, if you do not include a ``RESUBMISSION.md`` file with the above information,
your resubmission **will not be graded**.

Submitting
~~~~~~~~~~

For technical reasons, there will be two separate resubmission assignments on Gradescope: "Project 1A (resubmission)"
and "Project 1B (resubmission)":

- If you want to improve your score in both Project 1A and 1B, **you must submit the same code
  to both assignments**. We will only review the code in the 1B submission, but will use the 1A
  resubmission assignment to convey your updated scores for Project 1A.
- If you only need to improve your score in one (but not both) of the assignments, submit
  your code *only* in the corresponding resubmission assignment. e.g., if you are happy with
  your Project 1A score, but want to improve your Project 1B score, then you only need to
  make a submission to the "Project 1B (resubmission)" assignment on Gradescope.

Resubmission Grading
~~~~~~~~~~~~~~~~~~~~

In general, if you are making a resubmission that only involved addressing rubric items, without adding substantial
new code to your submission, there is a very high likelihood that addressing all the rubric items will bump your Code
Quality score to an S. You may leave up to two non-major rubric items unaddressed.

On the other hand, if you are making a resubmission that involves adding substantial new code, please bear in mind
that the graders could identify issues in that new code that will impact your Code Quality score. Please
make sure to carefully review the `Project 1 Rubric <project1_rubric.html>`__ so you know what the graders will be looking at.




