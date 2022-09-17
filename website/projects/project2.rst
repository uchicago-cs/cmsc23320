Project 2: chitcp
-----------------

.. warning::

   Project 2 has not yet been updated for Autumn 2022. You are welcome to read
   through the project documentation, but bear in mind that some aspects of the
   project may change. Please do not start working on the project until instructed
   to do so in class.

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

- `chiTCP specification <http://chi.cs.uchicago.edu/chitcp/>`__

  - Project 2a: `Assignment 1 <http://chi.cs.uchicago.edu/chitcp/assignment1.html>`__
  - Project 2b: `Assignment 2 <http://chi.cs.uchicago.edu/chitcp/assignment2.html>`__

- `Project 2 rubric <project2_rubric.html>`__
- `Project 2 tips <project2_tips.html>`__

Initializing your Project 2 Repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure that you have read the :ref:`Getting Started <project_started>` page
as well as the the :ref:`Project Registration <project_registration>` instructions.

**One-time setup instructions**

Only one team member needs to run these commands. Create an empty directory and, inside that
directory run the following commands. In the commands below, ``$REPO_URL`` refers to the
SSH URL of your repository. To get this URL, log into GitHub and navigate to your
project repository. Then, click on the green "Code" button, and make sure the
"SSH" tab is selected. Your repository URL should look something like this:
``git@github.com:uchicago-cmsc23320-2022-aut/chitcp-p2-jdoe-jrandom.git``

::

    git init
    git remote add origin $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chitcp.git
    git pull upstream master
    git push -u origin master


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
