/**
 * @file test.cpp
 * @brief Unit tests for Library Book Management System using doctest
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <fstream>
#include "Book.hpp"
#include "LibraryCard.hpp"

using namespace library;

// ==================== BOOK CLASS TESTS ====================

TEST_CASE("Book - Default Constructor") {
    Book b;
    CHECK(b.getTitle() == "Unknown");
    CHECK(b.getAuthorName() == "Unknown");
    CHECK(b.getPages() == 0);
    CHECK(b.getAvailability() == true);
}

TEST_CASE("Book - Parameterized Constructor with Author Name") {
    Book b("1984", "George Orwell", "ISBN-001", 328);
    CHECK(b.getTitle() == "1984");
    CHECK(b.getAuthorName() == "George Orwell");
    CHECK(b.getISBN() == "ISBN-001");
    CHECK(b.getPages() == 328);
}

TEST_CASE("Book - Parameterized Constructor with Author Object (Composition)") {
    Author author("J.K. Rowling", "UK", 1965);
    Book b("Harry Potter", author, "ISBN-002", 309);
    
    CHECK(b.getTitle() == "Harry Potter");
    CHECK(b.getAuthorName() == "J.K. Rowling");
    CHECK(b.getAuthor().country == "UK");
    CHECK(b.getAuthor().birthYear == 1965);
}

TEST_CASE("Book - Copy Constructor") {
    Book b1("Original", "Author", "ISBN-003", 200);
    Book b2(b1);
    
    CHECK(b2.getTitle() == b1.getTitle());
    CHECK(b2.getAuthorName() == b1.getAuthorName());
    CHECK(b2.getPages() == b1.getPages());
}

TEST_CASE("Book - Setters") {
    Book b;
    b.setTitle("New Title");
    b.setAvailability(false);
    
    CHECK(b.getTitle() == "New Title");
    CHECK(b.getAvailability() == false);
}

TEST_CASE("Book - setAuthor Overloading") {
    Book b("Test", "Original", "ISBN-004", 100);
    
    // Overload 1: string parameter
    b.setAuthor("New Author");
    CHECK(b.getAuthorName() == "New Author");
    
    // Overload 2: Author object parameter
    Author author("Another Author", "USA", 1980);
    b.setAuthor(author);
    CHECK(b.getAuthorName() == "Another Author");
    CHECK(b.getAuthor().country == "USA");
}

TEST_CASE("Book - Const Methods") {
    const Book b("Test Book", "Author", "ISBN-005", 600);
    
    // All these should compile and work with const object
    CHECK(b.getTitle() == "Test Book");
    CHECK(b.getPages() == 600);
    CHECK(b.isLargeBook() == true);  // > 500 pages
    CHECK(b.getCategory() == "Long");
}

TEST_CASE("Book - isLargeBook Method") {
    Book small("Small", "Author", "ISBN", 300);
    Book large("Large", "Author", "ISBN", 600);
    
    CHECK_FALSE(small.isLargeBook());
    CHECK(large.isLargeBook());
}

TEST_CASE("Book - getCategory Method") {
    Book short_book("Short", "A", "ISBN", 150);
    Book medium_book("Medium", "A", "ISBN", 350);
    Book long_book("Long", "A", "ISBN", 600);
    
    CHECK(short_book.getCategory() == "Short");
    CHECK(medium_book.getCategory() == "Medium");
    CHECK(long_book.getCategory() == "Long");
}

TEST_CASE("Book - getCategory Boundary Values") {
    Book at199("B", "A", "ISBN", 199);
    Book at200("B", "A", "ISBN", 200);
    Book at500("B", "A", "ISBN", 500);
    Book at501("B", "A", "ISBN", 501);
    
    CHECK(at199.getCategory() == "Short");   // < 200 is Short
    CHECK(at200.getCategory() == "Medium");  // 200 is Medium
    CHECK(at500.getCategory() == "Medium");  // 500 is Medium
    CHECK(at501.getCategory() == "Long");    // > 500 is Long
}

TEST_CASE("Book - Reference Return (getAuthorReference)") {
    Book b("Test", "Original Author", "ISBN", 200);
    
    // Get mutable reference and modify
    Author& authorRef = b.getAuthorReference();
    authorRef.name = "Modified Author";
    authorRef.country = "France";
    
    CHECK(b.getAuthorName() == "Modified Author");
    CHECK(b.getAuthor().country == "France");
}

TEST_CASE("Book - Const Reference Return (getAuthor)") {
    Book b("Test", "Author", "ISBN", 200);
    const Author& authorRef = b.getAuthor();
    
    CHECK(authorRef.name == "Author");
    // authorRef.name = "New"; // Should not compile (const reference)
}

TEST_CASE("Book - Static Members") {
    int initialTotal = Book::getTotalBooksCreated();
    int initialCurrent = Book::getCurrentBookCount();
    
    {
        Book b1("Book1", "Author", "ISBN", 100);
        Book b2("Book2", "Author", "ISBN", 200);
        
        CHECK(Book::getTotalBooksCreated() == initialTotal + 2);
        CHECK(Book::getCurrentBookCount() == initialCurrent + 2);
    } // b1 and b2 destroyed
    
    CHECK(Book::getCurrentBookCount() == initialCurrent);
    CHECK(Book::getTotalBooksCreated() == initialTotal + 2); // Never decrements
}

TEST_CASE("Book - Friend Functions") {
    Book b1("Book1", "Author A", "ISBN-001", 300);
    Book b2("Book2", "Author B", "ISBN-002", 500);
    Book b3("Book3", "Author A", "ISBN-003", 200);
    
    // compareByPages friend function
    CHECK(compareByPages(b2, b1) == true);
    CHECK(compareByPages(b1, b2) == false);
    
    // haveSameAuthor friend function
    CHECK(haveSameAuthor(b1, b3) == true);
    CHECK(haveSameAuthor(b1, b2) == false);
}

// ==================== LIBRARYCARD CLASS TESTS ====================

TEST_CASE("LibraryCard - Default Constructor") {
    LibraryCard card;
    CHECK(card.getMemberName() == "Guest");
    CHECK(card.getBorrowCount() == 0);
    CHECK(card.getCapacity() == 3);
    CHECK_FALSE(card.isFull());
}

TEST_CASE("LibraryCard - Parameterized Constructor") {
    LibraryCard card("Alice", "MEM-001", 5);
    CHECK(card.getMemberName() == "Alice");
    CHECK(card.getMemberID() == "MEM-001");
    CHECK(card.getCapacity() == 5);
}

TEST_CASE("LibraryCard - Borrow Book (Reference Parameter)") {
    LibraryCard card("Bob", "MEM-002");
    Book book("1984", "Orwell", "ISBN-001", 328);
    
    CHECK(card.borrowBook(book));
    CHECK(card.getBorrowCount() == 1);
}

TEST_CASE("LibraryCard - Resize on Overflow") {
    LibraryCard card("Charlie", "MEM-003", 2);
    
    Book b1("Book1", "A", "ISBN1", 100);
    Book b2("Book2", "A", "ISBN2", 200);
    Book b3("Book3", "A", "ISBN3", 300);
    
    card.borrowBook(b1);
    card.borrowBook(b2);
    CHECK(card.getCapacity() == 2);
    
    card.borrowBook(b3); // Triggers resize
    CHECK(card.getCapacity() == 4);
    CHECK(card.getBorrowCount() == 3);
}

TEST_CASE("LibraryCard - Return Book by Index") {
    LibraryCard card("Dave", "MEM-004");
    Book b1("Book1", "A", "ISBN1", 100);
    Book b2("Book2", "A", "ISBN2", 200);
    
    card.borrowBook(b1);
    card.borrowBook(b2);
    
    CHECK(card.returnBook(0));
    CHECK(card.getBorrowCount() == 1);
    CHECK_FALSE(card.returnBook(10)); // Invalid index
}

TEST_CASE("LibraryCard - Return Book by Title") {
    LibraryCard card("Eve", "MEM-005");
    Book b1("Target Book", "A", "ISBN1", 100);
    Book b2("Other Book", "A", "ISBN2", 200);
    
    card.borrowBook(b1);
    card.borrowBook(b2);
    
    CHECK(card.returnBook("Target Book"));
    CHECK(card.getBorrowCount() == 1);
    CHECK_FALSE(card.returnBook("Nonexistent"));
}

TEST_CASE("LibraryCard - Find Borrowed Book") {
    LibraryCard card("Frank", "MEM-006");
    Book book("Find Me", "Author", "ISBN", 300);
    
    card.borrowBook(book);
    
    Book* found = card.findBorrowedBook("Find Me");
    CHECK(found != nullptr);
    CHECK(found->getTitle() == "Find Me");
    
    CHECK(card.findBorrowedBook("Not There") == nullptr);
}

TEST_CASE("LibraryCard - Get Total Borrowed Pages") {
    LibraryCard card("Grace", "MEM-007");
    Book b1("B1", "A", "ISBN1", 100);
    Book b2("B2", "A", "ISBN2", 200);
    Book b3("B3", "A", "ISBN3", 300);
    
    card.borrowBook(b1);
    card.borrowBook(b2);
    card.borrowBook(b3);
    
    CHECK(card.getTotalBorrowedPages() == 600);
}

TEST_CASE("LibraryCard - Copy Constructor (Deep Copy & Destruct-Arrays)") {
    LibraryCard card1("Original", "MEM-008");
    Book book("Book", "Author", "ISBN", 250);
    card1.borrowBook(book);
    
    LibraryCard card2(card1);
    card2.setMemberName("Copy");
    card2.returnBook(0);
    
    CHECK(card1.getBorrowCount() == 1);  // Original unchanged
    CHECK(card2.getBorrowCount() == 0);  // Copy modified
    CHECK(card1.getMemberName() == "Original");
    CHECK(card2.getMemberName() == "Copy");
}

TEST_CASE("LibraryCard - Clear (Destruct-Arrays)") {
    LibraryCard card("Harry", "MEM-009");
    Book b1("B1", "A", "ISBN1", 100);
    Book b2("B2", "A", "ISBN2", 200);
    
    card.borrowBook(b1);
    card.borrowBook(b2);
    
    card.clear();
    CHECK(card.getBorrowCount() == 0);
}

TEST_CASE("LibraryCard - Static Members") {
    int initialCount = LibraryCard::getTotalCardsIssued();
    
    LibraryCard c1("Member1", "ID1");
    LibraryCard c2("Member2", "ID2");
    
    CHECK(LibraryCard::getTotalCardsIssued() == initialCount + 2);
}

TEST_CASE("LibraryCard - Friend Function (compareByBorrowCount)") {
    LibraryCard c1("Alice", "ID1");
    LibraryCard c2("Bob", "ID2");
    
    Book b("Book", "Author", "ISBN", 100);
    c1.borrowBook(b);
    c1.borrowBook(b);
    c2.borrowBook(b);
    
    CHECK(compareByBorrowCount(c1, c2) == true);
    CHECK(compareByBorrowCount(c2, c1) == false);
}

TEST_CASE("LibraryCard - isFull Method") {
    LibraryCard card("Test", "ID", 2);
    Book b("Book", "Author", "ISBN", 100);
    
    CHECK_FALSE(card.isFull());
    
    card.borrowBook(b);
    card.borrowBook(b);
    
    CHECK(card.isFull());
}

// ==================== INTEGRATION TESTS ====================

TEST_CASE("Integration - Complete Library Workflow") {
    // Create books
    Author author("Test Author", "USA", 1970);
    Book b1("Book 1", author, "ISBN-101", 250);
    Book b2("Book 2", "Another Author", "ISBN-102", 350);
    
    // Create library card
    LibraryCard card("Test Member", "MEM-100", 3);
    
    // Borrow books
    card.borrowBook(b1);
    card.borrowBook(b2);
    
    CHECK(card.getBorrowCount() == 2);
    CHECK(card.getTotalBorrowedPages() == 600);
    
    // Return a book
    card.returnBook("Book 1");
    CHECK(card.getBorrowCount() == 1);
    
    // Verify remaining book
    Book* found = card.findBorrowedBook("Book 2");
    CHECK(found != nullptr);
    CHECK(found->getPages() == 350);
}

TEST_CASE("Student custom tests file exists") {
    std::ifstream f("StudentTest.cpp");
    CHECK_MESSAGE(f.good(), "StudentTest.cpp file must be created by the student");
}