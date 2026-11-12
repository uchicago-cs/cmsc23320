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
# so by running this from the website/ directory of a freshly
# cloned version of the repo:
#
#   git worktree add -B gh-pages _build/html origin/gh-pages
#
# If you move the repo to a different directory, run this from
# the website/ directory to update the worktree's paths:
#
#   git worktree repair _build/html
#
# Since the site is rebuilt from scratch every time, the deploy target
# moves the gh-pages branch to the latest remote commit (keeping the
# freshly built files) before committing, so that deploying from a
# checkout whose gh-pages branch is out of date doesn't fail.

GHP = git --work-tree=$(BUILDDIR)/html/ --git-dir=$(BUILDDIR)/html/.git

deploy: html
	rm -f $(BUILDDIR)/html/.buildinfo.bak
	$(GHP) fetch origin gh-pages
	$(GHP) reset --soft FETCH_HEAD
	$(GHP) add -A .
	$(GHP) diff --cached --quiet || $(GHP) commit -m "Updated website"
	$(GHP) push origin HEAD:gh-pages

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
