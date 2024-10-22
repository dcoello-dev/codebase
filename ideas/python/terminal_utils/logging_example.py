# sandbox_idea: python/terminal_utils
# sandbox_name: logging_example
# sandbox_description: how to use logging python module
# sandbox_env: python

import logging
import argparse


parser = argparse.ArgumentParser(
    description="example script on how to use argparse")

parser.add_argument('--verbose', '-v', action='count', default=1)

parser.add_argument(
    '-l', '--log_level',
    default="info",
    help="app log level")

args = parser.parse_args()

args.verbose = 70 - (10*args.verbose) if args.verbose > 0 else 0

logging.basicConfig(
    format='%(asctime)s %(levelname)s:%(message)s',
    level=eval(f"logging.{args.log_level.upper()}"))

if __name__ == "__main__":
    print(args)
    logging.info(args)
