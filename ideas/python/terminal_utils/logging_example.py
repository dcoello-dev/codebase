# sandbox_idea: python/terminal_utils
# sandbox_name: logging_example
# sandbox_description: how to use logging python module
# sandbox_env: python

import logging

logging.basicConfig(
    format='%(asctime)s %(levelname)s:%(message)s',
    level=logging.INFO)

if __name__ == "__main__":
    logging.info("hello world!")
