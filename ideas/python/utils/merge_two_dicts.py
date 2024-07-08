# sandbox_idea: python/utils
# sandbox_name: merge_two_dicts
# sandbox_description: how to deep merge 2 dicts
# sandbox_env: python

import json

def merge_two_dicts(a, b, path=[]):
    for key in b:
        if key in a:
            if isinstance(a[key], dict) and isinstance(b[key], dict):
                merge_two_dicts(a[key], b[key], path + [str(key)])
        else:
            a[key] = b[key]
    return a

if __name__ == "__main__":
    # a overrides b
    a = dict(a="h", b=1)
    b = dict(b=2, c=3)
    print(json.dumps(merge_two_dicts(a,b), indent=2))
