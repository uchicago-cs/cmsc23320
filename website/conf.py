# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'CMSC 23320 - Foundations of Computer Networks'
copyright = '2011-2026, University of Chicago'
author = 'University of Chicago'
release = '2026-autumn'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.mathjax',
]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store', 'venv']



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "pydata_sphinx_theme"
html_title = project
html_static_path = ['_static']
html_css_files = [
    'css/chiweb.css',
]
html_theme_options = {
    "logo": {
        "text": "CMSC 23320",
    },
    "navbar_center": ["navbar-dropdowns"],
    "show_prev_next": False,
    "secondary_sidebar_items": ["page-toc"],
}

html_sidebars = {
  "**": []
}

# Entries in the navbar (rendered by _templates/navbar-dropdowns.html).
# Each entry is either (title, page) or (title, [(title, page_or_url, is_external), ...])
html_context = {"web_navbar": [("Course Information", [
                                    ("Syllabus", "syllabus", False),
                                    ("Calendar", "calendar", False),
                                    ("Getting Help", "getting-help", False),
                                    ("Academic Integrity", "academic-integrity", False),
                                    ("Code of Conduct for Course Staff", "code-of-conduct", False),
                                 ]),
                                 ("Projects", [
                                     ("Getting Started", "projects/started", False),
                                     ("Project 1: chirc", "projects/project1", False),
                                     ("Project 2: chiTCP", "projects/project2", False),
                                     ("Project 3: chirouter", "projects/project3", False),
                                 ]),
                                 ("Resources", [
                                     ("UChicago CS Student Resource Guide", "https://uchicago-cs.github.io/student-resource-guide/", True),
                                     ("Code Samples", "https://github.com/uchicago-cs/cmsc23320/tree/main/samples", True),
                                     ("The Debugging Guide", "https://uchicago-cs.github.io/debugging-guide", True),
                                     ("Other Resources", "resources/other", False),
                                 ])
                                 ]}
