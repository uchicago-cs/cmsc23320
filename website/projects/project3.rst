Project 3: chirouter
--------------------

.. warning::
   This page has not yet been updated for Autumn 2024.

In this project you will be implementing a simple IP router capable of routing IPv4 datagrams between multiple networks. This router will have a static routing table, so you will not have to deal with implementing a routing protocol like RIP or OSPF; instead, the project will focus on the routing of IP datagrams. While, at a high level, this just involves receiving IP datagrams and figuring out what interface they should be sent on, this requires building additional functionality before you can actually start routing IP datagrams.

Please refer to the following documents to complete this project:

- `chirouter specification <http://chi.cs.uchicago.edu/chirouter/>`__
- `Project 3 rubric <project3_rubric.html>`__
- `Project 3 tips <project3_tips.html>`__

Take into account that this project requires using a network simulator that
needs to be run with root privileges on a Linux machine. For students using
Windows or Mac, we provide a Docker container that you can use to run
the network simulator on your computer ()

Submission Timeline
~~~~~~~~~~~~~~~~~~~

This project has one required submission, and an optional resubmission:

.. include:: project3_timeline.txt

Please see `Project 3 rubric <project3_rubric.html>`__ for more details on how each submission will be graded.

Initializing your Project 3 Repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure that you have read the :ref:`Getting Started <project_started>` page
as well as the the :ref:`Project Registration <project_registration>` instructions.

**One-time setup instructions**

Only one team member needs to run these commands. Create an empty directory and, inside that
directory run the following commands. In the commands below, ``$REPO_URL`` refers to the
SSH URL of your repository. To get this URL, log into GitHub and navigate to your
project repository. Then, under "Quick setup — if you’ve done this kind of thing before",
make sure the "SSH" button is selected, and copy the URL that appears next to it.
It should look something like this: ``git@github.com:uchicago-cmsc23320-spr-24/chirouter-jdoe-jrandom.git``

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

.. toctree::
   :maxdepth: 2
   :hidden:

   project3_tips.rst
   project3_rubric.rst
