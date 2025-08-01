# sandbox_idea: parse_cli_args
# sandbox_name: parse_cli_args
# sandbox_description: how to parse cli arguments in bash
# sandbox_env: python

import os
import json
# use std argparse module
import argparse

# create parser to be configured with the expected arguments
parser = argparse.ArgumentParser(
    description="example script on how to use argparse")

# argument with value and default value
parser.add_argument(
    '-c', '--config',
    default=os.path.expanduser('~') + ".config",
    help="configuration file")

# boolean argument
parser.add_argument(
    '-b', '--boolean',
    action='store_true',
    default=True,
    help="boolean argument")

# integer argument
parser.add_argument(
    '-i', '--index',
    type=int,
    # if required comment default
    # required=True
    default=-1,
    help="index")

# subparsers for conditional modes
subparsers = parser.add_subparsers(dest='subcommand')
subparsers.required = True  # required since 3.7

#  subparser for dump
parser_dump = subparsers.add_parser('dump')
# add a required argument
parser_dump.add_argument(
    'format',
    choices=['csv', 'json'],
    help='Dump the file in this format.')

#  subparser for upload
parser_upload = subparsers.add_parser('upload')
# add a required argument
parser_upload.add_argument(
    'server',
    choices=['amazon', 'imgur'],
    help='Upload the file to this service.')

parser.add_argument(
    '-v', '--var',
    action='append',
    help='append argument in a list',
)

# pipe text and get all remainder arguments as string
parser.add_argument('text', nargs=argparse.REMAINDER)
parser.add_argument('stdin', nargs='?', type=argparse.FileType('r'), default=sys.stdin)

# once arguments are created it is time to parse it
args = parser.parse_args()

if __name__ == "__main__":
    print(json.dumps(args.__dict__, indent=2))
