import os
import sys
sys.path.insert(0, os.path.abspath('..'))
import ffilupa

project = 'ffilupa'
copyright = '2017, 2018, 2019, TitanSnow'
author = 'TitanSnow'
release = ffilupa.__version__
version = '.'.join(ffilupa.__version__.split('.')[:2])
master_doc = 'index'
autoclass_content = 'both'
autodoc_default_options = {
    'member-order': 'bysource',
    'members': True,
    'undoc-members': True,
    'imported-members': True,
}
extensions = [
    "sphinx.ext.autodoc",
    "sphinx.ext.intersphinx",
    "sphinx.ext.viewcode",
    "sphinx.ext.todo",
    "sphinx_autodoc_typehints",
]
templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']
html_theme = 'alabaster'
html_static_path = ['_static']
intersphinx_mapping = {
    "python": ("https://docs.python.org/3/", None),
}