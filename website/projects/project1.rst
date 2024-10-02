Project 1: chirc
----------------

In this project, you will implement a simple Internet Relay Chat (IRC)
server called chirc. This project has three goals:

#. To learn how to program with sockets, as well as some basic concurrent programming
   (including refreshing some concepts covered in CMSC 14300/14400 or 15400)

#. To implement a system that is (partially) compliant with an
   established network protocol specification.

#. To allow you to become comfortable with high-level networking
   concepts before we move on to the lower-level concepts in this
   course.

Please refer to the following documents to complete this project:

- Make sure you've read our :ref:`Getting Started <project_started>` page.
  That page also includes instructions on how to register for the project (and how to
  get your Git repo)
- `chirc specification <http://chi.cs.uchicago.edu/chirc/>`__: In this project,
  you will be implementing Assignments 1, 4, and 5 of chirc.
- `Project 1 rubric <project1_rubric.html>`__
- `Project 1 tips <project1_tips.html>`__

Submission Timeline
~~~~~~~~~~~~~~~~~~~

This project has the following submissions:

.. include:: project1_timeline.txt

Please see `Project 1 rubric <project1_rubric.html>`__ for more details on how each submission will be graded.

Initializing your Project 1 Repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure that you have read the :ref:`Getting Started <project_started>` page
before following the instructions below.

**One-time setup instructions**

Only one team member needs to run these commands. Create an empty directory and, inside that
directory run the following commands. In the commands below, ``$REPO_URL`` refers to the
SSH URL of your repository. To get this URL, log into GitHub and navigate to your
project repository. Then, under "Quick setup — if you’ve done this kind of thing before",
make sure the "SSH" button is selected, and copy the URL that appears next to it.
It should look something like this: ``git@github.com:uchicago-cmsc23320-aut-24/chirc-jdoe-jrandom.git``

::

    git init
    git remote add origin $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chirc.git
    git pull upstream main
    git branch -M main
    git push -u origin main

**Cloning instructions**

Once the repository has been set up, you can clone the repository in
other locations as follows::

    git clone $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chirc.git

Submission
~~~~~~~~~~

Before submitting, make sure you've added, committed, and pushed all
your code to GitHub. You will submit your code through `Gradescope <https://gradescope.com/>`__,
which you can access through our Canvas site.

When submitting through Gradescope, you will be asked to select a repository to submit.
Make sure that you select the correct repository and branch. Please note that you can
submit as many times as you want before the deadline.

In this project, Gradescope will *only* fetch the following files from your repository:

- All ``.c`` and ``.h`` files inside the ``src/`` directory (including any subdirectories you may
  have added in that directory)
- The ``CMakeLists.txt`` file in the root of your repository
- The ``DOCUMENTATION.md`` file in the root of your repository

Once you submit your files, an "autograder" will run. This autograder should produce the same test results as when you run the code yourself; if it doesn't, please let us know so we can look into it.

.. toctree::
   :maxdepth: 2
   :hidden:

   project1_tips.rst
   project1_rubric.rst
