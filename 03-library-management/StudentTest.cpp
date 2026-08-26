#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Book.hpp"
#include "LibraryCard.hpp"

using namespace library;

// Book Class Tests (1-10)

TEST_CASE("1. Book: Default Info") {
    Book b;
    CHECK(b.getTitle() == "Unknown");
    CHECK(b.getPages() == 0);
}

TEST_CASE("2. Book: String Author Info (Short Book)") {
    Book b("The Old Man and the Sea", "Ernest Hemingway", "ISBN-1001", 127);
    CHECK(b.getAuthorName() == "Ernest Hemingway");
    CHECK(b.getCategory() == "Short");
}

TEST_CASE("3. Book: Object Author Info (Long Book)") {
    Author amos("Amos Oz", "Israel", 1939);
    Book b("Sipur Al Ahava VeChoshech", amos, "ISBN-1012", 602);
    CHECK(b.getAuthor().birthYear == 1939);
    CHECK(b.isLargeBook() == true);
    CHECK(b.getCategory() == "Long");
}

TEST_CASE("4. Book: Copy Constructor") {
    Book original("1984", "George Orwell", "ISBN-1003", 328);
    Book copy(original);
    CHECK(copy.getTitle() == "1984");
    CHECK(copy.getCategory() == "Medium");
}

TEST_CASE("5. Book: Setters & Overloaded setAuthor") {
    Book b;
    b.setTitle("The Great Gatsby");
    
    b.setAuthor("F. Scott Fitzgerald");
    CHECK(b.getAuthorName() == "F. Scott Fitzgerald");
    
    Author tolstoy("Leo Tolstoy", "Russia", 1828);
    b.setAuthor(tolstoy);
    CHECK(b.getAuthor().country == "Russia");
}

TEST_CASE("6. Book: Mutable Reference Return") {
    Book b("HaDavar HaBa", "Etgar Keret", "ISBN-1016", 160);
    Author& ref = b.getAuthorReference();
    ref.country = "Israel";
    CHECK(b.getAuthor().country == "Israel");
}

TEST_CASE("7. Book: Friend Function - compareByPages") {
    Book lotr("The Lord of the Rings", "J.R.R. Tolkien", "ISBN-1007", 1178);
    Book catcher("The Catcher in the Rye", "J.D. Salinger", "ISBN-1005", 234);
    CHECK(compareByPages(lotr, catcher) == true);
    CHECK(compareByPages(catcher, lotr) == false);
}

TEST_CASE("8. Book: Friend Function - haveSameAuthor") {
    Book b1("MiShehu Larutz Ito", "David Grossman", "ISBN-1011", 352);
    Book b2("Isha Borachat MiBsora", "David Grossman", "ISBN-0000", 630);
    Book b3("Keren Or", "Eli Amir", "ISBN-1014", 420);
    CHECK(haveSameAuthor(b1, b2) == true);
    CHECK(haveSameAuthor(b1, b3) == false);
}

TEST_CASE("9. Book: Static Book Counter") {
    int before = Book::getCurrentBookCount();
    {
        Book temp("Tzipur HaNefesh", "Michal Snunit", "ISBN-1018", 32);
        CHECK(Book::getCurrentBookCount() == before + 1);
    }
    CHECK(Book::getCurrentBookCount() == before);
}

TEST_CASE("10. Book: Boundary Categories") {
    Book almostMedium("Almost", "Author", "ISBN", 199);
    Book exactMedium("Exact", "Author", "ISBN", 200);
    Book exactlyLong("Longer", "Author", "ISBN", 501);
    
    CHECK(almostMedium.getCategory() == "Short");
    CHECK(exactMedium.getCategory() == "Medium");
    CHECK(exactlyLong.getCategory() == "Long");
}

// LibraryCard Class Tests (11-20)

TEST_CASE("11. LibraryCard: Default Constructor") {
    LibraryCard card;
    CHECK(card.getMemberName() == "Guest");
    CHECK(card.getBorrowCount() == 0);
    CHECK(card.getCapacity() == 3);
}

TEST_CASE("12. LibraryCard: Parameterized Constructor") {
    LibraryCard card("Roee", "ID-2671", 5);
    CHECK(card.getMemberName() == "Roee");
    CHECK(card.getCapacity() == 5);
}

TEST_CASE("13. LibraryCard: Dynamic Resize") {
    LibraryCard card("Reader", "ID", 1);
    card.borrowBook(Book("To Kill a Mockingbird", "Harper Lee", "ISBN-1004", 281));
    card.borrowBook(Book("The Stranger", "Albert Camus", "ISBN-1010", 123)); 
    CHECK(card.getCapacity() >= 2);
    CHECK(card.getBorrowCount() == 2);
}

TEST_CASE("14. LibraryCard: Return Book by Index") {
    LibraryCard card("Test", "ID", 5);
    card.borrowBook(Book("HaTe'omim", "Ram Oren", "ISBN-1020", 348));
    card.borrowBook(Book("Bat HaRav", "Naomi Ragen", "ISBN-1019", 416));
    
    CHECK(card.returnBook(0) == true);
    CHECK(card.getBorrowCount() == 1);
    CHECK(card.findBorrowedBook("Bat HaRav") != nullptr);
}

TEST_CASE("15. LibraryCard: Return Book by Title") {
    LibraryCard card("Test", "ID", 5);
    card.borrowBook(Book("HaIsha HaGvoha", "Meir Shalev", "ISBN-1017", 544));
    CHECK(card.returnBook("HaIsha HaGvoha") == true);
    CHECK(card.getBorrowCount() == 0);
    CHECK(card.returnBook("Nonexistent") == false);
}

TEST_CASE("16. LibraryCard: Find Borrowed Book") {
    LibraryCard card("Test", "ID", 5);
    card.borrowBook(Book("Crime and Punishment", "Fyodor Dostoevsky", "ISBN-1006", 671));
    
    Book* found = card.findBorrowedBook("Crime and Punishment");
    CHECK(found != nullptr);
    CHECK(found->getPages() == 671);
}

TEST_CASE("17. LibraryCard: Get Total Borrowed Pages") {
    LibraryCard card("Test", "ID", 5);
    card.borrowBook(Book("Tzipur HaNefesh", "Michal Snunit", "ISBN-1018", 32));
    card.borrowBook(Book("The Old Man and the Sea", "Ernest Hemingway", "ISBN-1001", 127));
    CHECK(card.getTotalBorrowedPages() == 159);
}

TEST_CASE("18. LibraryCard: Deep Copy Arrays") {
    LibraryCard original("Original", "ID1", 2);
    original.borrowBook(Book("Ayalet Ahuvati", "Yitzhak Shalev", "ISBN-1015", 240));
    
    LibraryCard copy(original); 
    copy.clear(); 
    
    CHECK(original.getBorrowCount() == 1); 
    CHECK(copy.getBorrowCount() == 0);
}

TEST_CASE("19. LibraryCard: Friend Function - compareByBorrowCount") {
    LibraryCard c1("Heavy Reader", "ID1", 5);
    LibraryCard c2("Light Reader", "ID2", 5);
    
    c1.borrowBook(Book("B1", "A", "I", 100));
    c1.borrowBook(Book("B2", "A", "I", 100));
    c2.borrowBook(Book("B3", "A", "I", 100));
    
    CHECK(compareByBorrowCount(c1, c2) == true);
    CHECK(compareByBorrowCount(c2, c1) == false);
}

TEST_CASE("20. LibraryCard: Clear All") {
    LibraryCard card("Test", "ID", 5);
    card.borrowBook(Book("HaYeled HaLo Nachon", "Gali Mila", "ISBN-1013", 185));
    card.borrowBook(Book("One Hundred Years of Solitude", "Gabriel Garcia Marquez", "ISBN-1008", 417));
    
    card.clear();
    CHECK(card.getBorrowCount() == 0);
    CHECK(card.findBorrowedBook("HaYeled HaLo Nachon") == nullptr);
}