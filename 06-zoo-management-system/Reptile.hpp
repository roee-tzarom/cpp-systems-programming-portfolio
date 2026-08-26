/**
 * @file Reptile.hpp
 * @brief Header file for the Reptile class
 *
 * This file contains the declaration of the Reptile class, which inherits
 * from the abstract Animal class. It introduces properties like venomous
 * status and body length.
 */

#ifndef REPTILE_HPP
#define REPTILE_HPP

#include "Animal.hpp"
#include <string>

namespace zoo {

    class Reptile : public Animal {
    private:
        bool isVenomous;
        double bodyLengthCm;

    public:
        // ============ Constructors & Destructor ============
        Reptile(const std::string& animalName, int animalAge, const std::string& animalSpecies, bool isVenomousValue, double lengthCm);
        Reptile(const Reptile& otherReptile);
        ~Reptile() override;

        Reptile& operator=(const Reptile& otherReptile);

        // ============ Getters & Setters ============
        bool getIsVenomous() const;
        double getBodyLengthCm() const;

        void setVenomous(bool isVenomousValue);
        void setBodyLengthCm(double lengthCm);

        // ============ Overridden Virtual Functions ============
        std::string makeSound() const override;
        std::string getAnimalType() const override;
        std::string getDiet() const override;
    };

} // namespace zoo

#endif // REPTILE_HPP