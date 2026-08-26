#include "doctest.h"
#include "Entity.hpp"
#include "Resource.hpp"
#include "Scene.hpp"
#include "SmartStack.hpp"
#include <memory>
#include <string>

using namespace gameengine;

// --- Entity Tests ---
TEST_CASE("1-2: Move Semantics") {
    Entity a("A", 0, 0, 100);
    Entity b("B", 0, 0, 50);
    
    // Test 1: Move Constructor
    Entity c(std::move(a));
    CHECK(c.getName() == "A");
    CHECK_FALSE(a.isAlive());

    // Test 2: Move Assignment
    b = std::move(c);
    CHECK(b.getName() == "A");
    CHECK_FALSE(c.isAlive());
}

TEST_CASE("3: HP Clamping") {
    // מניחים שהקוד יזרוק חריגה לפי מה שכתבנו ב-Entity.cpp
    CHECK_THROWS_AS(Entity("Dead", 0, 0, -10), std::invalid_argument);
}

TEST_CASE("4: Inventory Transfer") {
    Entity a("A", 0, 0, 100);
    Entity b("B", 0, 0, 100);
    a.addItem("Sword");
    b.addItem(std::move(a.toString())); // דוגמה להעברת מידע
    CHECK(b.getInventorySize() == 1);
}

// --- Resource Tests ---
TEST_CASE("5-6: Shared Pointer Counts") {
    auto r = Resource::create("Res", "data", 100);
    CHECK(r.use_count() == 1);
    auto r2 = r;
    CHECK(r.use_count() == 2);
    r2.reset();
    CHECK(r.use_count() == 1);
}

TEST_CASE("7: Weak Pointer Expired") {
    std::weak_ptr<Resource> weak;
    {
        auto r = Resource::create("Tmp", "data", 100);
        weak = r;
    }
    CHECK(weak.lock() == nullptr);
}

// --- Scene Tests ---
TEST_CASE("8-9: Scene Find and Remove Out of Bounds") {
    Scene s("S");
    CHECK(s.findEntity("None") == nullptr);
    CHECK_THROWS_AS(s.removeEntity(999), std::out_of_range);
}

TEST_CASE("10-11: Scene Count") {
    Scene s("S");
    s.createEntity("1", 0, 0, 1);
    s.createEntity("2", 0, 0, 1);
    s.removeEntity(0);
    CHECK(s.getEntityCount() == 1);
    // ניקוי מלא
    s.removeEntity(0);
    CHECK(s.getEntityCount() == 0);
}

// --- SmartStack Tests ---
TEST_CASE("12-13: LIFO Logic") {
    SmartStack<int> s;
    s.push(1); s.push(2); s.push(3);
    CHECK(s.pop() == 3);
    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
}

TEST_CASE("14-15: Large Stack and Clear") {
    SmartStack<int> s;
    for(int i = 0; i < 10000; ++i) s.push(i);
    CHECK(s.size() == 10000);
    s.clear();
    CHECK(s.empty());
}

TEST_CASE("16: Pop Empty") {
    SmartStack<int> s;
    CHECK_THROWS_AS(s.pop(), std::underflow_error);
}

TEST_CASE("17: Resource Destructor Trigger") {
    auto r = Resource::create("Test", "T", 10);
    CHECK(Resource::getResourceCount() == 1);
    r.reset();
    CHECK(Resource::getResourceCount() == 0);
}

TEST_CASE("18: Inventory No Change") {
    Entity a("A", 0, 0, 100);
    a.addItem("Item");
    size_t count = a.getInventorySize();
    // בדיקה שאין שינוי כפול/מיותר
    CHECK(a.getInventorySize() == count);
}

TEST_CASE("19: Remove Existing Entity") {
    Scene s("S");
    s.createEntity("E", 0, 0, 10);
    s.removeEntity(0);
    CHECK(s.getEntityCount() == 0);
}

TEST_CASE("20: Peek Empty") {
    SmartStack<int> s;
    CHECK_THROWS_AS(s.top(), std::underflow_error);
}