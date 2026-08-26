/**
 * @file main.cpp
 * @brief Demo for Library Book Management System
 */

#include <iostream>
#include "Book.hpp"
#include "LibraryCard.hpp"

using namespace std;
using namespace library;

int main() {
    cout << "========================================" << endl;
    cout << "  Library Book Management System Demo" << endl;
    cout << "========================================\n" << endl;

    // ============ 1. COMPOSITION DEMO ============
    cout << "=== 1. COMPOSITION (Book HAS-A Author) ===" << endl;
    Author author1("George Orwell", "UK", 1903);
    Book book1("1984", author1, "ISBN-001", 328);
    cout << "Created book with author object (composition): ";
    book1.print(cout);
    cout << endl;
    // Expected: 1984 by George Orwell | ISBN-001 | 328 pages | Available
    
    cout << endl;

    // ============ 2. CONSTRUCTORS DEMO ============
    cout << "=== 2. CONSTRUCTORS (Default, Parameterized, Copy) ===" << endl;
    
    // Default constructor
    Book defaultBook;
    cout << "Default book:  ";
    defaultBook.print(cout);
    cout << endl;
    // Expected: Unknown by Unknown | | 0 pages | Available
    
    // Parameterized constructor - overloaded version 1
    Book book2("To Kill a Mockingbird", "Harper Lee", "ISBN-002", 281);
    cout << "Book with author name: ";
    book2.print(cout);
    cout << endl;
    // Expected: To Kill a Mockingbird by Harper Lee | ISBN-002 | 281 pages | Available
    
    // Copy constructor
    Book book1Copy(book1);
    cout << "Copy of book1: ";
    book1Copy.print(cout);
    cout << endl;
    // Expected: Same as book1
    
    cout << endl;

    // ============ 3. OVERLOADING (not operators) DEMO ============
    cout << "=== 3. FUNCTION OVERLOADING (setAuthor) ===" << endl;
    Book book3("The Great Gatsby", "F. Scott Fitzgerald", "ISBN-003", 180);
    
    // Overloaded setAuthor - version 1 (string)
    book3.setAuthor("Francis Scott Fitzgerald");
    cout << "After setAuthor(string): " << book3.getAuthorName() << endl;
    // Expected: Francis Scott Fitzgerald
    
    // Overloaded setAuthor - version 2 (Author object)
    Author newAuthor("F. S.  Fitzgerald", "USA", 1896);
    book3.setAuthor(newAuthor);
    cout << "After setAuthor(Author): " << book3.getAuthorName() << endl;
    // Expected: F. S.  Fitzgerald
    
    cout << endl;

    // ============ 4. CONST METHODS DEMO ============
    cout << "=== 4. CONST METHODS ===" << endl;
    const Book constBook("Pride and Prejudice", "Jane Austen", "ISBN-004", 432);
    
    // All these methods are const, so they can be called on const objects
    cout << "Const book title: " << constBook.getTitle() << endl;
    // Expected: Pride and Prejudice
    
    cout << "Is large book?  " << (constBook.isLargeBook() ? "Yes" : "No") << endl;
    // Expected: No (pages <= 500)
    
    cout << "Category: " << constBook.getCategory() << endl;
    // Expected: Medium
    
    cout << endl;

    // ============ 5. REFERENCE & REFERENCE-RETURN DEMO ============
    cout << "=== 5. REFERENCE PARAMETERS & REFERENCE-RETURN ===" << endl;
    
    Book book4("The Hobbit", "J. R.R. Tolkien", "ISBN-005", 310);
    
    // Reference-return:  getAuthorReference() returns Author&
    Author& authorRef = book4.getAuthorReference();
    cout << "Original author country: " << authorRef.country << endl;
    // Expected:  Unknown
    
    // Modify through reference
    authorRef.country = "England";
    authorRef.birthYear = 1892;
    cout << "After modifying through reference: " << book4.getAuthor().country 
         << ", " << book4.getAuthor().birthYear << endl;
    // Expected: England, 1892
    
    // Const reference return
    const Author& constAuthorRef = book4.getAuthor();
    cout << "Author via const reference: " << constAuthorRef.name << endl;
    // Expected:  J.R.R. Tolkien
    
    cout << endl;

    // ============ 6. INLINE vs OUTLINE DEMO ============
    cout << "=== 6. INLINE (header) vs OUTLINE (. cpp) IMPLEMENTATIONS ===" << endl;
    cout << "getTitle() is INLINE: " << book4.getTitle() << endl;
    // Expected: The Hobbit
    
    cout << "getAuthorName() is OUTLINE: " << book4.getAuthorName() << endl;
    // Expected: J.R.R.  Tolkien
    
    cout << "getPages() is INLINE: " << book4.getPages() << endl;
    // Expected: 310
    
    cout << "getCategory() is OUTLINE: " << book4.getCategory() << endl;
    // Expected: Medium
    
    cout << endl;

    // ============ 7. STATIC MEMBERS DEMO ============
    cout << "=== 7. STATIC MEMBERS ===" << endl;
    cout << "Total books created so far: " << Book::getTotalBooksCreated() << endl;
    cout << "Current books in memory: " << Book::getCurrentBookCount() << endl;
    // Expected: Total created >= Current count
    
    {
        Book tempBook("Temporary", "Author", "ISBN-999", 100);
        cout << "After creating temp book - Current count: " 
             << Book::getCurrentBookCount() << endl;
    } // tempBook destroyed here
    
    cout << "After temp book destroyed - Current count: " 
         << Book::getCurrentBookCount() << endl;
    // Expected: Count decremented by 1
    
    cout << endl;

    // ============ 8. FRIEND FUNCTIONS DEMO ============
    cout << "=== 8. FRIEND FUNCTIONS ===" << endl;
    Book book5("War and Peace", "Leo Tolstoy", "ISBN-006", 1225);
    Book book6("Anna Karenina", "Leo Tolstoy", "ISBN-007", 864);
    
    // Friend function: compareByPages
    cout << "Does 'War and Peace' have more pages than 'Anna Karenina'? "
         << (compareByPages(book5, book6) ? "Yes" : "No") << endl;
    // Expected: Yes
    
    // Friend function: haveSameAuthor
    cout << "Do they have the same author? "
         << (haveSameAuthor(book5, book6) ? "Yes" : "No") << endl;
    // Expected:  Yes
    
    cout << endl;

    // ============ 9. LIBRARY CARD DEMO (Composition & Destruct-arrays) ============
    cout << "=== 9. LIBRARY CARD (Composition, Destruct-Arrays) ===" << endl;
    
    LibraryCard card1("Alice Johnson", "MEM-001", 2);
    cout << "Created library card for:  " << card1.getMemberName() << endl;
    // Expected: Alice Johnson
    
    // Borrow books - demonstrates reference parameters and composition
    card1.borrowBook(book1);
    card1.borrowBook(book2);
    cout << "Borrowed " << card1.getBorrowCount() << " books" << endl;
    // Expected:  Borrowed 2 books
    
    card1.borrowBook(book3); // Will trigger resize
    cout << "After borrowing 3rd book: " << card1.getBorrowCount() 
         << " books (capacity:  " << card1.getCapacity() << ")" << endl;
    // Expected: 3 books (capacity: 4)
    
    cout << "\nCard details:" << endl;
    card1.print(cout);
    cout << endl;
    // Expected: Card details with all borrowed books listed
    
    cout << "Total borrowed pages: " << card1.getTotalBorrowedPages() << endl;
    // Expected: Sum of all borrowed books' pages
    
    cout << endl;

    // ============ 10. DESTRUCTORS & DESTRUCT-ARRAYS DEMO ============
    cout << "=== 10. DESTRUCTORS & DESTRUCT-ARRAYS ===" << endl;
    cout << "Creating cards in a scope block..." << endl;
    
    {
        LibraryCard tempCard1("Bob", "MEM-002");
        LibraryCard tempCard2("Charlie", "MEM-003");
        tempCard1.borrowBook(book4);
        tempCard2.borrowBook(book5);
        tempCard2.borrowBook(book6);
        
        cout << "Total cards issued: " << LibraryCard::getTotalCardsIssued() << endl;
        // Expected: At least 3
        
        cout << "Exiting scope - destructors will be called..." << endl;
    } // tempCard1 and tempCard2 destroyed here - demonstrates proper array destruction
    
    cout << "Scope exited - cards destroyed (including their book arrays)" << endl;
    cout << endl;

    // ============ 11. COPY CONSTRUCTOR (Deep Copy) DEMO ============
    cout << "=== 11. COPY CONSTRUCTOR (Deep Copy) ===" << endl;
    
    LibraryCard card2(card1); // Deep copy
    card2.setMemberName("Alice's Copy");
    card2.returnBook(0); // Return first book
    
    cout << "Original card books: " << card1.getBorrowCount() << endl;
    // Expected: 3 (unchanged)
    
    cout << "Copied card books: " << card2.getBorrowCount() << endl;
    // Expected: 2 (one returned)
    
    cout << endl;

    // ============ 12. FINAL STATISTICS ============
    cout << "=== 12. FINAL STATISTICS ===" << endl;
    cout << "Total books ever created: " << Book::getTotalBooksCreated() << endl;
    cout << "Current books in memory: " << Book::getCurrentBookCount() << endl;
    cout << "Total library cards issued: " << LibraryCard::getTotalCardsIssued() << endl;
    
    cout << "\n========================================" << endl;
    cout << "       Demo Complete!" << endl;
    cout << "========================================" << endl;

    return 0;
}
// All destructors will be called here for objects going out of scope