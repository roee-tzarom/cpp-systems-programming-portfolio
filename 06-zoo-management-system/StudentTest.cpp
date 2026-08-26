#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Mammal.hpp"
#include "Bird.hpp"
#include "Reptile.hpp"
#include "Zoo.hpp"
#include <stdexcept>

using namespace zoo;

TEST_CASE("1. Zoo deep copy preserves polymorphic types") {
    Zoo originalZoo("WildSphere", 2);
    Mammal wolfAnimal("Rogue", 4, "Wolf", false, 4);
    originalZoo.addAnimal(wolfAnimal);
    
    Zoo copiedZoo(originalZoo);
    copiedZoo.setZooName("Arkadia Haven");
    
    CHECK(originalZoo.getZooName() == "WildSphere");
    CHECK(copiedZoo.getZooName() == "Arkadia Haven");
    CHECK(copiedZoo.getAnimal(0).getName() == "Rogue");
    CHECK(copiedZoo.getAnimal(0).getAnimalType() == "Mammal");
}

TEST_CASE("2. Zoo assignment operator overwrites memory correctly") {
    Zoo firstZoo("BioPulse Park", 2);
    Zoo secondZoo("Terra Wilds", 5);
    Reptile crocodileAnimal("Titan", 12, "Crocodile", false, 450.0);
    firstZoo.addAnimal(crocodileAnimal);
    
    secondZoo = firstZoo;
    
    CHECK(secondZoo.getCount() == 1);
    CHECK(secondZoo.getZooName() == "BioPulse Park");
    CHECK(secondZoo.getAnimal(0).getName() == "Titan");
}

TEST_CASE("3. Dynamic resize beyond initial capacity works perfectly") {
    Zoo expandingZoo("The Oasis Hub", 1);
    Bird ravenAnimal("Echo", 3, "Raven", true, 1.2);
    Bird kingfisherAnimal("Piper", 2, "Kingfisher", true, 0.3);
    Bird falconAnimal("Icarus", 4, "Falcon", true, 1.1);
    
    expandingZoo.addAnimal(ravenAnimal);
    expandingZoo.addAnimal(kingfisherAnimal);
    expandingZoo.addAnimal(falconAnimal);
    
    CHECK(expandingZoo.getCapacity() >= 3);
    CHECK(expandingZoo.getCount() == 3);
    CHECK(expandingZoo.getAnimal(2).getName() == "Icarus");
}

TEST_CASE("4. Mammal constructor throws on negative age") {
    CHECK_THROWS_AS(Mammal("Atlas", -5, "Elephant", false, 4), std::invalid_argument);
}

TEST_CASE("5. Mammal constructor throws on negative legs") {
    CHECK_THROWS_AS(Mammal("Vibe", 7, "Sloth", true, -2), std::invalid_argument);
}

TEST_CASE("6. Bird constructor throws on zero wingspan") {
    CHECK_THROWS_AS(Bird("Nova", 5, "Owl", true, 0.0), std::invalid_argument);
}

TEST_CASE("7. Reptile constructor throws on negative body length") {
    CHECK_THROWS_AS(Reptile("Slink", 2, "Snake", true, -10.5), std::invalid_argument);
}

TEST_CASE("8. Zoo constructor throws on zero or negative capacity") {
    CHECK_THROWS_AS(Zoo("WildSphere", 0), std::invalid_argument);
    CHECK_THROWS_AS(Zoo("Arkadia Haven", -10), std::invalid_argument);
}

TEST_CASE("9. Removing animal out of positive bounds throws") {
    Zoo limitsZoo("BioPulse Park", 5);
    Mammal pandaAnimal("Cinder", 3, "Red Panda", true, 4);
    limitsZoo.addAnimal(pandaAnimal);
    
    CHECK_THROWS_AS(limitsZoo.removeAnimal(1), std::out_of_range);
    CHECK_THROWS_AS(limitsZoo.removeAnimal(50), std::out_of_range);
}

TEST_CASE("10. Removing animal out of negative bounds throws") {
    Zoo negativeBoundsZoo("Terra Wilds", 5);
    CHECK_THROWS_AS(negativeBoundsZoo.removeAnimal(-1), std::out_of_range);
}

TEST_CASE("11. Getting animal out of bounds throws") {
    Zoo emptySearchZoo("The Oasis Hub", 5);
    CHECK_THROWS_AS(emptySearchZoo.getAnimal(0), std::out_of_range);
}

TEST_CASE("12. Find animal returns correct pointer for existing animal") {
    Zoo finderZoo("WildSphere", 5);
    Reptile dragonAnimal("Rex", 8, "Komodo Dragon", true, 250.0);
    finderZoo.addAnimal(dragonAnimal);
    
    Animal* found = finderZoo.findAnimal("Rex");
    CHECK(found != nullptr);
    CHECK(found->getSpecies() == "Komodo Dragon");
}

TEST_CASE("13. Find animal returns nullptr for non-existent animal") {
    Zoo finderZoo("Arkadia Haven", 5);
    Animal* missing = finderZoo.findAnimal("Koda");
    CHECK(missing == nullptr);
}

TEST_CASE("14. Animal static count updates correctly on scope exit") {
    int initialCount = Animal::getAnimalCount();
    {
        Bird macawAnimal("Azure", 10, "Macaw", true, 0.9);
        CHECK(Animal::getAnimalCount() == initialCount + 1);
    }
    CHECK(Animal::getAnimalCount() == initialCount);
}

TEST_CASE("15. Reptile sound behavior changes based on venomous trait") {
    Reptile dangerSnake("Slink", 2, "Snake", true, 120.0);
    Reptile safeIguana("Jade", 4, "Iguana", false, 60.0);
    
    CHECK(dangerSnake.makeSound() == "Hisss!");
    CHECK(safeIguana.makeSound() == "...");
}

TEST_CASE("16. Bird sound behavior changes based on flying capability") {
    Bird flyingHummingbird("Blitz", 1, "Hummingbird", true, 0.1);
    Bird nonFlyingBird("Echo", 3, "Raven", false, 1.2);
    
    CHECK(flyingHummingbird.makeSound() == "Tweet tweet!");
    CHECK(nonFlyingBird.makeSound() == "Squawk!");
}

TEST_CASE("17. Mammal sound behavior changes based on domestication") {
    Mammal petBear("Koda", 5, "Bear", true, 4);
    Mammal wildLeopard("Zenith", 6, "Snow Leopard", false, 4);
    
    CHECK(petBear.makeSound() == "Purr...");
    CHECK(wildLeopard.makeSound() == "Roar!");
}

TEST_CASE("18. Diet verification across all polymorphic types") {
    Mammal domesticatedSloth("Vibe", 7, "Sloth", true);
    Mammal wildWolf("Rogue", 4, "Wolf", false);
    Bird flyingFalcon("Icarus", 4, "Falcon", true, 1.1);
    Reptile venomousSnake("Slink", 2, "Snake", true, 120.0);
    Reptile safeTortoise("Apollo", 50, "Tortoise", false, 50.0);
    
    CHECK(domesticatedSloth.getDiet() == "Meat and plants");
    CHECK(wildWolf.getDiet() == "Meat");
    CHECK(flyingFalcon.getDiet() == "Seeds and insects");
    CHECK(venomousSnake.getDiet() == "Rodents and eggs");
    CHECK(safeTortoise.getDiet() == "Insects and plants");
}

TEST_CASE("19. Exact description string formatting check") {
    Mammal redPanda("Cinder", 3, "Red Panda", true, 4);
    std::string expected = "[Mammal] Cinder (Red Panda), Age: 3, Sound: Purr..., Diet: Meat and plants";
    CHECK(redPanda.getDescription() == expected);
}

TEST_CASE("20. Setters throw exceptions correctly after instantiation") {
    Mammal snowLeopard("Zenith", 6, "Snow Leopard", false, 4);
    CHECK_THROWS_AS(snowLeopard.setAge(-10), std::invalid_argument);
    CHECK_THROWS_AS(snowLeopard.setNumberOfLegs(-1), std::invalid_argument);
    
    Bird owl("Nova", 5, "Owl", true, 1.0);
    CHECK_THROWS_AS(owl.setWingspanMeters(0.0), std::invalid_argument);
    
    Reptile chameleon("Glint", 2, "Chameleon", false, 15.0);
    CHECK_THROWS_AS(chameleon.setBodyLengthCm(-5.0), std::invalid_argument);
}

TEST_CASE("21. Zoo count increments correctly when new zoos are created") {
    int startingZoos = Zoo::getTotalZoosCreated();
    Zoo bioPulseTemp("BioPulse Park", 2);
    Zoo terraWildsTemp("Terra Wilds", 2);
    CHECK(Zoo::getTotalZoosCreated() == startingZoos + 2);
}