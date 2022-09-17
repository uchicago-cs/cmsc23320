Project 3: chirouter
--------------------

.. warning::

   Project 3 has not yet been updated for Autumn 2022. You are welcome to read
   through the project documentation, but bear in mind that some aspects of the
   project may change. Please do not start working on the project until instructed
   to do so in class.

In this project you will be implementing a simple IP router capable of routing IPv4 datagrams between multiple networks. This router will have a static routing table, so you will not have to deal with implementing a routing protocol like RIP or OSPF; instead, the project will focus on the routing of IP datagrams. While, at a high level, this just involves receiving IP datagrams and figuring out what interface they should be sent on, this requires building additional functionality before you can actually start routing IP datagrams.

Please refer to the following documents to complete this project:

- `chirouter specification <http://chi.cs.uchicago.edu/chirouter/>`__
- `Project 3 rubric <project3_rubric.html>`__
- `Project 3 tips <project3_tips.html>`__

Take into account that this project requires using a network simulator that
needs to be run with root privileges on a Linux machine. If you do not have
access to such a machine, you can use the `CS Virtual Machine <https://howto.cs.uchicago.edu/vm:index>`__
(version 202122.2 or higher) to run the network simulator. This virtual
machine will only work on computers with Intel processors so, if you are running
a newer Mac with an M1 processor, please see our Ed Discussion site for instructions
on how to set up a virtual machine on your computer.

Initializing your Project 3 Repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure that you have read the :ref:`Getting Started <project_started>` page
as well as the the :ref:`Project Registration <project_registration>` instructions.

**One-time setup instructions**

Only one team member needs to run these commands. Create an empty directory and, inside that
directory run the following commands. In the commands below, ``$REPO_URL`` refers to the
SSH URL of your repository. To get this URL, log into GitHub and navigate to your
project repository. Then, click on the green "Code" button, and make sure the
"SSH" tab is selected. Your repository URL should look something like this:
``git@github.com:uchicago-cmsc23320-2022-aut/chirouter-p3-jdoe-jrandom.git``

::

    git init
    git remote add origin $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chirouter.git
    git pull upstream master
    git push -u origin master


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
