# sandbox_idea: python/basics
# sandbox_name: flask_minimal
# sandbox_description: minimal flask example
# sandbox_env: python

import json
from  flask import Flask, request, jsonify

def hello_world():
    return 'Hello, World!'

def generate_print_and_status(status_code):
    status = status_code
    def print_and_status():
        print(json.dumps(request.json))
        resp = jsonify()
        resp.status_code = status
        return resp
    return print_and_status

class HttpServer:
    def __init__(self, endpoints):
        self.app = Flask(__name__)
        for end in endpoints:
            self.app.route(end["endpoint"], methods=end["methods"])(end["callback"])

    def run(self):
        self.app.run()

if __name__ == "__main__":
    server = HttpServer([dict(endpoint="/", methods=["GET"],
                              callback=hello_world),
                         dict(endpoint="/put/", methods=["PUT"],
                              callback=generate_print_and_status(200))]) 
    server.run()
