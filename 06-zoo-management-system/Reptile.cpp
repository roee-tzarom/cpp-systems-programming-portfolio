#include "Reptile.hpp"
#include <iostream>
#include <stdexcept>

namespace zoo {

    Reptile::Reptile(const std::string& animalName, int animalAge, const std::string& animalSpecies, bool isVenomousValue, double lengthCm)
        // Passes the shared data (name, age, species) for initialization directly in the parent class (Animal) constructor
        : Animal(animalName, animalAge, animalSpecies), isVenomous(isVenomousValue), bodyLengthCm(lengthCm) {
        if (lengthCm <= 0.0) {
            throw std::invalid_argument("Body length must be strictly positive");
        }
        std::cout << "Reptile constructed: " << getName() << "\n";
    }

    Reptile::Reptile(const Reptile& otherReptile)
        // Explicitly calls the parent's Copy Constructor to copy its variables, then copies the rest
        : Animal(otherReptile), isVenomous(otherReptile.isVenomous), bodyLengthCm(otherReptile.bodyLengthCm) {
        std::cout << "Reptile copy-constructed: " << getName() << "\n";
    }

    Reptile::~Reptile() {
        std::cout << "Reptile destructed: " << getName() << "\n";
    }

    Reptile& Reptile::operator=(const Reptile& otherReptile) {
        // Prevents data deletion in case of Self-assignment (e.g.: snake = snake)
        if (this != &otherReptile) {
            // Use the parent class's assignment operator to handle name and age
            Animal::operator=(otherReptile);
            isVenomous = otherReptile.isVenomous;
            bodyLengthCm = otherReptile.bodyLengthCm;
        }
        return *this;
    }

    bool Reptile::getIsVenomous() const {
        return isVenomous;
    }

    double Reptile::getBodyLengthCm() const {
        return bodyLengthCm;
    }

    void Reptile::setVenomous(bool isVenomousValue) {
        isVenomous = isVenomousValue;
    }

    void Reptile::setBodyLengthCm(double lengthCm) {
        if (lengthCm <= 0.0) {
            throw std::invalid_argument("Body length must be strictly positive");
        }
        bodyLengthCm = lengthCm;
    }

    std::string Reptile::makeSound() const {
        if (isVenomous) {
            return "Hisss!";
        }
        return "...";
    }

    // Override of the virtual function. Allows polymorphism to work correctly in the Zoo's animal array
    std::string Reptile::getAnimalType() const {
        return "Reptile";
    }

    std::string Reptile::getDiet() const {
        if (isVenomous) {
            return "Rodents and eggs";
        }
        return "Insects and plants";
    }

}