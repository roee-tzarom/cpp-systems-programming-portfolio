/**
 * @file Bird.hpp
 * @brief Header file for the Bird class
 *
 * This file contains the declaration of the Bird class, which inherits
 * from the abstract Animal class. It introduces specific properties like
 * ability to fly and wingspan.
 */

#ifndef BIRD_HPP
#define BIRD_HPP

#include "Animal.hpp"
#include <string>

namespace zoo {

    class Bird : public Animal {
    private:
        bool canFly;
        double wingspanMeters;

    public:
        // ============ Constructors & Destructor ============
        Bird(const std::string& animalName, int animalAge, const std::string& animalSpecies, bool canFlyValue, double wingspan);
        Bird(const Bird& otherBird);
        ~Bird() override;

        Bird& operator=(const Bird& otherBird);

        // ============ Getters & Setters ============
        bool getCanFly() const;
        double getWingspanMeters() const;

        void setCanFly(bool canFlyValue);
        void setWingspanMeters(double wingspan);

        // ============ Overridden Virtual Functions ============
        std::string makeSound() const override;
        std::string getAnimalType() const override;
        std::string getDiet() const override;
    };

} // namespace zoo

#endif // BIRD_HPP