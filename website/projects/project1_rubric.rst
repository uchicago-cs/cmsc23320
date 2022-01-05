Project 1 Rubric
----------------

.. note::

    Project 1 has not yet been updated for Winter 2022, and the rubric below refers to the old grading scheme
    we used in this class. While you are welcome to read through this page, please bear in mind that the
    grading scheme is being overhauled this year (see our `Grading <../grading.html>`__ page for more details).

This project is worth 15% of your final grade, and is divided into two parts:

* Project 1a (Assignment 1 in chirc). Worth 5% of your final grade.
* Project 1b (Assignment 4 in chirc). Worth 10% of your final grade.

The grade for each project is divided into the following components:

- Completeness (50 points)
- Correctness (10 points)
- Design (20 points) 
- Style (20 points)

Completeness
~~~~~~~~~~~~

The Completeness component of the grade will be determined by the result of running
the tests and, more specifically, on the number of points obtained when
running ``make assignment-X`` (see `Using the automated tests <http://chi.cs.uchicago.edu/chirc/testing.html#using-the-automated-tests>`_
in the chirc documentation).

Correctness
~~~~~~~~~~~

The Correctness component of the grade encompasses issues with your code that, while
not explicitly captured by the tests, could lead to *incorrect* behaviour in your server.
In project 1b, we will mostly be looking at whether you are using locks
correctly. In particular, your code must adequately protect any data that can
be accessed concurrently by more than one thread. Using a Big Fat Lock (i.e.,
using a single lock for your entire server) will result in an 8 point penalty.

However, in general, the graders may take points off for issues like the following:

- Hardcoding reply values that happen to make the tests pass, but which would fail
  under reasonable use cases (e.g., hardcoding the LUSERS values)
- Segfaults that happen under reasonable use cases (i.e., the graders won't be
  trying to make your code fail with bizarre corner cases)
- Not implementing something that is clearly specified in the project, even if
  the tests don't test for it (e.g., implementing a command almost completely,
  but not implementing one of the replies).

Please note that this section of the rubric will not re-penalize you for a failure
that is already captured by the tests. So, if your code fails to implement something
we told you to implement, but that is already captured by the tests, we would not
re-penalize you here.

Design
~~~~~~

The Design component of the grade will be determined by "qualities, many of which are intangible, 
that don’t have to do with (and exist to some extent independently of) the correct operation of your code."
(thanks to Adam Shaw for this concise phrasing). Across all three
parts of the project, we will be looking at least at the following
(the exact points for each of the parts of the project is specified
later):

* **Module/function decomposition**: We will look at whether you divided your
  implementation into modules and functions that make sense. This includes avoiding
  repeated/redundant code, ensuring that each function performs a well-defined
  task, and putting related functions in the same module (i.e., the same C file).
* **Data structure design**: We will look at whether you have designed (and/or used)
  the right data structures to store your server's state.
* **Efficiency**: We will look at whether your code is minimally efficient.
  In other words, we are not looking for sublimely efficient code but, rather,
  for the lack of grossly inefficient code. For example, we don't care whether
  you store your list of channels in a linked list (:math:`O(n)` lookup times) or a
  hash table (:math:`O(1)` lookup times), but we do care whether you iterate over a list
  in :math:`O(n^2)` time when the same task can reasonably be accomplished in
  :math:`O(n)` time (i.e., when the :math:`O(n)` is not particularly clever or relies
  on some obscure algorithm).
  
In Project 1a, we will be looking at the following:

* **Module/function decomposition** (8 points). Please note that, in this part of
  the project, it is acceptable to have all your code in a single C file (so you
  are not required to divide your implementation into multiple modules, but are
  welcome to do so). You will get at most 5 points here if your entire implementation
  is inside the main() function, without using any additional functions.
* **Data structure design** (8 points). We will specifically be looking at how you
  handle the reassembly of partitioned messages (and the data structures to support
  this).
* **Efficiency** (4 points)

In Project 1b, we will be looking at the following:

* **Module/function decomposition** (8 points). Please note that, in this part of
  the project, you *must* divide your server into multiple modules.
* **Data structure design** (8 points). We will specifically look at how you store
  information about the server state, including the list of users (and their state)
  and the list of channels (and their state).
* **Efficiency** (4 points)

Please note that we will discuss the module/function decomposition and 
the data structure design of Project 1b on Week 2's Tuesday lecture.


Style
~~~~~

The Style component of the grade will be determined by your adherence to
our `Style Guide <https://uchicago-cs.github.io/dev-guide/style_guide_c.html>`__. While you should strive to follow this guide as
closely as possible, there *are* certain aspects we will be paying more
attention to. In all three parts of the project, the 20 points of the Style 
portion are divided as follows:

- **Documenting functions** (8 points): Every function written by you must have
  a `function comment <https://uchicago-cs.github.io/dev-guide/style_guide_c.html#function-comments>`__ with a brief description
  of what the function does, and a description of the parameters and the 
  return value.
- **Consistent indentation** (2 points): Your code must follow one of the
  `allowed indentation styles <https://uchicago-cs.github.io/dev-guide/style_guide_c.html#indentation>`__ consistently.
  The presence of even a single tab character in your code will result in 0 points
  here.
- **Clarity** (6 points): Your code must be easy to read and understand. This
  is a fairly subjective aspect, but common deductions for lack of clarity
  include using variables without descriptive names, writing convoluted code
  that would be easier to understand with more code comments, using magic
  numbers, etc.
- **General adherence to the style guide** (4 points): The graders will not be
  checking that you follow every minute aspect of our style guide, and occasional
  infractions are ok (and won't necessarily be penalized). What we're more
  concerned with is that your code, overall, has a *consistent* style that
  asymptotically approaches the one specified in our style guide.

Additionally, the graders will apply the following penalties:

- Using `global variables <https://uchicago-cs.github.io/dev-guide/style_guide_c.html#global-variables>`__: 10 point penalty
- Using `goto statements <https://uchicago-cs.github.io/dev-guide/style_guide_c.html#goto-statements>`__: 5 point penalty

Please note that the style guide does specify a few exceptions when using
some of the above is acceptable. You will not be penalized in those cases.


Additional Penalties
~~~~~~~~~~~~~~~~~~~~

.. include:: additional_penalties.txt



