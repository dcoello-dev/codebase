# sandbox_idea: parse_cli_args
# sandbox_name: parse_cli_args
# sandbox_description: how to parse cli arguments in bash
# sandbox_env: bash

function usage(){
  echo "bash ${BASH_SOURCE[0]} args"
  echo
  echo "  -h/--help         this help message"
  echo "  -a/--aarg         a arg"
  echo "  -b/--barg {value} b arg"
}

# support --arg input
for arg in "$@"; do
  shift
  case "$arg" in
    '--help') set -- "$@" '-h' ;;
    '--aarg') set -- "$@" '-a' ;;
    '--barg') set -- "$@" '-b' ;;
    *) set -- "$@" "$arg" ;;
  esac
done

# first : is to allow us to manage the errors.
OPTSTRING=":ab:h"

while getopts ${OPTSTRING} opt; do
  case ${opt} in
    a)
      # bash main.sh -a
      echo "argument a called"
      ;;
    b)
      # bash main.sh -b opt
      echo "to add argument to arg place : after b arg in optstring, the argument is $OPTARG"
      ;;
    h)
      usage
      ;;
    ?)
      echo "Invalid option: -${OPTARG}."
      exit 1
      ;;
  esac
done
