Project 1: chirc
----------------

.. warning::
   This page has not yet been updated for Autumn 2024.

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
- You can find instructions on how to register for the project (and how to
  get your Git repo) in our :ref:`Project Registration <project_registration>` page.
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
as well as the :ref:`Project Registration <project_registration>` instructions
before following the instructions below.

**One-time setup instructions**

Only one team member needs to run these commands. Create an empty directory and, inside that
directory run the following commands. In the commands below, ``$REPO_URL`` refers to the
SSH URL of your repository. To get this URL, log into GitHub and navigate to your
project repository. Then, under "Quick setup — if you’ve done this kind of thing before",
make sure the "SSH" button is selected, and copy the URL that appears next to it.
It should look something like this: ``git@github.com:uchicago-cmsc23320-spr-24/chirc-jdoe-jrandom.git``

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

.. toctree::
   :maxdepth: 2
   :hidden:

   project1_tips.rst
   project1_rubric.rst
