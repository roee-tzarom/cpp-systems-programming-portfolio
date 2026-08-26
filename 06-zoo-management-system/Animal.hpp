/**
 * @file Animal.hpp
 * @brief Header file for the abstract base class Animal
 *
 * This file contains the declaration of the Animal class, which serves as
 * the base class for all specific animal types in the zoo. It enforces
 * polymorphism through pure virtual functions.
 */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

namespace zoo {

    class Animal {
    private:
        std::string name;
        int age;
        std::string species;

        // Static counter to track the total number of Animal objects currently alive
        static int animalCount;

    public:
        // ============ Constructors & Destructor ============
        Animal(const std::string& animalName, int animalAge, const std::string& animalSpecies);
        Animal(const Animal& otherAnimal);
        
        // Virtual destructor is strictly required for polymorphic deletion
        virtual ~Animal();

        // Assignment operator
        Animal& operator=(const Animal& otherAnimal);

        // ============ Getters ============
        std::string getName() const;
        int getAge() const;
        std::string getSpecies() const;

        // ============ Setters ============
        void setName(const std::string& newName);
        void setAge(int newAge);

        // ============ Pure Virtual Functions (Abstract Interface) ============
        virtual std::string makeSound() const = 0;
        virtual std::string getAnimalType() const = 0;
        virtual std::string getDiet() const = 0;

        // ============ Virtual Functions ============
        virtual std::string getDescription() const;

        // ============ Static Methods ============
        static int getAnimalCount();
    };

} // namespace zoo

#endif // ANIMAL_HPP