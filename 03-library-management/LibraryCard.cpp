#include "LibraryCard.hpp"
#include <cstddef>

namespace library {

    int LibraryCard::totalCardsIssued = 0;

    void LibraryCard::resize() {
        int newCapacity = capacity * 2;
        Book** temp = new Book*[static_cast<size_t>(newCapacity)];
        for (int i = 0; i < borrowCount; ++i) {
            temp[i] = borrowedBooks[i];
        }
        delete[] borrowedBooks;
        borrowedBooks = temp;
        capacity = newCapacity;
    }

    LibraryCard::LibraryCard() 
        : memberName("Guest"), capacity(3), borrowCount(0) {
        borrowedBooks = new Book*[static_cast<size_t>(capacity)];
        totalCardsIssued++;
    }

    LibraryCard::LibraryCard(const std::string& memberName, const std::string& memberID, int capacity)
        : memberName(memberName), memberID(memberID), capacity(capacity > 0 ? capacity : 3), borrowCount(0) {
        borrowedBooks = new Book*[static_cast<size_t>(this->capacity)];
        totalCardsIssued++;
    }

    LibraryCard::LibraryCard(const LibraryCard& other)
        : memberName(other.memberName), memberID(other.memberID), 
          capacity(other.capacity), borrowCount(other.borrowCount) {
        borrowedBooks = new Book*[static_cast<size_t>(capacity)];
        for (int i = 0; i < borrowCount; ++i) {
            borrowedBooks[i] = new Book(*(other.borrowedBooks[i]));
        }
        totalCardsIssued++;
    }

    LibraryCard& LibraryCard::operator=(const LibraryCard& other) {
        if (this == &other) {
            return *this;
        }

        clear();
        delete[] borrowedBooks;

        memberName = other.memberName;
        memberID = other.memberID;
        capacity = other.capacity;
        borrowCount = other.borrowCount;

        borrowedBooks = new Book*[static_cast<size_t>(capacity)];
        for (int i = 0; i < borrowCount; ++i) {
            borrowedBooks[i] = new Book(*(other.borrowedBooks[i]));
        }

        return *this;
    }

    LibraryCard::~LibraryCard() {
        clear();
        delete[] borrowedBooks;
    }

    void LibraryCard::setMemberName(const std::string& newName) {
        memberName = newName;
    }

    bool LibraryCard::borrowBook(const Book& book) {
        if (borrowCount == capacity) {
            resize();
        }
        borrowedBooks[borrowCount++] = new Book(book);
        return true;
    }

    bool LibraryCard::returnBook(int index) {
        if (index < 0 || index >= borrowCount) {
            return false;
        }
        
        delete borrowedBooks[index];
        
        for (int i = index; i < borrowCount - 1; ++i) {
            borrowedBooks[i] = borrowedBooks[i + 1];
        }
        borrowCount--;
        return true;
    }

    bool LibraryCard::returnBook(const std::string& title) {
        for (int i = 0; i < borrowCount; ++i) {
            if (borrowedBooks[i]->getTitle() == title) {
                return returnBook(i);
            }
        }
        return false;
    }

    Book* LibraryCard::findBorrowedBook(const std::string& title) const {
        for (int i = 0; i < borrowCount; ++i) {
            if (borrowedBooks[i]->getTitle() == title) {
                return borrowedBooks[i];
            }
        }
        return nullptr;
    }

    int LibraryCard::getTotalBorrowedPages() const {
        int total = 0;
        for (int i = 0; i < borrowCount; ++i) {
            total += borrowedBooks[i]->getPages();
        }
        return total;
    }

    void LibraryCard::clear() {
        for (int i = 0; i < borrowCount; ++i) {
            delete borrowedBooks[i];
        }
        borrowCount = 0;
    }

    void LibraryCard::print(std::ostream& outStream) const {
        outStream << "Library Card for " << memberName << " (ID: " << memberID << ")\n";
        outStream << "Borrowed Books: " << borrowCount << "/" << capacity << "\n";
        for (int i = 0; i < borrowCount; ++i) {
            outStream << "  " << (i + 1) << ". ";
            borrowedBooks[i]->print(outStream);
            outStream << "\n";
        }
    }

    int LibraryCard::getTotalCardsIssued() {
        return totalCardsIssued;
    }

    bool compareByBorrowCount(const LibraryCard& card1, const LibraryCard& card2) {
        return card1.borrowCount > card2.borrowCount;
    }

}