 from typing import TypeVar, Generic

 T = TypeVar('T')
 S = TypeVar('S')

 class Person(Generic[T,S]):
     def __init__(self, name: str, birthdate: T, deathdate: S) -> None:
          self.name = name
          self.birthdate = birthdate
          self.deathdate = deathdate
        
          def getBirthdate(self) -> T:
              return self.birthdate
        
          def getDeathdate(self) -> S:
              return self.deathdate
        
if __name__ == '__main__':
    person_instance = Person("Tom", "17/04/1947", "30/01/2017")
    print(person_instance.getBirthdate())
    print(person_instance.getDeathdate())
