#include "Mammal.hpp"
#include <iostream>
#include <stdexcept>

namespace zoo {

    Mammal::Mammal(const std::string& animalName, int animalAge, const std::string& animalSpecies, bool isDomesticatedValue, int legsCount)
        // Passes the relevant data to the parent (Animal) and initializes the rest itself
        : Animal(animalName, animalAge, animalSpecies), isDomesticated(isDomesticatedValue), numberOfLegs(legsCount) {
        if (legsCount < 0) {
            throw std::invalid_argument("Number of legs cannot be negative");
        }
        std::cout << "Mammal constructed: " << getName() << "\n";
    }

    Mammal::Mammal(const Mammal& otherMammal)
        : Animal(otherMammal), isDomesticated(otherMammal.isDomesticated), numberOfLegs(otherMammal.numberOfLegs) {
        std::cout << "Mammal copy-constructed: " << getName() << "\n";
    }

    Mammal::~Mammal() {
        std::cout << "Mammal destructed: " << getName() << "\n";
    }

    Mammal& Mammal::operator=(const Mammal& otherMammal) {
        if (this != &otherMammal) {
            // Handle the Animal part before copying local fields
            Animal::operator=(otherMammal);
            isDomesticated = otherMammal.isDomesticated;
            numberOfLegs = otherMammal.numberOfLegs;
        }
        return *this;
    }

    bool Mammal::getIsDomesticated() const {
        return isDomesticated;
    }

    int Mammal::getNumberOfLegs() const {
        return numberOfLegs;
    }

    void Mammal::setDomesticated(bool isDomesticatedValue) {
        isDomesticated = isDomesticatedValue;
    }

    void Mammal::setNumberOfLegs(int legsCount) {
        if (legsCount < 0) {
            throw std::invalid_argument("Number of legs cannot be negative");
        }
        numberOfLegs = legsCount;
    }

    std::string Mammal::makeSound() const {
        if (isDomesticated) {
            return "Purr...";
        }
        return "Roar!";
    }

    std::string Mammal::getAnimalType() const {
        return "Mammal";
    }

    std::string Mammal::getDiet() const {
        if (isDomesticated) {
            return "Meat and plants";
        }
        return "Meat";
    }

}