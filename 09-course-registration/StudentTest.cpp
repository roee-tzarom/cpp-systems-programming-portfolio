/**
 * @file StudentTest.cpp
 * @brief 20+ Custom unit tests for the Registration System based on AI generated data.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "StringUtils.hpp"
#include "StudentRecord.hpp"
#include "CourseManager.hpp"
#include <vector>
#include <stdexcept>

using namespace registration;

// ==================== Text Processing Tests ====================

TEST_CASE("StudentTest 1: Palindrome - Valid simple word") {
    CHECK(isPalindrome("racecar") == true);
}

TEST_CASE("StudentTest 2: Palindrome - Invalid word") {
    CHECK(isPalindrome("course") == false);
}

TEST_CASE("StudentTest 3: Palindrome - With spaces and mixed case") {
    CHECK(isPalindrome("A man a plan a canal Panama") == true);
}

TEST_CASE("StudentTest 4: Sentence Splitting - Standard separation") {
    auto res = split("Welcome,Read", ',');
    CHECK(res.size() == 2);
    CHECK(res[0] == "Welcome");
    CHECK(res[1] == "Read");
}

TEST_CASE("StudentTest 5: Sentence Splitting - Multiple parts") {
    auto res = split("Yes,No,Good luck", ',');
    CHECK(res.size() == 3);
    CHECK(res[0] == "Yes");
    CHECK(res[2] == "Good luck");
}

TEST_CASE("StudentTest 6: Sentence Splitting - No delimiter present") {
    auto res = split("Just one single sentence", ',');
    CHECK(res.size() == 1);
    CHECK(res[0] == "Just one single sentence");
}

TEST_CASE("StudentTest 7: Whitespace - Remove leading and trailing") {
    CHECK(trim("   Student Name   ") == "Student Name");
}

TEST_CASE("StudentTest 8: Whitespace - Internal spaces are untouched") {
    // Our trim only targets edges, verifying internal spaces remain
    CHECK(trim("Intro   to     CS") == "Intro   to     CS");
}

TEST_CASE("StudentTest 9: Whitespace - Only spaces becomes empty") {
    CHECK(trim("      ") == "");
}

// ==================== Student Grades Tests ====================

TEST_CASE("StudentTest 10: Finding Average - Standard list") {
    std::vector<StudentRecord> v = {
        createRecord("A", 1, 80), createRecord("B", 2, 90), createRecord("C", 3, 100)
    };
    CHECK(averageGrade(v) == doctest::Approx(90.0));
}

TEST_CASE("StudentTest 11: Finding Average - Decimal results") {
    std::vector<StudentRecord> v = {
        createRecord("A", 1, 85), createRecord("B", 2, 86), createRecord("C", 3, 88)
    };
    CHECK(averageGrade(v) == doctest::Approx(86.333333));
}

TEST_CASE("StudentTest 12: Finding Average - Empty list throws exception") {
    std::vector<StudentRecord> v;
    CHECK_THROWS_AS(averageGrade(v), std::invalid_argument);
}

TEST_CASE("StudentTest 13: Highest Grade - Standard list") {
    std::vector<StudentRecord> v = {
        createRecord("A", 1, 75), createRecord("B", 2, 92), 
        createRecord("C", 3, 88), createRecord("D", 4, 100), 
        createRecord("E", 5, 64)
    };
    CHECK(getGrade(bestStudent(v)) == doctest::Approx(100.0));
}

TEST_CASE("StudentTest 14: Highest Grade - Single student") {
    std::vector<StudentRecord> v = { createRecord("A", 1, 85) };
    CHECK(getGrade(bestStudent(v)) == doctest::Approx(85.0));
}

TEST_CASE("StudentTest 15: Highest Grade - Identical grades returns first") {
    std::vector<StudentRecord> v = {
        createRecord("A", 1, 90), createRecord("B", 2, 90), createRecord("C", 3, 90)
    };
    CHECK(getName(bestStudent(v)) == "A");
    CHECK(getGrade(bestStudent(v)) == doctest::Approx(90.0));
}

// ==================== Sets (Lists of Numbers) Tests ====================

TEST_CASE("StudentTest 16: Union - Combining without duplicates") {
    CourseManager cm;
    for(int i=1; i<=5; ++i) cm.addStudent(createRecord("S", i, 90));
    cm.createCourse("ListA"); cm.createCourse("ListB");
    
    cm.enrollStudent(1, "ListA"); cm.enrollStudent(2, "ListA"); cm.enrollStudent(3, "ListA");
    cm.enrollStudent(3, "ListB"); cm.enrollStudent(4, "ListB"); cm.enrollStudent(5, "ListB");
    
    auto u = cm.studentsInEitherCourse("ListA", "ListB");
    CHECK(u.size() == 5);
    CHECK(u == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("StudentTest 17: Union - Completely separate lists") {
    CourseManager cm;
    cm.addStudent(createRecord("S", 10, 90)); cm.addStudent(createRecord("S", 20, 90));
    cm.addStudent(createRecord("S", 30, 90)); cm.addStudent(createRecord("S", 40, 90));
    cm.addStudent(createRecord("S", 50, 90));
    
    cm.createCourse("ListA"); cm.createCourse("ListB");
    cm.enrollStudent(10, "ListA"); cm.enrollStudent(20, "ListA"); cm.enrollStudent(30, "ListA");
    cm.enrollStudent(40, "ListB"); cm.enrollStudent(50, "ListB");
    
    auto u = cm.studentsInEitherCourse("ListA", "ListB");
    CHECK(u.size() == 5);
    CHECK(u == std::vector<int>{10, 20, 30, 40, 50});
}

TEST_CASE("StudentTest 18: Union - Error on duplicate insertion to same list") {
    CourseManager cm;
    cm.addStudent(createRecord("S", 1, 90));
    cm.createCourse("ListA");
    cm.enrollStudent(1, "ListA");
    
    // Verifying that our system protects against the duplicates the AI mentioned
    CHECK_THROWS_AS(cm.enrollStudent(1, "ListA"), std::invalid_argument);
}

TEST_CASE("StudentTest 19: Intersection - Finding common elements") {
    CourseManager cm;
    cm.addStudent(createRecord("S", 10, 90)); cm.addStudent(createRecord("S", 20, 90));
    cm.addStudent(createRecord("S", 30, 90)); cm.addStudent(createRecord("S", 40, 90));
    cm.addStudent(createRecord("S", 50, 90)); cm.addStudent(createRecord("S", 60, 90));
    
    cm.createCourse("ListA"); cm.createCourse("ListB");
    cm.enrollStudent(10, "ListA"); cm.enrollStudent(20, "ListA");
    cm.enrollStudent(30, "ListA"); cm.enrollStudent(40, "ListA");
    
    cm.enrollStudent(30, "ListB"); cm.enrollStudent(40, "ListB");
    cm.enrollStudent(50, "ListB"); cm.enrollStudent(60, "ListB");
    
    auto intersect = cm.studentsInBothCourses("ListA", "ListB");
    CHECK(intersect.size() == 2);
    CHECK(intersect == std::vector<int>{30, 40});
}

TEST_CASE("StudentTest 20: Intersection - No shared numbers") {
    CourseManager cm;
    cm.addStudent(createRecord("S", 1, 90)); cm.addStudent(createRecord("S", 2, 90));
    cm.addStudent(createRecord("S", 3, 90)); cm.addStudent(createRecord("S", 7, 90));
    cm.addStudent(createRecord("S", 8, 90)); cm.addStudent(createRecord("S", 9, 90));
    
    cm.createCourse("ListA"); cm.createCourse("ListB");
    cm.enrollStudent(1, "ListA"); cm.enrollStudent(2, "ListA"); cm.enrollStudent(3, "ListA");
    cm.enrollStudent(7, "ListB"); cm.enrollStudent(8, "ListB"); cm.enrollStudent(9, "ListB");
    
    auto intersect = cm.studentsInBothCourses("ListA", "ListB");
    CHECK(intersect.empty() == true);
}