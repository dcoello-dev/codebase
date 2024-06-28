# sandbox_idea: python/register_cls/
# sandbox_name: register_decorator
# sandbox_description: decorator to register implementations
# sandbox_env: python

from collections import defaultdict

REG_NAMESPACE = defaultdict(dict)

def Register(type_reg: str, name: str, description: str):
    """Register implementation.

    Args:
        name (Type): type of registered entity.
        name (str): implementation id.
        description (str): implementation description.
        short (str, optional): short argparse val. Defaults to None.
        long (str, optional): long argparse val. Defaults to None.
    """
    def wrapper(cls):
        REG_NAMESPACE[type_reg][name] = dict(instance=(cls),
                                             description=description)
        return cls
    return wrapper

if __name__ == "__main__":
    print("hello world!")
