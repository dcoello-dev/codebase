# sandbox_idea: python/utils
# sandbox_name: list_files_recursively
# sandbox_description: list all files recursively of a given path
# sandbox_env: python

import os
import pathlib

def list_files_recursively(dir):
    dd = pathlib.Path(dir)
    ret = []
    for elem in dd.iterdir():
        if os.path.isfile(elem):
            ret.append(elem)
        else:
            ret += list_files_recursively(elem)
    return ret

if __name__ == "__main__":
    print(list_files_recursively("."))
