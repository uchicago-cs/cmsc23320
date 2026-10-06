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
  That page also includes instructions on how to request your team repo.
- `chirc specification <http://chi.cs.uchicago.edu/chirc/>`__: In this project,
  you will be implementing Assignments 1, 4, and 5 of chirc.
- `Project 1 rubric <project1_rubric.html>`__
- `Project 1 tips <project1_tips.html>`__

Submission Timeline
~~~~~~~~~~~~~~~~~~~

This project has the following submissions:

.. include:: project1_timeline.txt

Please see `Project 1 rubric <project1_rubric.html>`__ for more details on how each submission will be graded.

Initializing your Team Repository for Project 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure that you have read the :ref:`Getting Started <project_started>` page
before following the instructions below.

**One-time setup instructions**

Only one team member needs to run these commands. Create an empty directory and, inside that
directory run the following commands.

In the commands below, ``$REPO_URL`` refers to the
SSH URL of your repository. To get this URL, log into the `CS GitLab server <https://gitlab.cs.uchicago.edu/>`__
and navigate to your project repository (you can also find a direct link from the
`CS Course Repositories <https://course-repos.cs.uchicago.edu>`__ website).
Then, click on the "Code" button and copy the URL that appears under "Clone with SSH".
It should look something like this: ``git@gitlab.cs.uchicago.edu:courses/aut-26/cmsc23320/cnetid1-cnetid2.git``

::

    git init
    git commit --allow-empty -m "Initial commit"
    git branch -M main
    git remote add -f origin $REPO_URL
    git remote add -f chirc-upstream https://github.com/uchicago-cs/chirc.git
    git subtree add --prefix chirc chirc-upstream main --squash
    git push -u origin main

**Cloning instructions**

Once the repository has been set up, you can clone the repository in
other locations as follows::

    git clone $REPO_URL
    git remote add chirc-upstream https://github.com/uchicago-cs/chirc.git

**Pulling changes to the upstream code**

If we make any changes to the upstream repository, and you want to merge them into your repository, you need to run the following command::

    git subtree pull --prefix chirc chirc-upstream main --squash

Submission
~~~~~~~~~~

Before submitting, make sure you've added, committed, and pushed all
your code to Git. You will submit your code through `Gradescope <https://gradescope.com/>`__,
which you can access through our Canvas site. Please see our :ref:`Submitting from GitLab <project_gitlab>` page
for details on how to submit your GitLab repository on Gradescope.

Please note that you must make a **single submission per pair of students** (do not make two submissions, one per student). When making your submission, you will be allowed to add "team members" to your submission. Make sure you add your project partner in your submission.

In this project, Gradescope will *only* fetch the following files from the ``chirc/`` directory in your repository:

- All ``.c`` and ``.h`` files inside the ``src/`` directory (including any subdirectories you may
  have added in that directory)
- The ``CMakeLists.txt`` file
- The ``DOCUMENTATION.md`` file
- The ``RESUBMISSION.md`` file (when making a resubmission)

Once you submit your files, an "autograder" will run. This autograder should produce the same test results as when you run the code yourself; if it doesn't, please let us know so we can look into it.

.. toctree::
   :maxdepth: 2
   :hidden:

   project1_tips.rst
   project1_rubric.rst
