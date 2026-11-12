Project 3: chirouter
--------------------

In this project you will be implementing a simple IP router capable of routing IPv4 datagrams between multiple networks. This router will have a static routing table, so you will not have to deal with implementing a routing protocol like RIP or OSPF; instead, the project will focus on the routing of IP datagrams. While, at a high level, this just involves receiving IP datagrams and figuring out what interface they should be sent on, this requires building additional functionality before you can actually start routing IP datagrams.

Please refer to the following documents to complete this project:

- Make sure you've read our :ref:`Getting Started <project_started>` page.
  That page also includes instructions on how to request your team repo.
- `chirouter specification <http://chi.cs.uchicago.edu/chirouter/>`__: In this project,
  you will be implementing the entire chirouter assignment.
- `Project 3 rubric <project3_rubric.html>`__
- `Project 3 tips <project3_tips.html>`__

Take into account that this project requires using a network simulator (Mininet) that
needs to be run with root privileges on a Linux machine. To make this easier, we provide
a Docker container that you will use to run the network simulator on your computer
(regardless of whether you are using Linux, macOS, or Windows). The chirouter documentation
explains how to `install and run <http://chi.cs.uchicago.edu/chirouter/installing.html>`__
chirouter and the Docker container.

Project Timeline
~~~~~~~~~~~~~~~~

This project has the following timeline:

.. include:: project3_timeline.txt

Please see `Project 3 rubric <project3_rubric.html>`__ for more details on how your submission will be graded.

Initializing your Team Repository for Project 3
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure that you have read the :ref:`Getting Started <project_started>` page
before following the instructions below.

**One-time setup instructions**

Only one team member needs to run these commands. In the commands below, ``$REPO_URL`` refers to the
SSH URL of your repository. To get this URL, log into the `CS GitLab server <https://gitlab.cs.uchicago.edu/>`__
and navigate to your project repository (you can also find a direct link from the
`CS Course Repositories <https://course-repos.cs.uchicago.edu>`__ website).
Then, click on the "Code" button and copy the URL that appears under "Clone with SSH".
It should look something like this: ``git@gitlab.cs.uchicago.edu:courses/aut-26/cmsc23320/cnetid1-cnetid2.git``

If you are working with the same partner as in Project 2, you will add the chirouter code
to your existing team repository. Inside your local copy of that repository,
run the following commands::

    git pull
    git remote add -f chirouter-upstream https://github.com/uchicago-cs/chirouter.git
    git subtree add --prefix chirouter chirouter-upstream main --squash
    git push

If you are working with a new partner, you will first need to request a new team repo
(see the :ref:`Getting Started <project_started>` page). Then, create an empty directory and,
inside that directory, run the following commands::

    git init
    git commit --allow-empty -m "Initial commit"
    git branch -M main
    git remote add -f origin $REPO_URL
    git remote add -f chirouter-upstream https://github.com/uchicago-cs/chirouter.git
    git subtree add --prefix chirouter chirouter-upstream main --squash
    git push -u origin main

**Cloning instructions**

Once the repository has been set up, you can clone the repository in
other locations as follows (if you already have a local copy of your
team repository, just run ``git pull`` instead of ``git clone``)::

    git clone $REPO_URL
    git remote add chirouter-upstream https://github.com/uchicago-cs/chirouter.git

**Pulling changes to the upstream code**

If we make any changes to the upstream repository, and you want to merge them into your repository, you need to run the following command::

    git subtree pull --prefix chirouter chirouter-upstream main --squash

Submission
~~~~~~~~~~

Before submitting, make sure you've added, committed, and pushed all
your code to Git. You will submit your code through `Gradescope <https://gradescope.com/>`__,
which you can access through our Canvas site. Please see our :ref:`Submitting from GitLab <project_gitlab>` page
for details on how to submit your GitLab repository on Gradescope.

Please note that you must make a **single submission per pair of students** (do not make two submissions, one per student). When making your submission, you will be allowed to add "team members" to your submission. Make sure you add your project partner in your submission.

In this project, Gradescope will *only* fetch the following files from the ``chirouter/`` directory in your repository:

- ``src/c/router.c``
- ``src/c/arp.c``
- ``src/c/utils.c``
- ``src/c/utils.h``
- The ``DOCUMENTATION.md`` file
- The ``RESUBMISSION.md`` file (when making a resubmission)

Once you submit your files, an "autograder" will run. Unlike Projects 1 and 2, the autograder will not run any automated tests, because the chirouter tests require running a Docker container with elevated privileges, which is not possible on Gradescope's autograding infrastructure. Instead, the tests will be run manually by the graders (the autograder will just build your code to ensure it builds, and will check that you have included a ``DOCUMENTATION.md`` file).

.. toctree::
   :maxdepth: 2
   :hidden:

   project3_tips.rst
   project3_rubric.rst
