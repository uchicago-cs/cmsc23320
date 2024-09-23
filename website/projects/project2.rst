Project 2: chitcp
-----------------

.. warning::
   This page has not yet been updated for Autumn 2024.

In this project you will be implementing the Transmission Control Protocol, as
specified in `[RFC793] <http://tools.ietf.org/html/rfc793>`__. However, instead
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
- You can find instructions on how to register for the project (and how to
  get your Git repo) in our :ref:`Project Registration <project_registration>` page.
- `chiTCP specification <http://chi.cs.uchicago.edu/chitcp/>`__: In this project,
  you will be implementing Assignments 1 and 2 of chiTCP.
- `Project 2 rubric <project2_rubric.html>`__
- `Project 2 tips <project2_tips.html>`__

Submission Timeline
~~~~~~~~~~~~~~~~~~~

This project has two required submissions, and an optional resubmission:

.. include:: project2_timeline.txt

Please see `Project 2 rubric <project2_rubric.html>`__ for more details on how each submission will be graded.

Initializing your Project 2 Repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure that you have read the :ref:`Getting Started <project_started>` page
as well as the the :ref:`Project Registration <project_registration>` instructions.

**One-time setup instructions**

Only one team member needs to run these commands. Create an empty directory and, inside that
directory run the following commands. In the commands below, ``$REPO_URL`` refers to the
SSH URL of your repository. To get this URL, log into GitHub and navigate to your
project repository. Then, under "Quick setup — if you’ve done this kind of thing before",
make sure the "SSH" button is selected, and copy the URL that appears next to it.
It should look something like this: ``git@github.com:uchicago-cmsc23320-spr-24/chitcp-jdoe-jrandom.git``

::

    git init
    git remote add origin $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chitcp.git
    git pull upstream main
    git branch -M main
    git push -u origin main


**Cloning instructions**

Once the repository has been set up, you can clone the repository in
other locations as follows::

    git clone $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chitcp.git



.. toctree::
   :maxdepth: 2
   :hidden:

   project2_tips.rst
   project2_rubric.rst
