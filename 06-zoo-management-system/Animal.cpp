#include "Animal.hpp"
#include <iostream>
#include <stdexcept>

namespace zoo {

    // Initialization of a static variable must be done in the .cpp file, not the .hpp (otherwise we get a linker error)
    int Animal::animalCount = 0;

    Animal::Animal(const std::string& animalName, int animalAge, const std::string& animalSpecies) 
        : name(animalName), age(animalAge), species(animalSpecies) {
        if (animalAge < 0) {
            throw std::invalid_argument("Age cannot be negative");
        }
        // Increment the static counter every time a new animal is created to keep track of the total number of animals
        animalCount++;
        std::cout << species << " Animal constructed: " << name << "\n";
    }

    Animal::Animal(const Animal& otherAnimal) 
        : name(otherAnimal.name), age(otherAnimal.age), species(otherAnimal.species) {
        animalCount++;
        std::cout << species << " Animal copy-constructed: " << name << "\n";
    }

    Animal::~Animal() {
        // Decrement the static counter because the animal is being deleted from memory
        animalCount--;
        std::cout << species << " Animal destructed: " << name << "\n";
    }

    Animal& Animal::operator=(const Animal& otherAnimal) {
        // Self-assignment check: must check to prevent overwriting if we accidentally did a = a
        if (this != &otherAnimal) {
            name = otherAnimal.name;
            age = otherAnimal.age;
            species = otherAnimal.species;
        }
        return *this;
    }

    std::string Animal::getName() const {
        return name;
    }

    int Animal::getAge() const {
        return age;
    }

    std::string Animal::getSpecies() const {
        return species;
    }

    void Animal::setName(const std::string& newName) {
        name = newName;
    }

    void Animal::setAge(int newAge) {
        if (newAge < 0) {
            throw std::invalid_argument("Age cannot be negative");
        }
        age = newAge;
    }

    std::string Animal::getDescription() const {
        // Calls virtual methods like getAnimalType(). At runtime, this will call the actual child class function (polymorphism)
        return "[" + getAnimalType() + "] " + name + " (" + species + "), Age: " + std::to_string(age) + ", Sound: " + makeSound() + ", Diet: " + getDiet();
    }

    int Animal::getAnimalCount() {
        return animalCount;
    }

}