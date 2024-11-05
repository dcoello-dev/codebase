# sandbox_idea: python/terminal_utils
# sandbox_name: pipe_into_python
# sandbox_description: pipe colors into python script
# sandbox_env: python

import os
import sys
import argparse

# create parser to be configured with the expected arguments
parser = argparse.ArgumentParser(
    description="example script on how to use argparse")


# boolean argument
parser.add_argument(
    '-b', '--boolean',
    action='store_true',
    default=False,
    help="boolean argument")

parser.add_argument('-e', '--execute', nargs='+', default=[])

args = parser.parse_args()
print(args)

if __name__ == "__main__":
    if args.boolean:
        for line in sys.stdin:
            print(line.replace('\n', ''))
    else:
        print(args.execute)
        os.system(f"unbuffer {' '.join(args.execute)} | python3 main.py -b")
