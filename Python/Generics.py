from typing import TypeVar

T = TypeVar("T")
        
def add(x: T, y: T) -> T:
   	return x + y
	      	
print(add(5,16))
print(add('a', 'b'))
