Uploading the initial code to your repository
---------------------------------------------

For each project, we provide some initial code that you must upload to your repository. We need you to upload this code in a very specific way, to make sure that our grading scripts can find your code, build it, and run tests on it.

In this page we provide the exact commands you need to run to set up your repository. Some of them will look like dark magic but, at this point, you do not need to understand them.

Preliminaries
~~~~~~~~~~~~~

* If you are new to Git, make sure you've read the `Using Git <git.html>`_ page.
* Make sure you've set up `SSH access <https://docs.github.com/en/free-pro-team@latest/github/authenticating-to-github/connecting-to-github-with-ssh>`__ on your GitHub account.
* Only one of the team members needs to initialize the repository. In other words, do *not* follow these instructions more than once. Once one of you has initialized the repository, the other team member will be able to simply create a local copy of the (initialized) Git repository that you are both sharing.
* For each repository, you will need to get the SSH URL of the repository. To get this URL, log into GitHub and navigate to your project repository (take into account that you will have a different repository per project). Then, click on the green "Code" button, and make sure the "SSH" tab is selected. Your repository URL should look something like this: ``git@github.com:uchicago-cmsc23320-2021/p1-jdoe-jrandom.git``. In the steps below, we will refer to this simply as ``$REPO_URL``.


Project 1
~~~~~~~~~

To initialize your repository for project 1, create an empty directory and, inside the directory, run the following commands::

    git init
    git remote add origin $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chirc.git
    git pull upstream master
    git push -u origin master

Remember to replace ``$REPO_URL`` with the SSH URL of your repository!


Project 2
~~~~~~~~~

To initialize your repository for project 2, create an empty directory. *Do not reuse the directory or repository from Project 1*. Inside the directory, run the following commands::

    git init
    git remote add origin $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chitcp.git
    git pull upstream master
    git push -u origin master

Remember to replace ``$REPO_URL`` with the SSH URL of your repository!

Project 3
~~~~~~~~~

To initialize your repository for project 3, create an empty directory. *Do not reuse the directory or repository from Project 1 or 2*. Inside the directory, run the following commands::

    git init
    git remote add origin $REPO_URL
    git remote add upstream https://github.com/uchicago-cs/chirouter.git
    git pull upstream master
    git push -u origin master

Remember to replace ``$REPO_URL`` with the SSH URL of your repository!

Common Commands
~~~~~~~~~~~~~~~

If you want to create other copies of the repository (e.g., if you are the team member who did *not* run the above commands to initialize the repository) just run the following *after* the repository has been initialized::

    git clone $REPO_URL

If we make any changes to the upstream repository, and you want to merge them into your repository, you need to run the following command::

    git pull upstream master
