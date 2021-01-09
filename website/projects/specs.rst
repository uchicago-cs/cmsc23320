Project Specifications
----------------------

Project 1: chirc
~~~~~~~~~~~~~~~~

.. note::

   Project 1 has not yet been updated for Winter 2021. While you are welcome to look at last year's materials, you should not start working on them until we tell you that Project 1 is ready.

In this project, you will implement a simple Internet Relay Chat (IRC)
server called chirc. This project has three goals:

#. To learn how to program with sockets, as well as some basic concurrent programming
   (including refreshing some concepts covered in CMSC 15400)

#. To implement a system that is (partially) compliant with an
   established network protocol specification.

#. To allow you to become comfortable with high-level networking
   concepts before we move on to the lower-level concepts in this
   course.

The project specification is available `here <http://chi.cs.uchicago.edu/chirc/>`__. Please
note that you will be implementing the following "assignments" from the chirc specification:

- Project 1a: Assignment 1
- Project 1b: Assignment 4
- Project 1c: Assignment 5

Make sure you read the `Project 1 rubric <project1_rubric.html>`__ and the `Project 1 tips <project1_tips.html>`__.

Project 2: chitcp
~~~~~~~~~~~~~~~~~

.. note::

   Project 2 has not yet been updated for Winter 2021. While you are welcome to look at last year's materials, you should not start working on them until we tell you that Project 2 is ready.

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

The project specification is available `here <http://chi.cs.uchicago.edu/chitcp/>`__.

Make sure you read the `Project 2 rubric <project2_rubric.html>`__ and the `Project 2 tips <project2_tips.html>`__.


Project 3: chirouter
~~~~~~~~~~~~~~~~~~~~

.. note::

   Project 3 has not yet been updated for Winter 2021. While you are welcome to look at last year's materials, you should not start working on them until we tell you that Project 3 is ready.

In this project you will be implementing a simple IP router capable of routing IPv4 datagrams between multiple networks. This router will have a static routing table, so you will not have to deal with implementing a routing protocol like RIP or OSPF; instead, the project will focus on the routing of IP datagrams. While, at a high level, this just involves receiving IP datagrams and figuring out what interface they should be sent on, this requires building additional functionality before you can actually start routing IP datagrams.

The project specification is available `here <http://chi.cs.uchicago.edu/chirouter/>`__.

Make sure you read the `Project 3 rubric <project3_rubric.html>`__ and the `Project 3 tips <project3_tips.html>`__.

Take into account that this project requires using a network simulator that
needs to be run with root privileges on a Linux machine. If you do not have
access to such a machine, you can use the `CS Virtual Machine <https://howto.cs.uchicago.edu/vm:index>`__
(version 201920.2 or higher) to run the network simulator.


.. toctree::
   :maxdepth: 2
   :hidden:

   project1_tips.rst
   project1_rubric.rst
   project2_tips.rst
   project2_rubric.rst
   project3_tips.rst
   project3_rubric.rst
