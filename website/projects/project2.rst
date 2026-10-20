Project 2: chitcp
-----------------

In this project you will be implementing the Transmission Control Protocol, as
specified in `[RFC9293] <http://tools.ietf.org/html/rfc9293>`__. However, instead
of implementing it inside the operating system itself, you will be implementing
it inside a system called chiTCP. This system allows you to write socket-based
applications that rely on your TCP implementation instead of the one included
in your operating system. To do this, chiTCP provides an alternate socket
library, chisocket, that provides the same functions as the standard socket
library (``connect``, ``send``, ``recv``, etc.). Although the chisocket
functions have the same expected behaviour as the standard socket functions,
they do not implement the entire functionality provided by standard sockets
(e.g., non-blocking sockets are not supported).

Please refer to the following documents to complete this project:

- Make sure you've read our :ref:`Getting Started <project_started>` page.
  That page also includes instructions on how to request your team repo.
- `chiTCP specification <http://chi.cs.uchicago.edu/chitcp/>`__: In this project,
  you will be implementing Assignments 1 and 2 of chiTCP.
- `Project 2 rubric <project2_rubric.html>`__
- `Project 2 tips <project2_tips.html>`__

Project Timeline
~~~~~~~~~~~~~~~~

This project has the following timeline:

.. include:: project2_timeline.txt

Please see `Project 2 rubric <project2_rubric.html>`__ for more details on how each submission will be graded.

Initializing your Team Repository for Project 2
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

If you are working with the same partner as in Project 1, you will add the chiTCP code
to your existing team repository. Inside your local copy of that repository,
run the following commands::

    git pull
    git remote add -f chitcp-upstream https://github.com/uchicago-cs/chitcp.git
    git subtree add --prefix chitcp chitcp-upstream main --squash
    git push

If you are working with a new partner, you will first need to request a new team repo
(see the :ref:`Getting Started <project_started>` page). Then, create an empty directory and,
inside that directory, run the following commands::

    git init
    git commit --allow-empty -m "Initial commit"
    git branch -M main
    git remote add -f origin $REPO_URL
    git remote add -f chitcp-upstream https://github.com/uchicago-cs/chitcp.git
    git subtree add --prefix chitcp chitcp-upstream main --squash
    git push -u origin main

**Cloning instructions**

Once the repository has been set up, you can clone the repository in
other locations as follows (if you already have a local copy of your
team repository, just run ``git pull`` instead of ``git clone``)::

    git clone $REPO_URL
    git remote add chitcp-upstream https://github.com/uchicago-cs/chitcp.git

**Pulling changes to the upstream code**

If we make any changes to the upstream repository, and you want to merge them into your repository, you need to run the following command::

    git subtree pull --prefix chitcp chitcp-upstream main --squash

Submission
~~~~~~~~~~

Before submitting, make sure you've added, committed, and pushed all
your code to Git. You will submit your code through `Gradescope <https://gradescope.com/>`__,
which you can access through our Canvas site. Please see our :ref:`Submitting from GitLab <project_gitlab>` page
for details on how to submit your GitLab repository on Gradescope.

Please note that you must make a **single submission per pair of students** (do not make two submissions, one per student). When making your submission, you will be allowed to add "team members" to your submission. Make sure you add your project partner in your submission.

In this project, Gradescope will *only* fetch the following files from the ``chitcp/`` directory in your repository:

- ``src/chitcpd/tcp.h``
- ``src/chitcpd/tcp.c``
- ``src/libchitcp/multitimer.c`` (Project 2B only)
- ``include/chitcp/multitimer.h`` (Project 2B only)
- The ``DOCUMENTATION.md`` file
- The ``RESUBMISSION.md`` file (when making a resubmission)

Once you submit your files, an "autograder" will run. This autograder should produce the same test results as when you run the code yourself; if it doesn't, please let us know so we can look into it.

.. toctree::
   :maxdepth: 2
   :hidden:

   project2_tips.rst
   project2_rubric.rst
