# sandbox_idea: python/terminal_utils
# sandbox_name: execute_subprocess
# sandbox_description: how to execute subprocess
# sandbox_env: python

import subprocess

def _ex_subprocess(cmd: str, shell=True) -> tuple:
    p = subprocess.Popen(
        cmd, shell=shell,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        executable='/bin/bash')
    output, error = p.communicate()
    return (p.returncode, output, error)

class Process:
    def __init__(self, cmd):
        self.cmd_ = cmd
        self.process_ = None

    def __del__(self):
        if self.process_ is not None:
            if self.check() is None:
                self.stop()

    def start(self):
        self.process_ = subprocess.Popen(
            self.cmd_, shell=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            executable='/bin/bash')

    def check(self):
        if self.process_ is not None:
            return (self.process_.poll() is None)

    def stop(self):
        if self.process_ is not None:
            self.process_.terminate()
            return self.process_.communicate()
        
    def join(self):
        if self.process_ is not None:
            return self.process_.communicate()

if __name__ == "__main__":
    print(_ex_subprocess("echo hola"))
