Project 1 Rubric
================

.. warning::

   Project 1 has not yet been updated for Autumn 2022. You are welcome to read
   through the project documentation, but bear in mind that some aspects of the
   project may change. Please do not start working on the project until instructed
   to do so in class.

The grading of this project follows a specifications grading approach. If you have not already
done so, make sure to read our `Grading <../grading.html>`__ page for more details.

You will receive two ESNU scores for this project:

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

This project has two required submissions, and an optional resubmission.

The required submissions are the following:

- **Project 1a**, corresponding to Exercise 1 of the chirc project. This first submission
  also serves as sort of warm-up exercise for all the projects, to ensure you familiarize
  yourself with using a Git repo, running the automated tests, submitting through Gradescope,
  etc.
- **Project 1b**, corresponding to Exercise 4 of the chirc project (which builds upon Exercise 1)

The deadlines for the required submissions can be found in the `Course Calendar <../calendar.html>`__.

Your score on Project 1b will determine your ESNU scores on Project 1. This mean that you can also
treat Project 1b as an opportunity to revise the work you submitted as part of Project 1a (you will
get feedback on your Project 1a submission before Project 1b is due)

Please note that, to earn an E in Code Quality, you must have made an initial
good-faith submission for both Project 1a and Project 1b (i.e., work that would score an N or above).
So, for example, you could technically skip Project 1a entirely and only make a submission for
Project 1b but, if you do so, your Code Quality score will be capped at an S.

Finally, please see the "Optional Resubmission" section at the end of this page for more details on what an
optional resubmission involves.

Completeness
------------

The Completeness component will be determined by running the following command::

    make assignment-1+4

(see `Using the automated tests <http://chi.cs.uchicago.edu/chirc/testing.html#using-the-automated-tests>`_
in the chirc documentation for more details on these commands)

Your ESNU score will then be determined as follows:

+---------------------+----------------------+
| Grade               | Points on tests      |
+=====================+======================+
| Excellent           | at least 95          |
+---------------------+----------------------+
| Satisfactory        | at least 75          |
+---------------------+----------------------+
| Needs Improvement   | at least 25          |
+---------------------+----------------------+
| Ungradable          | less than 25         |
+---------------------+----------------------+


Code Quality
------------

When assessing your code quality, there are a number of things we will be paying
close attention to, and which we describe in the sections below (including major
issues, labelled "[Major Issue]" that you should be particularly mindful of).

Please note that the items below refer to a complete Project 1
implementation (i.e., Exercises 1 and 4 of the chirc project), so some of the items
will not apply to the Project 1a submission (most notably, you are not expected to use
threads or mutexes in that submission).

In general, your ESNU score will be determined as follows:

- **Excellent**: Your submission has none of the issues described below or, at most,
  has only a few minor mistakes or small style issues that would be trivial to address.
- **Satisfactory**: Your submission has a few of the issues described below (but no
  major issues), and would only require minor changes to get to an E.
- **Needs Improvement**: Your submission has several of the issues described below,
  or at least one major issue. In general, major revisions would be required to
  get up to an S or E.
- **Ungradable**: Your submission does not constitute a good-faith effort to complete
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
- [Major issue] **Not protecting access to shared data structures (list/hash of channels, users, etc.) with a mutex**
- **Using mutexes to protect access to data structures, but doing so inconsistently** (e.g., locking the mutex only when writing to a data structure, and not when reading).
- **Using mutexes to protect access to data structures, but not to socket accesses**. See `Inadequate locking <project1_tips.html#inadequate-locking>`__ in the Project 1 tips for more details.
- [Major issue] **Using a Big Fat Lock** (i.e., using a single mutex lock for the entire server).


Design
~~~~~~

When assessing the design of your code, we will be paying special attention
to the following:

* **How you reassemble incoming messages**: You should have some sort of array
  for assembling the next message that will be processed, separate from the buffer
  you pass to the ``recv()`` function (which cannot be a 1-byte array; using a 1-byte
  array when calling ``recv()`` is considered a major issue).
* **How you process IRC commands**: Ideally, you should use some sort of dispatch
  table data structure (as described in the `Project 1 Tips <project1_tips.html>`__)
  instead of a long sequence of "if command == JOIN then...", "if command == PRIVMSG then",
  etc. blocks of code.
* **How you store server data**. You should ideally use some sort of "server context"
  structure, which we will discuss in the Project 1b lecture in Week 2.
* **Module/function decomposition**. We will look at whether you divided your implementation
  into modules and functions that make sense. This includes avoiding repeated/redundant code,
  ensuring that each function performs a well-defined task, and putting related functions in the
  same module (i.e., the same C file). Please note that there are two potential major issues
  in this regard:

  * [Major Issue] **Putting all your code in a single main() function**
  * [Major Issue (in Project 1b)] **Putting all your code in a single C file**. Please
    note that this is ok in Project 1a.

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


Other Code Quality Issues
~~~~~~~~~~~~~~~~~~~~~~~~~

There are a couple of other issues that we care about across all projects:

.. include:: additional_penalties.txt


Optional Resubmission
---------------------

When you receive your graded Project 1b, you have two options:

#. If you are satisfied with the scores you have received, no action is necessary on your end.
   Your scores on Project 1b will be used to compute your `Base Grade <../grading.html#base-grade>`__.
#. You may make an *optional* resubmission to address any feedback you received in Project 1b,
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
    
- **Substantial new code added to your submission**: If you added substantial new code that was not present in your
  original submission (e.g., if your original submission did not implement several commands, and you have now included
  new code to implement those commands), you must specify the affected files, as well as the new functionality that
  is added by the new code. For example, you could include something like this::
  
    New files: channel.c/channel.h
    Modified files: ctx.h, handlers.c
  
    Channels: Added a channel hash table to ctx_t (in ctx.h) and a channel_t struct 
              (in channel.h) to add support for channels.
              
    JOIN and PART: Implemented the handlers for these commands in handlers.c
    
    QUIT: Updated the QUIT handler to relay the QUIT to users on the same channel as the user.
  
- **Changes made to pass additional tests**: If you made changes to your code with the goal of passing more tests,
  please specify your original test score, and the new test score. If your work only involved a few minor bug fixes,
  please let us know you did this (but you do not need to specify the exact changes you made). On the other hand, 
  if you skipped parts of Project 1b in your original submission, and have written entirely new code, please make 
  sure you have specified this as part of the "substantial new code", and that you also specify that doing so
  allowed you to pass additional tests.
- **Other changes**: If you made other changes to your code, such as refactoring large parts of your code, make
  sure to specify this too.

You should consider the ``README`` file as important as the changes you are making to your code: resubmissions 
that do not include the information requested above may not be graded at all.

In general, if you are making a resubmission that only involved addressing rubric items, without adding substantial
new code to your submission, there is a high likelihood that addressing all the rubric items will bump your Code
Quality score to at least the next score.

On the other hand, if you are making a resubmission that involves adding substantial new code, please bear in mind
that the graders could identify issues in that new code that will impact your Code Quality score. That said,
once you receive the resubmission grading, you will be given the option to revert back to your original Project 1b
score if you prefer.




