/**
 * @file test.cpp
 * @brief Unit tests for Zoo Management System using doctest
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Animal.hpp"
#include "Mammal.hpp"
#include "Bird.hpp"
#include "Reptile.hpp"
#include "Zoo.hpp"
#include <fstream>

using namespace zoo;

// ==================== MAMMAL CLASS TESTS ====================

TEST_CASE("Mammal - Constructor and Getters") {
    Mammal m("Leo", 5, "Lion", false, 4);
    CHECK(m.getName() == "Leo");
    CHECK(m.getAge() == 5);
    CHECK(m.getSpecies() == "Lion");
    CHECK(m.getIsDomesticated() == false);
    CHECK(m.getNumberOfLegs() == 4);
}

TEST_CASE("Mammal - Invalid Age Throws") {
    CHECK_THROWS_AS(Mammal("Bad", -1, "Cat", true, 4), std::invalid_argument);
}

TEST_CASE("Mammal - Invalid Legs Throws") {
    CHECK_THROWS_AS(Mammal("Bad", 5, "Cat", true, -2), std::invalid_argument);
}

TEST_CASE("Mammal - Sound (Wild)") {
    Mammal m("Leo", 5, "Lion", false);
    CHECK(m.makeSound() == "Roar!");
}

TEST_CASE("Mammal - Sound (Domesticated)") {
    Mammal m("Kitty", 2, "Cat", true);
    CHECK(m.makeSound() == "Purr...");
}

TEST_CASE("Mammal - Animal Type") {
    Mammal m("Leo", 5, "Lion", false);
    CHECK(m.getAnimalType() == "Mammal");
}

TEST_CASE("Mammal - Diet (Wild)") {
    Mammal m("Leo", 5, "Lion", false);
    CHECK(m.getDiet() == "Meat");
}

TEST_CASE("Mammal - Diet (Domesticated)") {
    Mammal m("Kitty", 2, "Cat", true);
    CHECK(m.getDiet() == "Meat and plants");
}

TEST_CASE("Mammal - Copy Constructor") {
    Mammal m1("Leo", 5, "Lion", false, 4);
    Mammal m2(m1);
    CHECK(m2.getName() == "Leo");
    CHECK(m2.getAge() == 5);
    CHECK(m2.getSpecies() == "Lion");
    CHECK(m2.getIsDomesticated() == false);
    CHECK(m2.getNumberOfLegs() == 4);
}

TEST_CASE("Mammal - Setters") {
    Mammal m("Leo", 5, "Lion", false, 4);
    m.setName("Simba");
    m.setAge(3);
    m.setNumberOfLegs(4);
    m.setDomesticated(true);
    CHECK(m.getName() == "Simba");
    CHECK(m.getAge() == 3);
    CHECK(m.getIsDomesticated() == true);
}

TEST_CASE("Mammal - setAge Throws on Negative") {
    Mammal m("Leo", 5, "Lion", false);
    CHECK_THROWS_AS(m.setAge(-1), std::invalid_argument);
}

TEST_CASE("Mammal - setNumberOfLegs Throws on Negative") {
    Mammal m("Leo", 5, "Lion", false);
    CHECK_THROWS_AS(m.setNumberOfLegs(-3), std::invalid_argument);
}

// ==================== BIRD CLASS TESTS ====================

TEST_CASE("Bird - Constructor and Getters") {
    Bird b("Eddie", 3, "Eagle", true, 2.0);
    CHECK(b.getName() == "Eddie");
    CHECK(b.getAge() == 3);
    CHECK(b.getSpecies() == "Eagle");
    CHECK(b.getCanFly() == true);
    CHECK(b.getWingspanMeters() == doctest::Approx(2.0));
}

TEST_CASE("Bird - Invalid Age Throws") {
    CHECK_THROWS_AS(Bird("Bad", -1, "Eagle", true, 2.0), std::invalid_argument);
}

TEST_CASE("Bird - Invalid Wingspan Throws") {
    CHECK_THROWS_AS(Bird("Bad", 3, "Eagle", true, 0.0), std::invalid_argument);
    CHECK_THROWS_AS(Bird("Bad", 3, "Eagle", true, -1.0), std::invalid_argument);
}

TEST_CASE("Bird - Sound (Can Fly)") {
    Bird b("Eddie", 3, "Eagle", true, 2.0);
    CHECK(b.makeSound() == "Tweet tweet!");
}

TEST_CASE("Bird - Sound (Cannot Fly)") {
    Bird b("Tux", 5, "Penguin", false, 0.5);
    CHECK(b.makeSound() == "Squawk!");
}

TEST_CASE("Bird - Animal Type") {
    Bird b("Eddie", 3, "Eagle", true, 2.0);
    CHECK(b.getAnimalType() == "Bird");
}

TEST_CASE("Bird - Diet") {
    Bird b("Eddie", 3, "Eagle", true, 2.0);
    CHECK(b.getDiet() == "Seeds and insects");
}

TEST_CASE("Bird - Copy Constructor") {
    Bird b1("Eddie", 3, "Eagle", true, 2.0);
    Bird b2(b1);
    CHECK(b2.getName() == "Eddie");
    CHECK(b2.getAge() == 3);
    CHECK(b2.getSpecies() == "Eagle");
    CHECK(b2.getCanFly() == true);
    CHECK(b2.getWingspanMeters() == doctest::Approx(2.0));
}

TEST_CASE("Bird - Setters") {
    Bird b("Eddie", 3, "Eagle", true, 2.0);
    b.setWingspanMeters(2.5);
    b.setCanFly(false);
    CHECK(b.getWingspanMeters() == doctest::Approx(2.5));
    CHECK(b.getCanFly() == false);
}

TEST_CASE("Bird - setWingspanMeters Throws on Invalid") {
    Bird b("Eddie", 3, "Eagle", true, 2.0);
    CHECK_THROWS_AS(b.setWingspanMeters(0.0), std::invalid_argument);
    CHECK_THROWS_AS(b.setWingspanMeters(-1.0), std::invalid_argument);
}

// ==================== REPTILE CLASS TESTS ====================

TEST_CASE("Reptile - Constructor and Getters") {
    Reptile r("Sly", 2, "Cobra", true, 150.0);
    CHECK(r.getName() == "Sly");
    CHECK(r.getAge() == 2);
    CHECK(r.getSpecies() == "Cobra");
    CHECK(r.getIsVenomous() == true);
    CHECK(r.getBodyLengthCm() == doctest::Approx(150.0));
}

TEST_CASE("Reptile - Invalid Age Throws") {
    CHECK_THROWS_AS(Reptile("Bad", -1, "Cobra", true, 150.0), std::invalid_argument);
}

TEST_CASE("Reptile - Invalid Body Length Throws") {
    CHECK_THROWS_AS(Reptile("Bad", 2, "Cobra", true, 0.0), std::invalid_argument);
    CHECK_THROWS_AS(Reptile("Bad", 2, "Cobra", true, -5.0), std::invalid_argument);
}

TEST_CASE("Reptile - Sound (Venomous)") {
    Reptile r("Sly", 2, "Cobra", true, 150.0);
    CHECK(r.makeSound() == "Hisss!");
}

TEST_CASE("Reptile - Sound (Non-venomous)") {
    Reptile r("Shelly", 50, "Turtle", false, 80.0);
    CHECK(r.makeSound() == "...");
}

TEST_CASE("Reptile - Animal Type") {
    Reptile r("Sly", 2, "Cobra", true, 150.0);
    CHECK(r.getAnimalType() == "Reptile");
}

TEST_CASE("Reptile - Diet (Venomous)") {
    Reptile r("Sly", 2, "Cobra", true, 150.0);
    CHECK(r.getDiet() == "Rodents and eggs");
}

TEST_CASE("Reptile - Diet (Non-venomous)") {
    Reptile r("Shelly", 50, "Turtle", false, 80.0);
    CHECK(r.getDiet() == "Insects and plants");
}

TEST_CASE("Reptile - Copy Constructor") {
    Reptile r1("Sly", 2, "Cobra", true, 150.0);
    Reptile r2(r1);
    CHECK(r2.getName() == "Sly");
    CHECK(r2.getAge() == 2);
    CHECK(r2.getSpecies() == "Cobra");
    CHECK(r2.getIsVenomous() == true);
    CHECK(r2.getBodyLengthCm() == doctest::Approx(150.0));
}

TEST_CASE("Reptile - Setters") {
    Reptile r("Sly", 2, "Cobra", true, 150.0);
    r.setBodyLengthCm(200.0);
    r.setVenomous(false);
    CHECK(r.getBodyLengthCm() == doctest::Approx(200.0));
    CHECK(r.getIsVenomous() == false);
}

TEST_CASE("Reptile - setBodyLengthCm Throws on Invalid") {
    Reptile r("Sly", 2, "Cobra", true, 150.0);
    CHECK_THROWS_AS(r.setBodyLengthCm(0.0), std::invalid_argument);
    CHECK_THROWS_AS(r.setBodyLengthCm(-10.0), std::invalid_argument);
}

// ==================== ANIMAL DESCRIPTION TESTS ====================

TEST_CASE("Animal - getDescription (Mammal)") {
    Mammal m("Leo", 5, "Lion", false, 4);
    CHECK(m.getDescription() == "[Mammal] Leo (Lion), Age: 5, Sound: Roar!, Diet: Meat");
}

TEST_CASE("Animal - getDescription (Bird)") {
    Bird b("Eddie", 3, "Eagle", true, 2.0);
    CHECK(b.getDescription() == "[Bird] Eddie (Eagle), Age: 3, Sound: Tweet tweet!, Diet: Seeds and insects");
}

TEST_CASE("Animal - getDescription (Reptile)") {
    Reptile r("Sly", 2, "Cobra", true, 150.0);
    CHECK(r.getDescription() == "[Reptile] Sly (Cobra), Age: 2, Sound: Hisss!, Diet: Rodents and eggs");
}

// ==================== POLYMORPHISM TESTS ====================

TEST_CASE("Polymorphism - Base Pointer Sound") {
    Mammal m("Leo", 5, "Lion", false);
    Bird b("Eddie", 3, "Eagle", true, 2.0);
    Reptile r("Sly", 2, "Cobra", true, 150.0);

    Animal* a1 = &m;
    Animal* a2 = &b;
    Animal* a3 = &r;

    CHECK(a1->makeSound() == "Roar!");
    CHECK(a2->makeSound() == "Tweet tweet!");
    CHECK(a3->makeSound() == "Hisss!");
}

TEST_CASE("Polymorphism - Base Pointer Type") {
    Mammal m("Leo", 5, "Lion", false);
    Bird b("Eddie", 3, "Eagle", true, 2.0);

    Animal* a1 = &m;
    Animal* a2 = &b;

    CHECK(a1->getAnimalType() == "Mammal");
    CHECK(a2->getAnimalType() == "Bird");
}

// ==================== ZOO CLASS TESTS ====================

TEST_CASE("Zoo - Default Constructor") {
    Zoo z;
    CHECK(z.getZooName() == "Unnamed Zoo");
    CHECK(z.getCapacity() == 4);
    CHECK(z.getCount() == 0);
    CHECK(z.isEmpty());
}

TEST_CASE("Zoo - Parameterized Constructor") {
    Zoo z("My Zoo", 8);
    CHECK(z.getZooName() == "My Zoo");
    CHECK(z.getCapacity() == 8);
}

TEST_CASE("Zoo - Invalid Capacity Throws") {
    CHECK_THROWS_AS(Zoo("Bad", 0), std::invalid_argument);
    CHECK_THROWS_AS(Zoo("Bad", -5), std::invalid_argument);
}

TEST_CASE("Zoo - Add Animals") {
    Zoo z("Test Zoo");
    Mammal m("Leo", 5, "Lion", false);
    Bird b("Eddie", 3, "Eagle", true, 2.0);

    z.addAnimal(m);
    CHECK(z.getCount() == 1);
    CHECK_FALSE(z.isEmpty());

    z.addAnimal(b);
    CHECK(z.getCount() == 2);
}

TEST_CASE("Zoo - Resize on Overflow") {
    Zoo z("Small Zoo", 2);
    Mammal m1("A", 1, "Cat", true);
    Mammal m2("B", 2, "Dog", true);
    Mammal m3("C", 3, "Horse", false);

    z.addAnimal(m1);
    z.addAnimal(m2);
    CHECK(z.getCapacity() == 2);

    z.addAnimal(m3);  // triggers resize
    CHECK(z.getCapacity() == 4);
    CHECK(z.getCount() == 3);
}

TEST_CASE("Zoo - Find Animal") {
    Zoo z("Test Zoo");
    Mammal m("Leo", 5, "Lion", false);
    Bird b("Eddie", 3, "Eagle", true, 2.0);

    z.addAnimal(m);
    z.addAnimal(b);

    Animal* found = z.findAnimal("Eddie");
    CHECK(found != nullptr);
    CHECK(found->getName() == "Eddie");
    CHECK(found->getAnimalType() == "Bird");

    Animal* notFound = z.findAnimal("Nonexistent");
    CHECK(notFound == nullptr);
}

TEST_CASE("Zoo - Get Animal by Index") {
    Zoo z("Test Zoo");
    Mammal m("Leo", 5, "Lion", false);
    z.addAnimal(m);

    const Animal& a = z.getAnimal(0);
    CHECK(a.getName() == "Leo");

    CHECK_THROWS_AS(z.getAnimal(1), std::out_of_range);
    CHECK_THROWS_AS(z.getAnimal(-1), std::out_of_range);
}

TEST_CASE("Zoo - Remove Animal") {
    Zoo z("Test Zoo");
    Mammal m("Leo", 5, "Lion", false);
    Bird b("Eddie", 3, "Eagle", true, 2.0);
    Reptile r("Sly", 2, "Cobra", true, 150.0);

    z.addAnimal(m);
    z.addAnimal(b);
    z.addAnimal(r);

    z.removeAnimal(1);  // Remove Eddie
    CHECK(z.getCount() == 2);
    CHECK(z.getAnimal(0).getName() == "Leo");
    CHECK(z.getAnimal(1).getName() == "Sly");
}

TEST_CASE("Zoo - Remove Animal Invalid Index Throws") {
    Zoo z("Test Zoo");
    Mammal m("Leo", 5, "Lion", false);
    z.addAnimal(m);

    CHECK_THROWS_AS(z.removeAnimal(1), std::out_of_range);
    CHECK_THROWS_AS(z.removeAnimal(-1), std::out_of_range);
}

TEST_CASE("Zoo - Set Zoo Name") {
    Zoo z("Old Name");
    z.setZooName("New Name");
    CHECK(z.getZooName() == "New Name");
}

TEST_CASE("Zoo - Mixed Animal Types") {
    Zoo z("Mixed Zoo");
    Mammal m("Leo", 5, "Lion", false);
    Bird b("Tux", 5, "Penguin", false, 0.5);
    Reptile r("Shelly", 50, "Turtle", false, 80.0);

    z.addAnimal(m);
    z.addAnimal(b);
    z.addAnimal(r);

    CHECK(z.getCount() == 3);
    CHECK(z.getAnimal(0).getAnimalType() == "Mammal");
    CHECK(z.getAnimal(1).getAnimalType() == "Bird");
    CHECK(z.getAnimal(2).getAnimalType() == "Reptile");
}

// ==================== ANIMAL COUNT TESTS ====================

TEST_CASE("Animal - Static Count Tracking") {
    int countBefore = Animal::getAnimalCount();
    {
        Mammal m("Temp", 1, "Cat", true);
        CHECK(Animal::getAnimalCount() == countBefore + 1);
    }
    CHECK(Animal::getAnimalCount() == countBefore);
}

TEST_CASE("Animal - Count with Copy") {
    int countBefore = Animal::getAnimalCount();
    Mammal m1("Leo", 5, "Lion", false);
    CHECK(Animal::getAnimalCount() == countBefore + 1);

    Mammal m2(m1);
    CHECK(Animal::getAnimalCount() == countBefore + 2);
}

// ==================== ADDITIONAL EDGE CASE TESTS ====================

TEST_CASE("Mammal - Default Number of Legs") {
    Mammal m("Leo", 5, "Lion", false);
    CHECK(m.getNumberOfLegs() == 4);
}

TEST_CASE("Zoo - Total Zoos Created") {
    int before = Zoo::getTotalZoosCreated();
    {
        Zoo z1("Zoo A");
        Zoo z2("Zoo B");
        CHECK(Zoo::getTotalZoosCreated() == before + 2);
    }
    // Counter does not decrease when zoos are destroyed
    CHECK(Zoo::getTotalZoosCreated() == before + 2);
}

TEST_CASE("Zoo - Remove First Animal") {
    Zoo z("Test Zoo");
    Mammal m("Leo", 5, "Lion", false);
    Bird b("Eddie", 3, "Eagle", true, 2.0);

    z.addAnimal(m);
    z.addAnimal(b);

    z.removeAnimal(0);  // Remove first
    CHECK(z.getCount() == 1);
    CHECK(z.getAnimal(0).getName() == "Eddie");
}

TEST_CASE("Zoo - Remove Last Animal") {
    Zoo z("Test Zoo");
    Mammal m("Leo", 5, "Lion", false);
    Bird b("Eddie", 3, "Eagle", true, 2.0);

    z.addAnimal(m);
    z.addAnimal(b);

    z.removeAnimal(1);  // Remove last
    CHECK(z.getCount() == 1);
    CHECK(z.getAnimal(0).getName() == "Leo");
}

TEST_CASE("Zoo - Add Animal After Removal") {
    Zoo z("Test Zoo");
    Mammal m("Leo", 5, "Lion", false);
    Bird b("Eddie", 3, "Eagle", true, 2.0);

    z.addAnimal(m);
    z.removeAnimal(0);
    CHECK(z.getCount() == 0);
    CHECK(z.isEmpty());

    z.addAnimal(b);
    CHECK(z.getCount() == 1);
    CHECK(z.getAnimal(0).getName() == "Eddie");
}

TEST_CASE("StudentTest - File exists") {
    std::ifstream f("StudentTest.cpp");
    CHECK_MESSAGE(f.good(), "StudentTest.cpp not found. You must create StudentTest.cpp with at least 20 test cases.");
}