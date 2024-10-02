.. _project_started:

Projects - Getting Started
--------------------------

Before working on the projects, we recommend you check out the `UChicago CS Student Resource Guide <https://uchicago-cs.github.io/student-resource-guide/>`__. In particular, please note the following:

- You should be able to compile and run the code for this class on Windows, MacOS, and Linux.
  If you are using a Windows system, you must specifically use WSL (Windows Subsystem for Linux).
  We will not be able to provide support if your use Windows PowerShell.

  If you are using a Windows or Mac system, you may need to install additional software required
  by the projects, such as CMake, pytest, etc.  Please note that, if you are running on the CS Linux servers,
  you do not need to install any of this software; it is already installed on those servers.

- Bear in mind that our code has been tested primarily on a `CS Software Environment <https://uchicago-cs.github.io/student-resource-guide/environment/environment.html>`__. If you would prefer to use such an environment, the Student Resource Guide describes several ways of accessing a CS Software Environment (including remote options).

  You can also run your development environment of choice on your personal computer, and connect to a CS machine only to compile, run, and test your code. This is particularly easy to set up using `Visual Studio Code <https://code.visualstudio.com/>`__. The Student Resource Guide includes instructions on how to set up Visual Studio Code, and how to set it up to SSH into a CS environment.

- If you are new to Git, you should work through the `Git Tutorial <https://uchicago-cs.github.io/student-resource-guide/tutorials/git-intro.html>`__ to familiarize yourself with Git.

- You will need to set up SSH access to your GitHub repositories. If you worked through
  the `Git Tutorial <https://uchicago-cs.github.io/student-resource-guide/tutorials/git-intro.html>`__ tutorial, then you will have already done this. If not, you can find instructions
  at the start of the tutorial, but you can also refer to Github's
  documentation on `Connecting to GitHub with SSH <https://docs.github.com/en/free-pro-team@latest/github/authenticating-to-github/connecting-to-github-with-ssh>`__

- The `C style guide <https://uchicago-cs.github.io/student-resource-guide/style-guide/c.html>`__ in the Student Resource Guide is the normative style guide for this class.

- When asking questions on Ed Discussion, you must follow the guidelines in the `Asking Questions <../getting-help.html#asking-questions>`__ section of our `Getting Help <../getting-help.html>`__ page.

- `The Debugging Guide <https://uchicago-cs.github.io/debugging-guide/>`__, linked from the guide, contains useful suggestions and pointers on how to debug your C code.

.. _project_registration:

Initial Project Registration
----------------------------

For each project, a Git repository will be created for you and your project partner on `GitHub <https://github.com/>`__, a web-based hosting service for Git repositories. However, before that repository can be created for you, you need to have a GitHub account. If you do not yet have one, you can get an account here: https://github.com/join. Once you create your account, you may want to get the `Student Developer Pack <https://education.github.com/pack>`__, which will give you access to a lot of other features (please note that having the Student Developer Pack is not necessary for this class; it's just a nice benefit you get as a student)

If you're unfamiliar with Git, you should work through the `Git Tutorial <https://uchicago-cs.github.io/student-resource-guide/tutorials/git-intro.html>`__ before proceeding further.

To actually get your private repository, you will need an *invitation URL*, which we will provide through Canvas when each project is released. When you click on an invitation URL, you will have to complete the following steps:

1. You will need to select your CNetID from a list. This will allow us to know what student is associated with each GitHub account. This step is only done for the very first invitation you accept.
2. Next, you will need to create a new team, or join an existing team if your project partner has already created a team. Please make sure to coordinate with your project partner so you do not end up creating two separate teams.

   Please note that, while GitHub will allow you to select an arbitrary team name, your team name **must** be your CNetIDs in alphabetical order and separated by a hyphen (e.g., ``jdoe-jrandom``).
3. Finally, you must click "Accept this assignment" or your repository will not actually be created.
4. Once the repository has been created, **DO NOT** run the commands shown on GitHub to
   initialize your repository. You must instead run the commands we provide to you (you
   can find these in the pertinent project page on this website)

If you run into any issues, or need us to make any manual adjustments to your registration, please let us know via Ed Discussion.
