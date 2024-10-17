# sandbox_idea: python/basics/coroutines/
# sandbox_name: threading_coroutines_example
# sandbox_description: example on how to coroutine
# sandbox_env: python

import time
import asyncio
import threading

loop1 = asyncio.new_event_loop()
loop2 = asyncio.new_event_loop()

message = ""
counter = 0

async def coro3():
    global message
    previous = ""
    while True:
        if message != "" and message != previous:
            print(f"coro3 {message}")
            previous = message
        time.sleep(1)

def fnc():
    global message
    global counter
    counter = counter + 1
    print("fnc")
    message = f"fnc {counter}"

async def coro2():
    print("coro2")
    fnc()

async def coro1():
    while True:
        print("coro1")
        await coro2()
        time.sleep(1)

def th_fnc(loop, coro):
    loop.run_until_complete(coro())

if __name__ == "__main__":
    th = threading.Thread(target=th_fnc, args=(loop1, coro1))
    th.start()
    loop2.run_until_complete(coro3())
    th.join()
    
