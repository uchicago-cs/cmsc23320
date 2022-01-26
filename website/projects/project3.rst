Project 3: chirouter
--------------------

.. note::

   Project 3 has not yet been updated for Winter 2022. While you are welcome to look at last year's materials, you should not start working on them until we tell you that Project 3 is ready.

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

   project3_tips.rst
   project3_rubric.rst
