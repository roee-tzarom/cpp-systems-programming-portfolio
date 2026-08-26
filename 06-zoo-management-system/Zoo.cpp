#include "Zoo.hpp"
#include "Mammal.hpp"
#include "Bird.hpp"
#include "Reptile.hpp"
#include <iostream>
#include <stdexcept>

namespace zoo {

    int Zoo::totalZoosCreated = 0;

    void Zoo::resize() {
        int newCapacity = capacity * 2;
        // Allocate a new array of pointers, because we store pointers to Animal to enable polymorphism
        Animal** newAnimals = new Animal*[static_cast<size_t>(newCapacity)];
        for (int i = 0; i < count; ++i) {
            newAnimals[i] = animals[i];
        }
        delete[] animals;
        animals = newAnimals;
        capacity = newCapacity;
    }

    Zoo::Zoo(const std::string& name, int initialCapacity)
        : zooName(name), capacity(initialCapacity), count(0), animals(nullptr) {
        if (initialCapacity <= 0) {
            throw std::invalid_argument("Capacity must be positive");
        }
        animals = new Animal*[static_cast<size_t>(capacity)];
        totalZoosCreated++;
    }

    Zoo::Zoo(const Zoo& otherZoo)
        : zooName(otherZoo.zooName), capacity(otherZoo.capacity), count(otherZoo.count), animals(nullptr) {
        animals = new Animal*[static_cast<size_t>(capacity)];
        for (int i = 0; i < count; ++i) {
            // Use dynamic_cast to identify the type of each animal at runtime, so we can do a proper Deep Copy
            if (const Mammal* mammalPtr = dynamic_cast<const Mammal*>(otherZoo.animals[i])) {
                animals[i] = new Mammal(*mammalPtr);
            } else if (const Bird* birdPtr = dynamic_cast<const Bird*>(otherZoo.animals[i])) {
                animals[i] = new Bird(*birdPtr);
            } else if (const Reptile* reptilePtr = dynamic_cast<const Reptile*>(otherZoo.animals[i])) {
                animals[i] = new Reptile(*reptilePtr);
            }
        }
        totalZoosCreated++;
    }

    Zoo::~Zoo() {
        // First delete each specific animal in the array to prevent Memory Leaks (this will call their virtual Destructor)
        for (int i = 0; i < count; ++i) {
            delete animals[i];
        }
        // Then delete the array itself
        delete[] animals;
    }

    Zoo& Zoo::operator=(const Zoo& otherZoo) {
        if (this != &otherZoo) {
            // Clear the old memory to free up space (delete all animals then the array)
            for (int i = 0; i < count; ++i) {
                delete animals[i];
            }
            delete[] animals;

            zooName = otherZoo.zooName;
            capacity = otherZoo.capacity;
            count = otherZoo.count;

            animals = new Animal*[static_cast<size_t>(capacity)];
            for (int i = 0; i < count; ++i) {
                // Deep copy like in the Copy Constructor by identifying the type
                if (const Mammal* mammalPtr = dynamic_cast<const Mammal*>(otherZoo.animals[i])) {
                    animals[i] = new Mammal(*mammalPtr);
                } else if (const Bird* birdPtr = dynamic_cast<const Bird*>(otherZoo.animals[i])) {
                    animals[i] = new Bird(*birdPtr);
                } else if (const Reptile* reptilePtr = dynamic_cast<const Reptile*>(otherZoo.animals[i])) {
                    animals[i] = new Reptile(*reptilePtr);
                }
            }
        }
        return *this;
    }

    std::string Zoo::getZooName() const {
        return zooName;
    }

    void Zoo::setZooName(const std::string& name) {
        zooName = name;
    }

    int Zoo::getCapacity() const {
        return capacity;
    }

    int Zoo::getCount() const {
        return count;
    }

    bool Zoo::isEmpty() const {
        return count == 0;
    }

    void Zoo::addAnimal(const Animal& newAnimal) {
        if (count == capacity) {
            resize();
        }
        
        // Dynamically allocate memory for the new animal based on its type, so polymorphism works properly in our array
        if (const Mammal* mammalPtr = dynamic_cast<const Mammal*>(&newAnimal)) {
            animals[count] = new Mammal(*mammalPtr);
        } else if (const Bird* birdPtr = dynamic_cast<const Bird*>(&newAnimal)) {
            animals[count] = new Bird(*birdPtr);
        } else if (const Reptile* reptilePtr = dynamic_cast<const Reptile*>(&newAnimal)) {
            animals[count] = new Reptile(*reptilePtr);
        } else {
            throw std::invalid_argument("Unknown animal type");
        }
        
        count++;
    }

    Animal* Zoo::findAnimal(const std::string& animalName) const {
        for (int i = 0; i < count; ++i) {
            if (animals[i]->getName() == animalName) {
                return animals[i];
            }
        }
        return nullptr;
    }

    const Animal& Zoo::getAnimal(int targetIndex) const {
        if (targetIndex < 0 || targetIndex >= count) {
            throw std::out_of_range("Index out of bounds");
        }
        return *(animals[targetIndex]);
    }

    void Zoo::removeAnimal(int targetIndex) {
        if (targetIndex < 0 || targetIndex >= count) {
            throw std::out_of_range("Index out of bounds");
        }
        // Must free the memory of the animal itself before removing it
        delete animals[targetIndex];
        
        // Move all animals after the index one place back to prevent "holes" in the array
        for (int i = targetIndex; i < count - 1; ++i) {
            animals[i] = animals[i + 1];
        }
        count--;
        animals[count] = nullptr; // Nullify the last pointer that remains empty
    }

    void Zoo::printAllAnimals() const {
        std::cout << "=== " << zooName << " ===\n";
        for (int i = 0; i < count; ++i) {
            std::cout << (i + 1) << ". " << animals[i]->getDescription() << "\n";
        }
    }

    void Zoo::makeAllSounds() const {
        for (int i = 0; i < count; ++i) {
            // Polymorphism in action: we don't need to know if it's a bird or mammal, C++ calls the correct function
            std::cout << animals[i]->getName() << " says: " << animals[i]->makeSound() << "\n";
        }
    }

    int Zoo::getTotalZoosCreated() {
        return totalZoosCreated;
    }

}