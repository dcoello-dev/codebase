# sandbox_idea: python/ollama
# sandbox_name: transcript_processor
# sandbox_description: 
# sandbox_env: python

from ollama import chat
from ollama import ChatResponse

import time
import os
import signal
import argparse
import subprocess
import multiprocessing

parser = argparse.ArgumentParser(
    description="example script on how to use argparse")

parser.add_argument(
    '-i', '--input',
    required=True,
    help="transcript file")

parser.add_argument(
    '-q', '--question',
    default="Please identify the main discussion points, decisions, and action items from my meeting notes below and provide a concise bulleted summary:\n",
    help="transcript file")

args = parser.parse_args()

class Process:
    def __init__(self, name, cmd, callback=print):
        self.name_ = name
        self.cmd_ = cmd
        self.process_ = None
        self.callback_ = callback

    def __del__(self):
        if self.process_ is not None:
            if self.check() is None:
                self.stop()

    def __forward_stdout(self):
        if self.process_ is not None:
            # while true due known issue on subprocess
            # loop for line in p.stdout:
            try:
                while True:
                    line = self.process_.stdout.readline()
                    if not line:
                        break
                    self.callback_(line.replace('\n', ''))
            except ValueError:
                pass
            except KeyboardInterrupt:
                pass

    def name(self):
        return self.name_

    def start(self):
        self.process_ = subprocess.Popen(
            self.cmd_, shell=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            start_new_session=True,
            executable='/bin/bash',
        )
        self.capture_th_ = multiprocessing.Process(
            target=self.__forward_stdout,
        )
        self.capture_th_.start()
        return self

    def __com(self, p):
        try:
            output, error = p.communicate()
        except ValueError:
            output = ''
            error = ''
        return (p.returncode, output, error)

    def check(self):
        if self.process_ is not None:
            return (self.process_.poll() is None)

    def stop(self):
        if self.process_ is not None:
            try:
                os.killpg(self.process_.pid, signal.SIGTERM)
            except Exception:
                pass
            self.capture_th_.kill()
            self.capture_th_.join()
            return self.__com(self.process_)

    def join(self):
        if self.process_ is not None:
            return self.__com(self.process_)

class Silent:
    def __call__(self, line):
        pass

if __name__ == "__main__":
    server = Process("ollama", "ollama serve", Silent())
    try:
        server.start()
        time.sleep(5)
        with open(args.input, "r", encoding="latin-1") as transcript:

            print("clean")
            trans = transcript.read()
            clean: ChatResponse = chat(model='llama3.1', messages=[
              {
                'role': 'user',
                'content': f'You are a transcript expert and now you have to clean next transcript making it more clear: {trans}',
              },
            ])
            print("summary")
            summary: ChatResponse = chat(model='llama3.1', messages=[
              {
                'role': 'user',
                'content': f'you are an expert writer and I need you to do a long summary of this transcript without missing any technical detail: {clean["message"]["content"]}',
              },
            ])
            print("response")
            response: ChatResponse = chat(model='llama3.1', messages=[
              {
                'role': 'user',
                'content': f'You are an expert engineer and I need you to extract most relevant key points of: {summary["message"]["content"]}',
              },
            ])
            with open(f'{args.input.split("/")[-1].split(".")[0]}_notes.txt', "w+") as note:
                note.write(response['message']['content'])
        server.stop()
        server.join()
    except KeyboardInterrupt:
        server.stop()
