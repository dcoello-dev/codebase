# sandbox_idea: python/basics
# sandbox_name: closure_example
# sandbox_description: closure example closure example
# sandbox_env: python


def closure():
    state = 0

    def inner(line):
        nonlocal state

        print(f"line: {line} {state}")
        state = state + 1
    return inner


def executor(fnc):
    fnc("hello")


if __name__ == "__main__":
    fnc = closure()
    executor(fnc)
    executor(fnc)
