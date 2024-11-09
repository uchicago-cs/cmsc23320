Project 3: chirouter
--------------------

In this project you will be implementing a simple IP router capable of routing IPv4 datagrams between multiple networks. This router will have a static routing table, so you will not have to deal with implementing a routing protocol like RIP or OSPF; instead, the project will focus on the routing of IP datagrams. While, at a high level, this just involves receiving IP datagrams and figuring out what interface they should be sent on, this requires building additional functionality before you can actually start routing IP datagrams.

Please refer to the following documents to complete this project:

- `chirouter specification <http://chi.cs.uchicago.edu/chirouter/>`__
- `Project 3 rubric <project3_rubric.html>`__
- `Project 3 tips <project3_tips.html>`__

Take into account that this project requires using a network simulator that
needs to be run with root privileges on a Linux machine. For students using
Windows or Mac, we provide a Docker container that you can use to run
the network simulator on your computer.

Submission Timeline
~~~~~~~~~~~~~~~~~~~

This project has one required submission, and an optional resubmission:

.. include:: project3_timeline.txt

Please see `Project 3 rubric <project3_rubric.html>`__ for more details on how your submission will be graded.

Initializing your Project 3 Repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure that you have read the :ref:`Getting Started <project_started>` page
before following the instructions below.

**One-time setup instructions**

Only one team member needs to run these commands. Create an empty directory and, inside that
directory run the following commands. In the commands below, ``$REPO_URL`` refers to the
SSH URL of your repository. To get this URL, log into GitHub and navigate to your
project repository. Then, under "Quick setup — if you’ve done this kind of thing before",
make sure the "SSH" button is selected, and copy the URL that appears next to it.
It should look something like this: ``git@github.com:uchicago-cmsc23320-aut-24/chirc-p1-jdoe-jrandom.git``

::

    git init
    git remote add origin $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chirouter.git
    git pull upstream main
    git push -u origin main


**Cloning instructions**

Once the repository has been set up, you can clone the repository in
other locations as follows::

    git clone $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chirouter.git

Submission
~~~~~~~~~~

Before submitting, make sure you've added, committed, and pushed all
your code to GitHub. You will submit your code through `Gradescope <https://gradescope.com/>`__,
which you can access through our Canvas site.

When submitting through Gradescope, you will be asked to select a repository to submit.
Make sure that you select the correct repository and branch. Please note that you can
submit as many times as you want before the deadline.

Please note that you must make a **single submission per pair of students** (do not make two submissions, one per student). When making your submission, you will be allowed to add "team members" to your submission. Make sure you add your project partner in your submission.

In this project, Gradescope will *only* fetch the following files from your repository:

- ``src/c/router.c``
- ``src/c/arp.c``
- ``src/c/utils.c``
- ``src/c/utils.h``
- The ``DOCUMENTATION.md`` file in the root of your repository

Once you submit your files, an "autograder" will run. Unlike Projects 1 and 2, the autograder will not run any automated tests, because the chirouter tests require running a Docker container with elevated privileges, which is not possible on Gradescope's autograding infrastructure. Instead, the tests will be run manually by the graders (the autograder will just build your code to ensure it builds).

.. toctree::
   :maxdepth: 2
   :hidden:

   project3_tips.rst
   project3_rubric.rst
