Academic Integrity in CMSC 23320
================================

**(or, how to get the most out of CMSC 23320)**

In this class, we assume that you are an intellectually curious
individual who has an earnest desire to learn. We believe you care about
your education and are committed to getting the most out of this course.
More specifically, our goal is for you to learn how to:

-  ...implement multithreaded client/server applications using sockets.
-  ...interpret existing specifications of network protocols, and
   translate them into code.
-  ...design and combine network protocols that form the foundation of the
   Internet.
-  ...develop complex software starting from an existing codebase, working
   collaboratively with other developers, and using industry-standard
   tools, including generative AI.

We trust that you are excited to learn all this and, to that end, we
have designed coursework and policies that will support your learning.

For example, in Project 1 we ask you to implement a standards-compliant
IRC chat server in C. We are not asking you to do this because the world
needs more IRC chat servers, but because working on this project will
help you learn how to take an existing network protocol and turn it into
functional, standards-compliant code. We also ask you to implement this
server using sockets and threads, both essential tools in network
programming.

On top of that, the projects are designed to approximate the experience
of working on a real software project. For example, software development
is an inherently collaborative activity, and we require you to work in
pairs so you can learn how to work well with other developers, including
through the use of collaborative tools like Git. We also require that
you work within an existing codebase because, in most software projects,
you will have to work with existing code, instead of writing a solution
completely from scratch.

While there are many activities in this class that will contribute to
your learning, there are actions you could take that hinder your
learning, or even actively harm it. For example, if you ask a classmate
(other than your project partner) or a Generative AI system to write the
code that implements some part of the IRC standard in Project 1, you are
depriving yourself of the opportunity to develop that skill for
yourself. You are short-circuiting your learning in this class, and you
are not getting what you’re supposed to get out of this class.

To that end, this document provides guidance on what activities are
allowed because they will benefit your learning, and which ones will not
be allowed because they will be detrimental to your learning (and, in
some cases, even morally reprehensible). As you read through the rest of
this document, we encourage you to reflect on how your actions in this
course will contribute to your learning, instead of treating these
guidelines as rules to follow “just because the professor said so”.

What is Allowed
---------------

This section describes a number of activities that we allow in this
class, because they align with the learning objectives of this class.
When reading through them, take into account that some of them come with
caveats, and may require providing some sort of citation in your code.

Acceptable Forms of Collaboration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Software development is an inherently collaborative process; to help you
practice and improve your collaborative skills, you are allowed to
collaborate with your project partner without any limitations or
constraints. You are also not required to provide citations on what you
discussed with your project partner.

You are also allowed to have *high-level* discussions with other
students in the class, as long as you don’t discuss implementation
details or share any code (except when discussing code we provide to
you). For example, the following would be acceptable questions to ask
other students in the class:

-  *“I am unclear on how IRC servers relay commands to other IRC
   servers. Can we walk through an example together?”*
-  *“Can I ask you some questions about RFC 793? I’m having trouble
   parsing this section in particular.”*
-  *“I’m having trouble wrapping my head around the tcp_data struct
   provided to us in Project 2. Can I ask you some questions about it?”*
-  *“I’m still getting the hang of Wireshark; I just opened this sample
   capture file, but I’m not sure where to find the IP payload. Do you
   know where it is?”*

Don’t forget that the course staff are also happy to answer these kinds
of questions on Ed Discussion or at office hours. That said, if you do
have these kinds of high-level discussions with a classmate, you must
list their name(s) in the documentation we ask you to submit with each
project.

Acceptable Uses of Generative AI
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Generative AI (GenAI) tools are becoming an increasingly common part of
a software developer’s toolkit, but you should remember that they are
ultimately just *productivity tools*. They are meant to facilitate and
speed up your work, not replace it entirely.

When talking with developers in industry, we have consistently heard
that these tools are most useful for routine or boilerplate tasks, where
they can significantly speed up work. Even then, developers stress the
importance of carefully reviewing the generated code to catch bugs or
issues that could arise later. A common caveat is that over-reliance on
these tools often results in errors creeping into a codebase, because
developers become too complacent with the GenAI’s output. Thus, many
developers avoid using generative AI for large or complex tasks, where
it’s beneficial for them to think through each line of code.

In this class, you are assumed to have four quarters worth of
programming experience (141 through 144), including two quarters of C
Programming. We assume your programming foundations are pretty solid,
and that you have reached a point where certain aspects of programming
start to feel routine and mechanical. We will allow you to use
Generative AI to deal with these kinds of tasks, but not with more
complex tasks, particularly those that are directly related to computer
networks.

More specifically, you are allowed to use GenAI tools in the following ways:

-  You can use autocomplete tools like Github Copilot to complete
   individual lines of code, as long as you understand exactly what that
   line of code is producing. You should exercise caution when
   repeatedly using this functionality (i.e., generating several lines
   one after the other)
-  You can use prompt-based tools to generate the code for small utility
   functions, or small self-contained blocks of code that are unrelated
   to networking.
-  You can take a piece of code we’ve provided to you, and ask a GenAI
   questions about that code.
-  You can provide a piece of code you’ve written to a prompt-based
   tool, and ask for feedback or for help with refactoring or
   documenting that code.
-  When interpreting a network protocol, you can use prompt-based tools
   to ask for clarifications on that protocol, or to resolve ambiguities
   in the protocol specification, as long as you do not ask the GenAI to
   produce code related to that protocol.
-  While the projects do not require you to write unit tests of your
   own, you are welcome to use GenAI tools to generate tests for any
   code you write.

You are also broadly allowed to use GenAI tools for reference purposes,
such as asking GenAI to explain how to perform certain tasks in C (e.g.,
“Is there a function in C to split a string based on a separator?”), or
to explain a concept from class in more detail (e.g., “Can you give me
an overview of the latest research in TCP Congestion Control?”).

**Important caveats about Generative AI**

-  Don’t forget that GenAI systems **have no sense of what is true or
   not**, and will sometimes produce plausible-looking code that contains
   errors, or which may cause issues in the context of the codebase that
   code is being used in. **Always double-check any code produced by
   GenAI**, and make sure that you understand what it does exactly.
-  Even when producing correct code, that code could contradict
   instructions/guidance we provide in this class. It is important that
   you always look at answers from GenAI with a critical eye, and that
   you remember that the content we provide in the class always takes
   precedence.
-  If a function or block of code was generated with GenAI, you must
   include a citation in the form of a code comment (e.g., “The
   following X lines of code were generated using GitHub Copilot”).
   Please note that you do not need to provide citations for
   autocompleting individual lines of code, only blocks of code.
-  If any part of your work benefitted from a conversation with a
   prompt-based tool, please provide a link to that conversation (you
   will be able to do so in the documentation we ask for in the
   projects). To facilitate this task (so you don’t have to generate
   multiple links), we encourage you to use a single conversation for
   all questions related to each project in the class (instead of
   starting new conversations for each question)
   The process for sharing these conversations will vary from one
   platform to another:

   -  **ChatGPT**: You will need to create a `shared
      link <https://help.openai.com/en/articles/7925741-chatgpt-shared-links-faq>`__
   -  **Gemini**: Follow their instructions to `share a
      chat <https://support.google.com/gemini/answer/13743730?hl=en&co=GENIE.Platform%3DDesktop>`__
   -  **PhoenixAI**: PhoenixAI does not appear to currently support
      ChatGPT’s shared links functionality. You can instead copy-paste
      the conversation(s) into your project documentation (in the
      Citations section)
   -  **GitHub Copilot** (chatting from an IDE like VSCode): There does
      not appear to be a way to generate a shareable link for these kind
      of chats (like above, you should copy-paste such conversations
      into your project documentation)
   -  **Other systems**: Check whether individual chats have some sort
      of “Share” button that will generate a shareable link. Otherwise,
      copy-paste the conversation into the project documentation.

Acceptable Uses of Other External Resources
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Software developers often rely on many external resources, including
websites like Stack Overflow, that can help them better understand how
to complete a certain task. You are allowed to use these external
resources, with the following caveats:

-  You must provide a citation for that external resource. If it
   affected a specific portion of your code, include a code comment with
   a link to that resource. If you consulted it more broadly, include it
   in the project’s documentation.
-  Reference documentation, as well as Stack Overflow posts, often
   include short snippets of sample code. Exercise caution when relying
   on these snippets of code. Using 2-3 lines of example code is
   typically not problematic, but longer pieces of code could result in
   your work being flagged as plagiarized (e.g., if other students
   relied on that same external resource). Make sure to always include a
   citation in these cases.

| Software developers also often rely on third-party libraries to
  perform routine tasks, so they can focus on the primary purpose of the
  code they are writing. For example, in the course projects, we do not
  want you to spend time implementing linked lists or hash tables; we
  are fine with you using existing implementations. In fact, the
  following libraries are pre-approved for use on the projects:

-  The `C Standard Library <https://en.cppreference.com/w/c/header>`__
-  `utlist <https://troydhanson.github.io/uthash/utlist.html>`__: A
   linked list library
-  `uthash <https://troydhanson.github.io/uthash/>`__: A hash table for
   C structures
-  `SDS <https://github.com/antirez/sds>`__: Simple Dynamic Strings

You can use these in your project code without asking for permission. If
there are other libraries you would like to use, please ask us first. We
will generally be fine with any library that does not provide
networks-related functionality that you’re expected to implement.

What is Not Allowed
-------------------

While certain forms of collaboration and uses of Generative AI and
external resources can supplement your learning, an over-reliance on
them can be detrimental to your learning, because they prevent you from
practicing and building the skills you should be taking away from this
class.

As such, we have to draw some lines in the sand:

-  While you are allowed to collaborate without constraints with your
   project partner, remember that you can only have high-level
   discussions with other students. This means that you **must not show
   or share your code with any other student in the class** (except your
   project partner). Please note that this prohibition extends beyond
   the end of this class (i.e., you also cannot share your code with a
   student taking a future offering of this class)
-  Do not use Generative AI systems to generate any code related to
   sockets or threads, as it is important that you get practice using
   these tools.
-  Do not use Generative AI to generate code that implements any portion
   of a network protocol, like IRC, TCP, etc. It is important that you
   think through the details of that protocol yourself, so you can
   better understand what is involved in taking a protocol specification
   and translating it into code.
-  Exercise caution when using Generative AI to generate anything larger
   than a utility function (with the exception of generating unit tests
   for your code).

Additionally, you must **not post your code in publicly-accessible
websites**, e.g., pastebin, a public GitHub repository, GitHub gists,
etc. This is less connected to your learning in the class, but can
affect the learning of future students, who could stumble upon your code
and may end up relying too heavily on it. Not just that, in the worst
case, you could be embroiled in a plagiarism case.

Don’t forget that you are provided with a private repository on GitHub,
and you should use that repository exclusively to do your work in this
class. We understand that you may want to share your work with
prospective employers after this class is over; you are welcome to do
so, but only by sending your code to them *privately* (not by posting it
on a publicly-accessible website).

Academic Integrity Offenses
---------------------------

If you run afoul of the above guidance, particularly if you actively
plagiarize someone else’s code, your code could be flagged as an
academic integrity offense. We take these incidents very seriously in
this class, and will escalate any such cases to the `Office of College
Community
Standards <https://college.uchicago.edu/student-services/office-college-community-standards>`__
for further adjudication. Going through disciplinary proceedings is an
unpleasant experience for everyone involved, and the outcome of these
cases can have an impact on your grade. At minimum, your final course
grade will drop one full step (letter). At maximum, you will receive an
F in the course.

We realize that sometimes students commit plagiarism out of desperation
and as a measure of last resort. If you are in this situation, please
just ask the instructors or other course staff for help. If you are
having a hard time in the class, we will provide as much assistance as
we can. Plus, a poor performance in one assignment is unlikely to wreck
your grade for the class. Plagiarism is never worth it.