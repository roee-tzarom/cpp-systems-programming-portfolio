/**
 * @file main.cpp
 * @brief Demo for Zoo Management System
 */

#include <iostream>
#include "Animal.hpp"
#include "Mammal.hpp"
#include "Bird.hpp"
#include "Reptile.hpp"
#include "Zoo.hpp"

using namespace zoo;

int main() {
    std::cout << "===== Zoo Management System Demo =====\n\n";

    // ---- Section 1: Creating animals and demonstrating ctor order ----
    std::cout << "--- Creating Animals ---\n";

    Mammal lion("Leo", 5, "Lion", false, 4);
    // Expected output:
    // Lion Animal constructed: Leo
    // Mammal constructed: Leo

    Bird eagle("Eddie", 3, "Eagle", true, 2.0);
    // Expected output:
    // Eagle Animal constructed: Eddie
    // Bird constructed: Eddie

    Reptile snake("Sly", 2, "Cobra", true, 150.0);
    // Expected output:
    // Cobra Animal constructed: Sly
    // Reptile constructed: Sly

    std::cout << "\n--- Animal Details ---\n";
    std::cout << lion.getDescription() << "\n";
    // Expected: [Mammal] Leo (Lion), Age: 5, Sound: Roar!, Diet: Meat

    std::cout << eagle.getDescription() << "\n";
    // Expected: [Bird] Eddie (Eagle), Age: 3, Sound: Tweet tweet!, Diet: Seeds and insects

    std::cout << snake.getDescription() << "\n";
    // Expected: [Reptile] Sly (Cobra), Age: 2, Sound: Hisss!, Diet: Rodents and eggs

    // ---- Section 2: Demonstrating pure virtual / polymorphism ----
    std::cout << "\n--- Polymorphism via Base Pointer ---\n";

    Animal* animalPtr = &lion;
    std::cout << animalPtr->makeSound() << "\n";
    // Expected: Roar!

    animalPtr = &eagle;
    std::cout << animalPtr->makeSound() << "\n";
    // Expected: Tweet tweet!

    animalPtr = &snake;
    std::cout << animalPtr->makeSound() << "\n";
    // Expected: Hisss!

    // ---- Section 3: Static counter ----
    std::cout << "\n--- Animal Count ---\n";
    std::cout << "Total animals: " << Animal::getAnimalCount() << "\n";
    // Expected: Total animals: 3

    // ---- Section 4: Copy constructor (demonstrates ctor order again) ----
    std::cout << "\n--- Copy Constructor ---\n";
    Mammal lionCopy(lion);
    // Expected output:
    // Lion Animal copy-constructed: Leo
    // Mammal copy-constructed: Leo

    std::cout << "Original: " << lion.getName() << ", Copy: " << lionCopy.getName() << "\n";
    // Expected: Original: Leo, Copy: Leo

    std::cout << "Total animals after copy: " << Animal::getAnimalCount() << "\n";
    // Expected: Total animals after copy: 4

    // ---- Section 5: Zoo management ----
    std::cout << "\n--- Creating Zoo ---\n";
    {
        Zoo myZoo("Safari World", 2);

        Mammal cat("Whiskers", 3, "Cat", true, 4);
        // Expected output:
        // Cat Animal constructed: Whiskers
        // Mammal constructed: Whiskers

        Bird penguin("Tux", 5, "Penguin", false, 0.5);
        // Expected output:
        // Penguin Animal constructed: Tux
        // Bird constructed: Tux

        Reptile turtle("Shelly", 50, "Turtle", false, 80.0);
        // Expected output:
        // Turtle Animal constructed: Shelly
        // Reptile constructed: Shelly

        myZoo.addAnimal(cat);
        // Expected output (copy ctor):
        // Cat Animal copy-constructed: Whiskers
        // Mammal copy-constructed: Whiskers

        myZoo.addAnimal(penguin);
        // Expected output (copy ctor):
        // Penguin Animal copy-constructed: Tux
        // Bird copy-constructed: Tux

        myZoo.addAnimal(turtle);  // triggers resize
        // Expected output (copy ctor):
        // Turtle Animal copy-constructed: Shelly
        // Reptile copy-constructed: Shelly

        std::cout << "\n--- Zoo Contents ---\n";
        myZoo.printAllAnimals();
        // Expected:
        // === Safari World ===
        // 1. [Mammal] Whiskers (Cat), Age: 3, Sound: Purr..., Diet: Meat and plants
        // 2. [Bird] Tux (Penguin), Age: 5, Sound: Squawk!, Diet: Seeds and insects
        // 3. [Reptile] Shelly (Turtle), Age: 50, Sound: ..., Diet: Insects and plants

        std::cout << "\n--- All Sounds ---\n";
        myZoo.makeAllSounds();
        // Expected:
        // Whiskers says: Purr...
        // Tux says: Squawk!
        // Shelly says: ...

        std::cout << "\n--- Find Animal ---\n";
        Animal* found = myZoo.findAnimal("Tux");
        if (found) {
            std::cout << "Found: " << found->getDescription() << "\n";
            // Expected: Found: [Bird] Tux (Penguin), Age: 5, Sound: Squawk!, Diet: Seeds and insects
        }

        std::cout << "\n--- Remove Animal ---\n";
        myZoo.removeAnimal(0);
        // Expected (dtor for the removed Mammal copy):
        // Mammal destructed: Whiskers
        // Cat Animal destructed: Whiskers

        std::cout << "Zoo count after removal: " << myZoo.getCount() << "\n";
        // Expected: Zoo count after removal: 2

        std::cout << "\n--- Zoo Destructor (end of scope) ---\n";
    }

    // ---- Section 6: Demonstrating dtor order ----
    std::cout << "\n--- Destructor Order (end of main) ---\n";

    return 0;
}