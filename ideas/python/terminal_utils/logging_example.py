# sandbox_idea: python/terminal_utils
# sandbox_name: logging_example
# sandbox_description: how to use logging python module
# sandbox_env: python

import logging
import argparse


parser = argparse.ArgumentParser(
    description="example script on how to use argparse")

parser.add_argument('--verbose', '-v', action='count', default=1)

args = parser.parse_args()

args.verbose = 70 - (10*args.verbose) if args.verbose > 0 else 0

logging.basicConfig(
    format='%(asctime)s %(levelname)s:%(message)s',
    level=args.verbose)

if __name__ == "__main__":
    logging.info("hello world!")
