# sandbox_idea: python/register_cls
# sandbox_name: import_util
# sandbox_description: import all files in a directory
# sandbox_env: python

import os

for module in os.listdir(os.path.dirname(__file__)):
    if module == '__init__.py' or module[-3:] != '.py':
        continue
    # adapt import to module path
    __import__(module[:-3], locals(), globals())
del module
