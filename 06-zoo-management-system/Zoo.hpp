/**
 * @file Zoo.hpp
 * @brief Header file for the Zoo management class
 *
 * This file contains the declaration of the Zoo class, which manages a dynamic
 * polymorphic array of Animal pointers. It handles dynamic memory allocation,
 * deep copying, and polymorphic method delegation.
 */

#ifndef ZOO_HPP
#define ZOO_HPP

#include "Animal.hpp"
#include <string>

namespace zoo {

    class Zoo {
    private:
        std::string zooName;
        int capacity;
        int count;
        Animal** animals;

        static int totalZoosCreated;

        /**
         * @brief Doubles the capacity of the animals array when full
         */
        void resize();

    public:
        // ============ Constructors & Destructor ============
        explicit Zoo(const std::string& name = "Unnamed Zoo", int initialCapacity = 4);
        Zoo(const Zoo& otherZoo);
        ~Zoo();

        Zoo& operator=(const Zoo& otherZoo);

        // ============ Getters & Setters ============
        std::string getZooName() const;
        void setZooName(const std::string& name);
        int getCapacity() const;
        int getCount() const;
        bool isEmpty() const;

        // ============ Zoo Management ============
        void addAnimal(const Animal& newAnimal);
        Animal* findAnimal(const std::string& animalName) const;
        const Animal& getAnimal(int targetIndex) const;
        void removeAnimal(int targetIndex);

        // ============ Polymorphic Actions ============
        void printAllAnimals() const;
        void makeAllSounds() const;

        // ============ Static Methods ============
        static int getTotalZoosCreated();
    };

} // namespace zoo

#endif // ZOO_HPP