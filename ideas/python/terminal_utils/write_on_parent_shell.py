# sandbox_idea: python/terminal_utils
# sandbox_name: write_on_parent_shell
# sandbox_description: write on parent bash shell
# sandbox_env: python

import fcntl
import shlex
import termios

BACKSPACE = '\x08'

def write_on_parent_shell(cmd: str, NB: int = 0):
    backspace = BACKSPACE * NB
    cmd = f"{backspace}{cmd}\n"
    for c in cmd:
        fcntl.ioctl(2, termios.TIOCSTI, c)

if __name__ == "__main__":
    print("hello world!")
