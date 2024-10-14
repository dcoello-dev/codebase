# sandbox_idea: python/basics
# sandbox_name: interface_class
# sandbox_description: How to define an interface in python
# sandbox_env: python
from abc import ABC, abstractmethod

class IInterface(ABC):
    @abstractmethod
    def interface_method(self):
        pass

class Implementation(IInterface):
    def interface_method(self):
        print("do things")

if __name__ == "__main__":
    i = Implementation()
    i.interface_method()
