# sandbox_idea: python/basics
# sandbox_name: multiprocessing_shared_memory
# sandbox_description: shared memory between multiprocessing threads
# sandbox_env: python

import time
import multiprocessing as mp


def th_run(name, sh_mem):
    for _ in range(0, 10):
        print(f"pr {name} exe")
        sh_mem["val"] += name
        time.sleep(name/10)
    print(f"end pr {name}")


if __name__ == "__main__":
    sm_manager = mp.Manager()
    mem = sm_manager.dict()
    mem["name"] = "example"
    mem["val"] = 0

    prs = [mp.Process(target=th_run, args=[i, mem]) for i in range(1, 3)]
    for pr in prs:
        pr.start()

    for pr in prs:
        pr.join()

    print(f"result: {mem['val']}")
