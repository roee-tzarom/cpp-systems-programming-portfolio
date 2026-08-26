#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Container.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Algorithms.hpp"
#include <string>
#include <stdexcept>

using namespace containers;

TEST_CASE("1. Double capacity resize check with exotic strings") {
    Container<std::string> c;
    for (int i = 0; i < 10; ++i) {
        c.add("Quetzalcoatlus");
    }
    CHECK(c.getCount() == 10);
    CHECK(c.getCapacity() == 16);
}

TEST_CASE("2. Consecutive removeAt(0) until empty") {
    Container<std::string> c;
    c.add("Rlyeh");
    c.add("Brobdingnag");
    c.add("Xoloitzcuintli");
    
    c.removeAt(0);
    c.removeAt(0);
    c.removeAt(0);
    
    CHECK(c.isEmpty() == true);
    CHECK(c.getCount() == 0);
}

TEST_CASE("3. Clear retains capacity while resetting count") {
    Container<std::string> c;
    for (int i = 0; i < 5; ++i) {
        c.add("Llanfairpwllgwyngyll");
    }
    int capBefore = c.getCapacity();
    c.clear();
    
    CHECK(c.isEmpty() == true);
    CHECK(c.getCapacity() == capBefore);
    c.add("New Element");
    CHECK(c.getCount() == 1);
}

TEST_CASE("4. Stack interleaved push and pop operations") {
    Stack<std::string> s;
    s.push("Professor Pumpernickel");
    s.push("Sir Reginald Fluffybottom");
    s.pop();
    s.push("Guy Incognito");
    
    CHECK(s.size() == 2);
    CHECK(s.top() == "Guy Incognito");
}

TEST_CASE("5. Queue interleaved enqueue and dequeue operations") {
    Queue<std::string> q;
    q.enqueue("Madam Zazzles");
    q.enqueue("Captain Bartholomew Quirk");
    q.dequeue();
    q.enqueue("Professor Pumpernickel");
    
    CHECK(q.size() == 2);
    CHECK(q.front() == "Captain Bartholomew Quirk");
    CHECK(q.back() == "Professor Pumpernickel");
}

TEST_CASE("6. Modify Stack element via top reference") {
    Stack<std::string> s;
    s.push("Guy Incognito");
    s.top() = "Real Identity";
    
    CHECK(s.top() == "Real Identity");
}

TEST_CASE("7. Modify Queue elements via front and back references") {
    Queue<double> q;
    q.enqueue(-3.14159265359);
    q.enqueue(-2.71828182846);
    
    q.front() = -1.0;
    q.back() = -2.0;
    
    CHECK(q.dequeue() == doctest::Approx(-1.0));
    CHECK(q.dequeue() == doctest::Approx(-2.0));
}

TEST_CASE("8. Stack range-based for loop with funny names") {
    Stack<std::string> s;
    s.push("Guy");
    s.push("Incognito");
    
    std::string result = "";
    for (const std::string& name : s) {
        result += name;
    }
    
    CHECK(result == "GuyIncognito");
}

TEST_CASE("9. find algorithm exact match on last element") {
    Container<std::string> c;
    c.add("Quetzalcoatlus");
    c.add("Brobdingnag");
    c.add("Xoloitzcuintli");
    
    CHECK(find(c, std::string("Xoloitzcuintli")) == 2);
}

TEST_CASE("10. count algorithm with separated duplicates") {
    Container<std::string> c;
    c.add("Madam Zazzles");
    c.add("Guy Incognito");
    c.add("Madam Zazzles");
    c.add("Professor Pumpernickel");
    c.add("Madam Zazzles");
    
    CHECK(count(c, std::string("Madam Zazzles")) == 3);
}

TEST_CASE("11. contains algorithm logic check") {
    Container<std::string> c;
    c.add("Sir Reginald Fluffybottom");
    
    CHECK(contains(c, std::string("Sir Reginald Fluffybottom")) == true);
    CHECK(contains(c, std::string("Guy Incognito")) == false);
}

TEST_CASE("12. sum algorithm of high precision negative doubles") {
    Container<double> c;
    c.add(-3.14159265359);
    c.add(-2.71828182846);
    c.add(-1.61803398875);
    
    CHECK(sum(c) == doctest::Approx(-7.4779084708));
}

TEST_CASE("13. min algorithm evaluates extremely close negative doubles") {
    Container<double> c;
    c.add(-0.00000000001);
    c.add(-273.15);
    c.add(-3.14159265359);
    
    CHECK(min(c) == doctest::Approx(-273.15));
}

TEST_CASE("14. max algorithm evaluates extremely close negative doubles") {
    Container<double> c;
    c.add(-273.15);
    c.add(-3.14159265359);
    c.add(-0.00000000001);
    
    CHECK(max(c) == doctest::Approx(-0.00000000001));
}

TEST_CASE("15. transform algorithm mutates strings by appending suffix") {
    Container<std::string> c;
    c.add("Guy");
    c.add("Madam");
    
    transform(c, [](std::string& s) { s += " Tested"; });
    
    CHECK(c.get(0) == "Guy Tested");
    CHECK(c.get(1) == "Madam Tested");
}

TEST_CASE("16. filter algorithm using substring search") {
    Container<std::string> c;
    c.add("Sir Reginald Fluffybottom");
    c.add("Guy Incognito");
    c.add("Professor Pumpernickel");
    
    Container<std::string> filtered = filter(c, [](const std::string& s) { 
        return s.find("Fluffy") != std::string::npos; 
    });
    
    CHECK(filtered.getCount() == 1);
    CHECK(filtered.get(0) == "Sir Reginald Fluffybottom");
}

TEST_CASE("17. reverse algorithm on an even number of elements") {
    Container<std::string> c;
    c.add("A");
    c.add("B");
    c.add("C");
    c.add("D");
    
    reverse(c);
    
    CHECK(c.get(0) == "D");
    CHECK(c.get(1) == "C");
    CHECK(c.get(2) == "B");
    CHECK(c.get(3) == "A");
}

TEST_CASE("18. toString algorithm works with negative doubles formatting") {
    Container<double> c;
    c.add(-273.15);
    c.add(-3.14);
    
    std::string res = toString(c);
    CHECK(res == "[-273.15, -3.14]");
}

TEST_CASE("19. Chained algorithms: filter followed by transform") {
    Container<double> c;
    c.add(-1.0);
    c.add(-5.0);
    c.add(-10.0);
    
    Container<double> filtered = filter(c, [](const double& d) { return d < -2.0; });
    transform(filtered, [](double& d) { d *= -1.0; });
    
    CHECK(filtered.getCount() == 2);
    CHECK(filtered.get(0) == doctest::Approx(5.0));
    CHECK(filtered.get(1) == doctest::Approx(10.0));
}

TEST_CASE("20. Iterator equivalence operators check") {
    Container<int> c;
    c.add(42);
    
    auto beginIt = c.begin();
    auto endIt = c.end();
    
    CHECK(beginIt != endIt);
    ++beginIt;
    CHECK(beginIt == endIt);
}