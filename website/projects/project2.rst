Project 2: chitcp
-----------------

.. note::

   Project 2 has not yet been updated for Winter 2022. While you are welcome to look at last year's materials, you should not start working on them until we tell you that Project 2 is ready.

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


.. toctree::
   :maxdepth: 2
   :hidden:

   project2_tips.rst
   project2_rubric.rst
