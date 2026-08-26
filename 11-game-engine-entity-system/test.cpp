/**
 * @file test.cpp
 * @brief Unit tests for Game Engine Entity System using doctest
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Entity.hpp"
#include "Resource.hpp"
#include "Scene.hpp"
#include "SmartStack.hpp"
#include <sstream>
#include <string>
#include <memory>
#include <vector>

using namespace gameengine;

// ==================== ENTITY TESTS ====================

TEST_CASE("Entity - Constructor") {
    Entity::resetIdCounter();
    Entity e("Hero", 1.0, 2.0, 100);
    CHECK(e.getName() == "Hero");
    CHECK(e.getX() == doctest::Approx(1.0));
    CHECK(e.getY() == doctest::Approx(2.0));
    CHECK(e.getHealth() == 100);
    CHECK(e.isAlive() == true);
    CHECK(e.getId() == 0);
}

TEST_CASE("Entity - Invalid Health Throws") {
    CHECK_THROWS_AS(Entity("Bad", 0, 0, 0), std::invalid_argument);
    CHECK_THROWS_AS(Entity("Bad", 0, 0, -10), std::invalid_argument);
}

TEST_CASE("Entity - Move Constructor") {
    Entity::resetIdCounter();
    Entity a("Alpha", 5.0, 10.0, 80);
    a.addItem("Sword");

    Entity b(std::move(a));
    CHECK(b.getName() == "Alpha");
    CHECK(b.getHealth() == 80);
    CHECK(b.getInventorySize() == 1);
    CHECK(b.isAlive() == true);

    CHECK(a.isAlive() == false);
    CHECK(a.getName() == "");
    CHECK(a.getId() == -1);
    CHECK(a.getHealth() == 0);
    CHECK(a.getInventorySize() == 0);
}

TEST_CASE("Entity - Move Assignment") {
    Entity::resetIdCounter();
    Entity a("Alpha", 1, 2, 100);
    Entity b("Beta", 3, 4, 50);

    b = std::move(a);
    CHECK(b.getName() == "Alpha");
    CHECK(b.getHealth() == 100);
    CHECK(b.isAlive() == true);

    CHECK(a.isAlive() == false);
}

TEST_CASE("Entity - Move Assignment Self") {
    Entity::resetIdCounter();
    Entity a("Alpha", 1, 2, 100);
    a = std::move(a);
    CHECK(a.getName() == "Alpha");
    CHECK(a.isAlive() == true);
}

TEST_CASE("Entity - Inventory") {
    Entity e("Hero", 0, 0, 100);
    e.addItem("Sword");
    e.addItem("Shield");
    CHECK(e.getInventorySize() == 2);
    CHECK(e.hasItem("Sword") == true);
    CHECK(e.hasItem("Bow") == false);
}

TEST_CASE("Entity - Inventory Move Add") {
    Entity e("Hero", 0, 0, 100);
    std::string item = "Potion";
    e.addItem(std::move(item));
    CHECK(e.hasItem("Potion") == true);
    CHECK(item.empty());
}

TEST_CASE("Entity - takeDamage") {
    Entity e("Hero", 0, 0, 100);
    e.takeDamage(30);
    CHECK(e.getHealth() == 70);
    e.takeDamage(200);
    CHECK(e.getHealth() == 0);
}

TEST_CASE("Entity - takeDamage invalid throws") {
    Entity e("Hero", 0, 0, 100);
    CHECK_THROWS_AS(e.takeDamage(0), std::invalid_argument);
    CHECK_THROWS_AS(e.takeDamage(-5), std::invalid_argument);
}

TEST_CASE("Entity - heal") {
    Entity e("Hero", 0, 0, 50);
    e.heal(20);
    CHECK(e.getHealth() == 70);
}

TEST_CASE("Entity - heal invalid throws") {
    Entity e("Hero", 0, 0, 100);
    CHECK_THROWS_AS(e.heal(0), std::invalid_argument);
    CHECK_THROWS_AS(e.heal(-5), std::invalid_argument);
}

TEST_CASE("Entity - setPosition") {
    Entity e("Hero", 0, 0, 100);
    e.setPosition(5.5, 3.2);
    CHECK(e.getX() == doctest::Approx(5.5));
    CHECK(e.getY() == doctest::Approx(3.2));
}

TEST_CASE("Entity - entityCount") {
    Entity::resetIdCounter();
    int before = Entity::getEntityCount();
    {
        Entity e("Temp", 0, 0, 100);
        CHECK(Entity::getEntityCount() == before + 1);
    }
    CHECK(Entity::getEntityCount() == before);
}

TEST_CASE("Entity - entityCount with move") {
    Entity::resetIdCounter();
    int before = Entity::getEntityCount();
    Entity a("A", 0, 0, 100);
    CHECK(Entity::getEntityCount() == before + 1);

    Entity b(std::move(a));
    CHECK(Entity::getEntityCount() == before + 1);  // count unchanged: transfer not creation
}

TEST_CASE("Entity - entityCount with move assignment") {
    Entity::resetIdCounter();
    int before = Entity::getEntityCount();
    Entity a("A", 0, 0, 100);
    Entity b("B", 0, 0, 50);
    CHECK(Entity::getEntityCount() == before + 2);

    b = std::move(a);
    // b's old entity is destroyed (count -1), a transfers to b (no change), a becomes moved-from
    CHECK(Entity::getEntityCount() == before + 1);
}

// ==================== RESOURCE TESTS ====================

TEST_CASE("Resource - Create") {
    auto r = Resource::create("texture", "texture", 1024);
    CHECK(r->getName() == "texture");
    CHECK(r->getType() == "texture");
    CHECK(r->getSizeBytes() == 1024);
    CHECK(r->isLoaded() == true);
}

TEST_CASE("Resource - Invalid Size Throws") {
    CHECK_THROWS_AS(Resource::create("bad", "texture", 0), std::invalid_argument);
    CHECK_THROWS_AS(Resource::create("bad", "texture", -100), std::invalid_argument);
}

TEST_CASE("Resource - Shared Ownership") {
    auto r1 = Resource::create("shared", "sound", 2048);
    CHECK(r1.use_count() == 1);

    auto r2 = r1;
    CHECK(r1.use_count() == 2);
    CHECK(r2.use_count() == 2);

    r2.reset();
    CHECK(r1.use_count() == 1);
}

TEST_CASE("Resource - resourceCount") {
    int before = Resource::getResourceCount();
    {
        auto r = Resource::create("temp", "shader", 512);
        CHECK(Resource::getResourceCount() == before + 1);
    }
    CHECK(Resource::getResourceCount() == before);
}

TEST_CASE("Resource - toString") {
    auto r = Resource::create("tex", "texture", 4096);
    CHECK(r->toString() == "tex (texture, 4096 bytes)");
}

// ==================== SCENE TESTS ====================

TEST_CASE("Scene - Constructor") {
    Scene s("TestScene");
    CHECK(s.getName() == "TestScene");
    CHECK(s.getEntityCount() == 0);
    CHECK(s.getResourceCount() == 0);
    CHECK(s.getObserverCount() == 0);
}

TEST_CASE("Scene - createEntity") {
    Scene s("Test");
    Entity* e = s.createEntity("Player", 1.0, 2.0, 100);
    CHECK(e != nullptr);
    CHECK(e->getName() == "Player");
    CHECK(s.getEntityCount() == 1);
}

TEST_CASE("Scene - addEntity (move)") {
    Scene s("Test");
    auto e = std::make_unique<Entity>("NPC", 3.0, 4.0, 50);
    s.addEntity(std::move(e));
    CHECK(s.getEntityCount() == 1);
    CHECK(e == nullptr);
}

TEST_CASE("Scene - removeEntity") {
    Scene s("Test");
    s.createEntity("A", 0, 0, 100);
    s.createEntity("B", 0, 0, 100);

    auto removed = s.removeEntity(0);
    CHECK(removed->getName() == "A");
    CHECK(s.getEntityCount() == 1);
}

TEST_CASE("Scene - removeEntity out of bounds throws") {
    Scene s("Test");
    CHECK_THROWS_AS(s.removeEntity(0), std::out_of_range);
    s.createEntity("A", 0, 0, 100);
    CHECK_THROWS_AS(s.removeEntity(-1), std::out_of_range);
    CHECK_THROWS_AS(s.removeEntity(1), std::out_of_range);
}

TEST_CASE("Scene - getEntity") {
    Scene s("Test");
    s.createEntity("Player", 0, 0, 100);
    Entity* e = s.getEntity(0);
    CHECK(e->getName() == "Player");
}

TEST_CASE("Scene - getEntity out of bounds throws") {
    Scene s("Test");
    CHECK_THROWS_AS(s.getEntity(0), std::out_of_range);
    s.createEntity("A", 0, 0, 100);
    CHECK_THROWS_AS(s.getEntity(-1), std::out_of_range);
    CHECK_THROWS_AS(s.getEntity(1), std::out_of_range);
}

TEST_CASE("Scene - findEntity") {
    Scene s("Test");
    s.createEntity("Hero", 0, 0, 100);
    s.createEntity("Villain", 0, 0, 50);

    CHECK(s.findEntity("Hero") != nullptr);
    CHECK(s.findEntity("Hero")->getName() == "Hero");
    CHECK(s.findEntity("Nobody") == nullptr);
}

TEST_CASE("Scene - addResource and getResource") {
    Scene s("Test");
    auto r = Resource::create("tex", "texture", 1024);
    s.addResource(r);
    CHECK(s.getResourceCount() == 1);
    CHECK(s.getResource(0)->getName() == "tex");
}

TEST_CASE("Scene - getResource out of bounds throws") {
    Scene s("Test");
    CHECK_THROWS_AS(s.getResource(0), std::out_of_range);
    auto r = Resource::create("tex", "texture", 1024);
    s.addResource(r);
    CHECK_THROWS_AS(s.getResource(-1), std::out_of_range);
    CHECK_THROWS_AS(s.getResource(1), std::out_of_range);
}

TEST_CASE("Scene - findResource") {
    Scene s("Test");
    auto r = Resource::create("tex", "texture", 1024);
    s.addResource(r);

    auto found = s.findResource("tex");
    CHECK(found != nullptr);
    CHECK(found->getName() == "tex");

    auto notFound = s.findResource("missing");
    CHECK(notFound == nullptr);
}

TEST_CASE("Scene - getResourceRefCount") {
    Scene s("Test");
    auto r = Resource::create("tex", "texture", 1024);
    s.addResource(r);
    // r (local) + scene's vector = 2
    CHECK(s.getResourceRefCount(0) == 2);
}

TEST_CASE("Scene - Observer (weak_ptr) alive") {
    Scene s("Test");
    auto r = Resource::create("sound", "sound", 2048);
    s.addResource(r);
    s.addObserver("watcher", r);

    CHECK(s.isObservedResourceAlive("watcher") == true);
    auto locked = s.lockObservedResource("watcher");
    CHECK(locked != nullptr);
    CHECK(locked->getName() == "sound");
}

TEST_CASE("Scene - Observer (weak_ptr) expired") {
    Scene s("Test");
    {
        auto r = Resource::create("temp_sound", "sound", 512);
        s.addObserver("temp_watcher", r);
        CHECK(s.isObservedResourceAlive("temp_watcher") == true);
    }
    // r is destroyed, weak_ptr should be expired
    CHECK(s.isObservedResourceAlive("temp_watcher") == false);
    auto locked = s.lockObservedResource("temp_watcher");
    CHECK(locked == nullptr);
}

TEST_CASE("Scene - Observer not found throws") {
    Scene s("Test");
    CHECK_THROWS_AS(s.isObservedResourceAlive("nonexistent"), std::invalid_argument);
    CHECK_THROWS_AS(s.lockObservedResource("nonexistent"), std::invalid_argument);
}

TEST_CASE("Scene - printSummary") {
    Scene s("Test");
    s.createEntity("Hero", 0, 0, 100);
    auto r = Resource::create("tex", "texture", 1024);
    s.addResource(r);
    s.addObserver("obs", r);

    std::ostringstream oss;
    s.printSummary(oss);
    std::string output = oss.str();

    CHECK(output.find("Test") != std::string::npos);
    CHECK(output.find("Hero") != std::string::npos);
    CHECK(output.find("tex") != std::string::npos);
    CHECK(output.find("obs") != std::string::npos);
}

TEST_CASE("Scene - Move Constructor") {
    Scene s1("Scene1");
    s1.createEntity("A", 0, 0, 100);

    Scene s2(std::move(s1));
    CHECK(s2.getName() == "Scene1");
    CHECK(s2.getEntityCount() == 1);
}

// ==================== SMARTSTACK TESTS ====================

TEST_CASE("SmartStack<int> - Push and Top") {
    SmartStack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    CHECK(s.size() == 3);
    CHECK(s.top() == 30);
}

TEST_CASE("SmartStack<int> - Pop") {
    SmartStack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    CHECK(s.pop() == 30);
    CHECK(s.pop() == 20);
    CHECK(s.pop() == 10);
    CHECK(s.empty());
}

TEST_CASE("SmartStack<int> - Pop Empty Throws") {
    SmartStack<int> s;
    CHECK_THROWS_AS(s.pop(), std::underflow_error);
}

TEST_CASE("SmartStack<int> - Top Empty Throws") {
    SmartStack<int> s;
    CHECK_THROWS_AS(s.top(), std::underflow_error);
    const SmartStack<int>& cs = s;
    CHECK_THROWS_AS(cs.top(), std::underflow_error);
}

TEST_CASE("SmartStack<int> - Mutable Top") {
    SmartStack<int> s;
    s.push(10);
    s.top() = 42;
    CHECK(s.top() == 42);
}

TEST_CASE("SmartStack<string> - Push and Pop") {
    SmartStack<std::string> s;
    s.push("hello");
    s.push("world");

    CHECK(s.top() == "world");
    CHECK(s.pop() == "world");
    CHECK(s.pop() == "hello");
}

TEST_CASE("SmartStack<string> - Move Push") {
    SmartStack<std::string> s;
    std::string item = "moved_item";
    s.push(std::move(item));
    CHECK(item.empty());
    CHECK(s.top() == "moved_item");
}

TEST_CASE("SmartStack - Move Constructor") {
    SmartStack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    SmartStack<int> s2(std::move(s1));
    CHECK(s2.size() == 3);
    CHECK(s2.top() == 3);
    CHECK(s1.empty());
    CHECK(s1.size() == 0);
}

TEST_CASE("SmartStack - Move Assignment") {
    SmartStack<int> s1;
    s1.push(10);
    s1.push(20);

    SmartStack<int> s2;
    s2.push(99);
    s2 = std::move(s1);

    CHECK(s2.size() == 2);
    CHECK(s2.top() == 20);
    CHECK(s1.empty());
}

TEST_CASE("SmartStack - toString") {
    SmartStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    CHECK(s.toString() == "[3, 2, 1]");
}

TEST_CASE("SmartStack - toString empty") {
    SmartStack<int> s;
    CHECK(s.toString() == "[]");
}

TEST_CASE("SmartStack - forEach") {
    SmartStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    std::vector<int> collected;
    s.forEach([&collected](const int& val) { collected.push_back(val); });

    CHECK(collected.size() == 3);
    CHECK(collected[0] == 3);  // top first
    CHECK(collected[1] == 2);
    CHECK(collected[2] == 1);
}

TEST_CASE("SmartStack - clear") {
    SmartStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    s.clear();
    CHECK(s.empty());
    CHECK(s.size() == 0);
}

TEST_CASE("SmartStack - no memory leaks (large stack)") {
    SmartStack<int> s;
    for (int i = 0; i < 10000; ++i) {
        s.push(i);
    }
    CHECK(s.size() == 10000);
    s.clear();
    CHECK(s.empty());
}

// ==================== STUDENT TEST FILE CHECK ====================

TEST_CASE("StudentTest - File exists") {
    std::ifstream f("StudentTest.cpp");
    CHECK_MESSAGE(f.good(), "StudentTest.cpp not found. You must create StudentTest.cpp with at least 20 test cases.");
}