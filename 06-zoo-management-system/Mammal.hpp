/**
 * @file Mammal.hpp
 * @brief Header file for the Mammal class
 *
 * This file contains the declaration of the Mammal class, which inherits
 * from the abstract Animal class. It demonstrates inheritance and overriding
 * of pure virtual functions.
 */

#ifndef MAMMAL_HPP
#define MAMMAL_HPP

#include "Animal.hpp"
#include <string>

namespace zoo {

    class Mammal : public Animal {
    private:
        bool isDomesticated;
        int numberOfLegs;

    public:
        // ============ Constructors & Destructor ============
        Mammal(const std::string& animalName, int animalAge, const std::string& animalSpecies, bool isDomesticatedValue, int legsCount = 4);
        Mammal(const Mammal& otherMammal);
        ~Mammal() override;

        Mammal& operator=(const Mammal& otherMammal);

        // ============ Getters & Setters ============
        bool getIsDomesticated() const;
        int getNumberOfLegs() const;

        void setDomesticated(bool isDomesticatedValue);
        void setNumberOfLegs(int legsCount);

        // ============ Overridden Virtual Functions ============
        std::string makeSound() const override;
        std::string getAnimalType() const override;
        std::string getDiet() const override;
    };

} // namespace zoo

#endif // MAMMAL_HPP