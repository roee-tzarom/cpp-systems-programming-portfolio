#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Grade.hpp"
#include "Student.hpp"
#include <stdexcept>

using namespace grading;

TEST_CASE("Student S001 - Bracket Operator and Basic Addition") {
    Student s("Liam Johnson", "S001");
    s.addGrade(Grade(92.0), Course("Calculus I", "MATH101", 5));
    s.addGrade(Grade(78.0), Course("Physics I", "PHYS102", 4));
    s.addGrade(Grade(85.0), Course("Intro to CS", "CS100", 3));
    
    CHECK(s[0].getScore() == 92.0);
    CHECK(s[1].getScore() == 78.0);
    CHECK(s[2].getScore() == 85.0);
}

TEST_CASE("Student S002 - Parentheses Operator for General Average") {
    Student s("Emma Smith", "S002");
    s.addGrade(Grade(64.0), Course("Data Structures", "CS201", 4));
    s.addGrade(Grade(91.0), Course("Statistics", "MATH205", 3));
    s.addGrade(Grade(88.0), Course("Macroeconomics", "ECON11", 3));
    
    CHECK(s() == doctest::Approx(81.0));
}

TEST_CASE("Student S003 - GPA Calculation with Failure") {
    Student s("Noah Williams", "S003");
    s.addGrade(Grade(45.0), Course("Algorithms", "CS302", 4));
    s.addGrade(Grade(72.0), Course("Linear Algebra", "MATH105", 4));
    s.addGrade(Grade(94.0), Course("Psychology 101", "PSY10", 3));
    
    CHECK(s.calculateGPA() == doctest::Approx(2.0));
}

TEST_CASE("Student S004 - Bracket Operator by Course Name") {
    Student s("Olivia Brown", "S004");
    s.addGrade(Grade(81.0), Course("Biology II", "BIO202", 4));
    s.addGrade(Grade(58.0), Course("Organic Chem", "CHEM301", 5));
    s.addGrade(Grade(100.0), Course("Ethics", "PHIL102", 2));
    
    CHECK(s["Organic Chem"].getScore() == 58.0);
    CHECK(s["Ethics"].getScore() == 100.0);
}

TEST_CASE("Student S005 - Highest and Lowest Grades") {
    Student s("William Jones", "S005");
    s.addGrade(Grade(77.0), Course("Networking", "CS405", 3));
    s.addGrade(Grade(82.0), Course("Database Systems", "CS310", 4));
    s.addGrade(Grade(69.0), Course("Discrete Math", "MATH210", 4));
    
    CHECK(s.getHighestGrade().getScore() == 82.0);
    CHECK(s.getLowestGrade().getScore() == 69.0);
}

TEST_CASE("Students S006 vs S007 - Comparison Operators") {
    Student s1("Sophia Garcia", "S006");
    s1.addGrade(Grade(96.0), Course("Art History", "ART110", 3));
    s1.addGrade(Grade(89.0), Course("Sociology", "SOC105", 3));
    s1.addGrade(Grade(91.0), Course("World History", "HIST101", 3));
    
    Student s2("James Miller", "S007");
    s2.addGrade(Grade(52.0), Course("Mechanics", "MECH100", 4));
    s2.addGrade(Grade(61.0), Course("Thermodynamics", "PHYS305", 4));
    s2.addGrade(Grade(75.0), Course("Calculus II", "MATH102", 5));
    
    CHECK(s1 > s2);
    CHECK_FALSE(s1 < s2);
    CHECK(s1 != s2);
}

TEST_CASE("Student S008 - Out of Range Exceptions") {
    Student s("Isabella Davis", "S008");
    s.addGrade(Grade(88.0), Course("Marketing", "BUS201", 3));
    s.addGrade(Grade(93.0), Course("Accounting", "BUS105", 4));
    s.addGrade(Grade(84.0), Course("Business Law", "LAW210", 3));
    
    CHECK_THROWS_AS(s[3], std::out_of_range);
    CHECK_THROWS_AS(s[-1], std::out_of_range);
    CHECK_THROWS_AS(s["Finance"], std::out_of_range);
}

TEST_CASE("Student S009 - Arithmetic Operator +") {
    Student s("Benjamin Rodriguez", "S009");
    s.addGrade(Grade(73.0), Course("OS Systems", "CS411", 4));
    s.addGrade(Grade(95.0), Course("Cyber Security", "CS505", 3));
    s.addGrade(Grade(88.0), Course("AI Ethics", "CS220", 2));
    
    Student curved = s + 5.0;
    CHECK(curved[0].getScore() == 78.0);
    CHECK(curved[1].getScore() == 100.0);
    CHECK(curved[2].getScore() == 93.0);
}

TEST_CASE("Student S010 - Arithmetic Operator *") {
    Student s("Mia Martinez", "S010");
    s.addGrade(Grade(42.0), Course("Genetics", "BIO405", 4));
    s.addGrade(Grade(67.0), Course("Microbiology", "BIO308", 4));
    s.addGrade(Grade(70.0), Course("Biochemistry", "CHEM410", 5));
    
    Student curved = s * 1.1;
    CHECK(curved[0].getScore() == doctest::Approx(46.2));
    CHECK(curved[1].getScore() == doctest::Approx(73.7));
}

TEST_CASE("Student S011 - Copy Constructor Deep Copy") {
    Student s1("Elijah Hernandez", "S011");
    s1.addGrade(Grade(98.0), Course("Philosophy", "PHIL201", 3));
    s1.addGrade(Grade(92.0), Course("Logic", "PHIL105", 3));
    
    Student s2(s1);
    s2[0] = Grade(100.0);
    
    CHECK(s1[0].getScore() == 98.0);
    CHECK(s2[0].getScore() == 100.0);
}

TEST_CASE("Student S012 - Copy Assignment Operator") {
    Student s1("Charlotte Young", "S012");
    s1.addGrade(Grade(85.0), Course("Microeconomics", "ECON10", 3));
    s1.addGrade(Grade(48.0), Course("Calculus I", "MATH101", 5));
    
    Student s2;
    s2 = s1;
    s2.addGrade(Grade(76.0), Course("Finance", "FIN202", 3));
    
    CHECK(s1.getGradeCount() == 2);
    CHECK(s2.getGradeCount() == 3);
}

TEST_CASE("Student S013 - Count Passing Grades") {
    Student s("Lucas King", "S013");
    s.addGrade(Grade(83.0), Course("Compilers", "CS440", 4));
    s.addGrade(Grade(90.0), Course("Machine Learning", "CS480", 4));
    s.addGrade(Grade(91.0), Course("Software Eng", "CS350", 4));
    
    CHECK(s.countPassingGrades() == 3);
}

TEST_CASE("Student S014 - Limit Average Operator") {
    Student s("Amelia Wright", "S014");
    s.addGrade(Grade(59.0), Course("Anatomy", "MED101", 5));
    s.addGrade(Grade(71.0), Course("Physiology", "MED105", 5));
    s.addGrade(Grade(82.0), Course("Chemistry I", "CHEM101", 4));
    
    CHECK(s(2) == doctest::Approx(65.0));
}

TEST_CASE("Student S015 - Range Average Operator") {
    Student s("Mason Scott", "S015");
    s.addGrade(Grade(66.0), Course("Civil Engineering", "CE101", 4));
    s.addGrade(Grade(74.0), Course("Geology", "GEO102", 3));
    s.addGrade(Grade(80.0), Course("Surveying", "CE105", 3));
    
    CHECK(s(1, 2) == doctest::Approx(77.0));
}

TEST_CASE("Student S016 - Weighted Average Operator") {
    Student s("Evelyn Green", "S016");
    s.addGrade(Grade(94.0), Course("English Lit", "LIT101", 3));
    s.addGrade(Grade(97.0), Course("Creative Writing", "CW202", 3));
    s.addGrade(Grade(91.0), Course("Poetry", "LIT205", 2));
    
    CHECK(s(1, 2.0) == doctest::Approx(94.75));
}

TEST_CASE("Student S017 - Compound Assignment +=") {
    Student s("Harper Adams", "S017");
    s.addGrade(Grade(55.0), Course("Algebra", "MATH103", 4));
    s.addGrade(Grade(62.0), Course("Statistics", "MATH205", 3));
    s.addGrade(Grade(70.0), Course("Programming I", "CS105", 4));
    
    s += 5.0;
    CHECK(s[0].getScore() == 60.0);
    CHECK(s[1].getScore() == 67.0);
    CHECK(s[2].getScore() == 75.0);
}

TEST_CASE("Student S018 - Const Bracket Access") {
    const Student s("Ethan Baker", "S018");
    Student temp("Ethan Baker", "S018");
    temp.addGrade(Grade(89.0), Course("Game Design", "CS250", 3));
    temp.addGrade(Grade(93.0), Course("3D Modeling", "ART220", 3));
    
    const Student s_const = temp;
    CHECK(s_const["Game Design"].getScore() == 89.0);
    CHECK(s_const[1].getScore() == 93.0);
}

TEST_CASE("Student S019 - Remove Grade") {
    Student s("Abigail Nelson", "S019");
    s.addGrade(Grade(78.0), Course("Political Science", "POL101", 3));
    s.addGrade(Grade(81.0), Course("International Rel", "POL205", 3));
    s.addGrade(Grade(49.0), Course("Public Policy", "POL310", 3));
    
    s.removeGrade(1);
    CHECK(s.getGradeCount() == 2);
    CHECK(s[1].getScore() == 49.0);
}

TEST_CASE("Student S020 - Equality Operators") {
    Student s1("Daniel Hill", "S020");
    s1.addGrade(Grade(72.0), Course("Circuits", "EE101", 4));
    s1.addGrade(Grade(68.0), Course("Digital Systems", "EE205", 4));
    s1.addGrade(Grade(54.0), Course("Signal Processing", "EE310", 4));
    
    Student s2("Clone", "S099");
    s2.addGrade(Grade(72.0), Course("Circuits", "EE101", 4));
    s2.addGrade(Grade(68.0), Course("Digital Systems", "EE205", 4));
    s2.addGrade(Grade(54.0), Course("Signal Processing", "EE310", 4));
    
    CHECK(s1 == s2);
}

TEST_CASE("Friend Function compareByAverage") {
    Student s1("Mia Martinez", "S010");
    s1.addGrade(Grade(42.0), Course("Genetics", "BIO405", 4));
    s1.addGrade(Grade(67.0), Course("Microbiology", "BIO308", 4));
    
    Student s2("Evelyn Green", "S016");
    s2.addGrade(Grade(94.0), Course("English Lit", "LIT101", 3));
    s2.addGrade(Grade(97.0), Course("Creative Writing", "CW202", 3));
    
    CHECK(compareByAverage(s2, s1) == true);
    CHECK(compareByAverage(s1, s2) == false);
}

TEST_CASE("Student S001 - Find missing course exception") {
    Student s("Liam Johnson", "S001");
    s.addGrade(Grade(92.0), Course("Calculus I", "MATH101", 5));
    CHECK_THROWS_AS(s["History"], std::out_of_range);
}