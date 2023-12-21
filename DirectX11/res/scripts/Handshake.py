import PythonSystemLibrary


def handshake_python():
    print("Python is shaking hands!")
    PythonSystemLibrary.handshake_cpp()


class Foo:
    __slots__ = ("a", "b")

    def __init__(self, a, b):
        self.a = a
        self.b = b

    def print_foo(self):
        print(f"Foo values are {self.a}, {self.b}")
