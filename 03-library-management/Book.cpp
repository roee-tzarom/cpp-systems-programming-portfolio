#include "Book.hpp"

namespace library {

    int Book::totalBooksCreated = 0;
    int Book::currentBookCount = 0;

    const int MAX_SHORT_PAGES = 200;
    const int MAX_MEDIUM_PAGES = 500;

    Book::Book() : title("Unknown"), pages(0), available(true) {
        totalBooksCreated++;
        currentBookCount++;
    }

    Book::Book(const std::string& title, const std::string& authorName, const std::string& ISBN, int pages) 
        : title(title), author(authorName, "Unknown", 0), ISBN(ISBN), pages(pages), available(true) {
        totalBooksCreated++;
        currentBookCount++;
    }

    Book::Book(const std::string& title, const Author& authorObject, const std::string& ISBN, int pages)
        : title(title), author(authorObject), ISBN(ISBN), pages(pages), available(true) {
        totalBooksCreated++;
        currentBookCount++;
    }

    Book::Book(const Book& other) 
        : title(other.title), author(other.author), ISBN(other.ISBN), pages(other.pages), available(other.available) {
        totalBooksCreated++;
        currentBookCount++;
    }

    Book::~Book() {
        currentBookCount--;
    }

    std::string Book::getAuthorName() const {
        return author.name;
    }

    std::string Book::getCategory() const {
        if (pages < MAX_SHORT_PAGES) {
            return "Short";
        }
        if (pages <= MAX_MEDIUM_PAGES) {
            return "Medium";
        }
        return "Long";
    }

    bool Book::isLargeBook() const {
        return pages > MAX_MEDIUM_PAGES;
    }

    void Book::print(std::ostream& outStream) const {
        outStream << title << " by " << author.name << " | " << ISBN << " | " 
           << pages << " pages | " << (available ? "Available" : "Borrowed");
    }

    void Book::setTitle(const std::string& newTitle) {
        title = newTitle;
    }

    void Book::setAvailability(bool isAvailable) {
        available = isAvailable;
    }

    void Book::setAuthor(const std::string& newAuthorName) {
        author.name = newAuthorName;
    }

    void Book::setAuthor(const Author& newAuthorObject) {
        author = newAuthorObject;
    }

    int Book::getTotalBooksCreated() {
        return totalBooksCreated;
    }

    int Book::getCurrentBookCount() {
        return currentBookCount;
    }

    bool compareByPages(const Book& book1, const Book& book2) {
        return book1.pages > book2.pages;
    }

    bool haveSameAuthor(const Book& book1, const Book& book2) {
        return book1.author.name == book2.author.name;
    }

}