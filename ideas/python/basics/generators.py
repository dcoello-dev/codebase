# sandbox_idea: python/basics
# sandbox_name: generators
# sandbox_description: simple generator example
# sandbox_env: python

def gen(n):
    for i in range(0, n):
        yield i

if __name__ == "__main__":
    g = gen(10)
    print(next(g))
    print(next(g))
    print(next(g))
