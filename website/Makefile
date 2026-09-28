# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = .
BUILDDIR      = _build

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

# For the deploy target to work, a worktree must be created
# in _build/html that tracks the gh-pages branch. You can do
# so by running this from a freshly cloned version of the repo:
#
#   git worktree add -B gh-pages _build/html origin/gh-pages

deploy:
	echo gitdir: $(shell cd ..; pwd)/.git/worktrees/html > $(BUILDDIR)/html/.git
	git --work-tree=$(BUILDDIR)/html/ --git-dir=$(BUILDDIR)/html/.git add -A .
	git --work-tree=$(BUILDDIR)/html/ --git-dir=$(BUILDDIR)/html/.git commit -m"Updated website"
	git --work-tree=$(BUILDDIR)/html/ --git-dir=$(BUILDDIR)/html/.git push origin gh-pages

# Note: we don't use Sphinx's "clean" target because it would remove
# the gh-pages worktree in _build/html
clean:
	rm -rf $(BUILDDIR)/html/*

cleanall:
	rm -rf $(BUILDDIR)/*

.PHONY: help deploy clean cleanall Makefile

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
