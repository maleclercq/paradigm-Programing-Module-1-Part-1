from typing import TypeVar

T = TypeVar("T", int, float)

def add(x: T, y: T) -> T:
  	return x + y

print(add(5, 16))
print(add(5.0, 16.0))
