#include "Bird.hpp"
#include <iostream>
#include <stdexcept>

namespace zoo {

    Bird::Bird(const std::string& animalName, int animalAge, const std::string& animalSpecies, bool canFlyValue, double wingspan)
        // Explicit call (Initializer list) to the parent Animal class constructor to initialize shared properties
        : Animal(animalName, animalAge, animalSpecies), canFly(canFlyValue), wingspanMeters(wingspan) {
        if (wingspan <= 0.0) {
            throw std::invalid_argument("Wingspan must be strictly positive");
        }
        std::cout << "Bird constructed: " << getName() << "\n";
    }

    Bird::Bird(const Bird& otherBird)
        // Call the parent's Copy Constructor so it copies the name, age, and species
        : Animal(otherBird), canFly(otherBird.canFly), wingspanMeters(otherBird.wingspanMeters) {
        std::cout << "Bird copy-constructed: " << getName() << "\n";
    }

    Bird::~Bird() {
        std::cout << "Bird destructed: " << getName() << "\n";
    }

    Bird& Bird::operator=(const Bird& otherBird) {
        if (this != &otherBird) {
            // Call the parent's assignment operator to handle its variables
            Animal::operator=(otherBird);
            canFly = otherBird.canFly;
            wingspanMeters = otherBird.wingspanMeters;
        }
        return *this;
    }

    bool Bird::getCanFly() const {
        return canFly;
    }

    double Bird::getWingspanMeters() const {
        return wingspanMeters;
    }

    void Bird::setCanFly(bool canFlyValue) {
        canFly = canFlyValue;
    }

    void Bird::setWingspanMeters(double wingspan) {
        if (wingspan <= 0.0) {
            throw std::invalid_argument("Wingspan must be strictly positive");
        }
        wingspanMeters = wingspan;
    }

    // Override of the pure virtual function from the parent class
    std::string Bird::makeSound() const {
        if (canFly) {
            return "Tweet tweet!";
        }
        return "Squawk!";
    }

    std::string Bird::getAnimalType() const {
        return "Bird";
    }

    std::string Bird::getDiet() const {
        return "Seeds and insects";
    }

}