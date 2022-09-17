Project 1: chirc
----------------

.. warning::

   Project 1 has not yet been updated for Autumn 2022. You are welcome to read
   through the project documentation, but bear in mind that some aspects of the
   project may change. Please do not start working on the project until instructed
   to do so in class.

In this project, you will implement a simple Internet Relay Chat (IRC)
server called chirc. This project has three goals:

#. To learn how to program with sockets, as well as some basic concurrent programming
   (including refreshing some concepts covered in CMSC 15400)

#. To implement a system that is (partially) compliant with an
   established network protocol specification.

#. To allow you to become comfortable with high-level networking
   concepts before we move on to the lower-level concepts in this
   course.

Please refer to the following documents to complete this project:

- `chirc specification <http://chi.cs.uchicago.edu/chirc/>`__

  - Project 1a: `Assignment 1 <http://chi.cs.uchicago.edu/chirc/assignment1.html>`__
  - Project 1b: `Assignment 4 <http://chi.cs.uchicago.edu/chirc/assignment4.html>`__

- `Project 1 rubric <project1_rubric.html>`__
- `Project 1 tips <project1_tips.html>`__

Initializing your Project 1 Repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure that you have read the :ref:`Getting Started <project_started>` page
as well as the the :ref:`Project Registration <project_registration>` instructions.

**One-time setup instructions**

Only one team member needs to run these commands. Create an empty directory and, inside that
directory run the following commands. In the commands below, ``$REPO_URL`` refers to the
SSH URL of your repository. To get this URL, log into GitHub and navigate to your
project repository. Then, click on the green "Code" button, and make sure the
"SSH" tab is selected. Your repository URL should look something like this:
``git@github.com:uchicago-cmsc23320-2022-aut/chirc-p1-jdoe-jrandom.git``

::

    git init
    git remote add origin $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chirc.git
    git pull upstream master
    git push -u origin master


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
