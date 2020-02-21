class Animal:

    def noise(self):
        print("Make a noise")

    class Dog(Animal):
    
        def noise(self):
            print("It barks")

    class Cat(Animal):
    
        def noise(self):
            print("It meows")

    if __name__ == '__main__':
        dog_instance = Dog()
        cat_instance = Cat()
        dog_instance.noise()
        cat_instance.noise()
