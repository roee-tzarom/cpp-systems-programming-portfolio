/**
 * @file LibraryCard.hpp
 * @brief Header file for the LibraryCard class
 *
 * This file contains the declaration of the LibraryCard class which manages
 * a dynamic array of Book pointers (Composition and memory management).
 *
 * Topics covered:
 * - Dynamic arrays and pointers (Book**)
 * - Rule of Three (Copy constructor, Assignment operator, Destructor)
 * - Deep copying
 * - Reference parameters
 */

#ifndef LIBRARYCARD_HPP
#define LIBRARYCARD_HPP

#include <string>
#include <iostream>
#include "Book.hpp"

namespace library {

    class LibraryCard {
    private:
        std::string memberName;
        std::string memberID;
        Book** borrowedBooks; // Dynamic array of pointers to Books
        int capacity;
        int borrowCount;

        // Static tracking variable
        static int totalCardsIssued;

        /**
         * @brief Helper method to double the capacity of the array
         */
        void resize();

    public:
        // ============ Constructors & Destructor ============

        LibraryCard();
        LibraryCard(const std::string& memberName, const std::string& memberID, int capacity = 3);
        LibraryCard(const LibraryCard& other);
        LibraryCard& operator=(const LibraryCard& other);
        ~LibraryCard();

        // ============ Getters (inline implementations) ============

        inline std::string getMemberName() const { return memberName; }
        inline std::string getMemberID() const { return memberID; }
        inline int getCapacity() const { return capacity; }
        inline int getBorrowCount() const { return borrowCount; }
        inline bool isFull() const { return borrowCount == capacity; }

        // ============ Outline Methods ============

        void setMemberName(const std::string& newName);
        bool borrowBook(const Book& book);
        bool returnBook(int index);
        bool returnBook(const std::string& title);
        Book* findBorrowedBook(const std::string& title) const;
        int getTotalBorrowedPages() const;
        void clear();
        
        /**
         * @brief Print library card details
         */
        void print(std::ostream& outStream) const;

        // ============ Static Methods ============

        static int getTotalCardsIssued();

        // ============ Friend Functions ============

        /**
         * @brief Compare two cards by their borrow count
         */
        friend bool compareByBorrowCount(const LibraryCard& card1, const LibraryCard& card2);
    };

    bool compareByBorrowCount(const LibraryCard& card1, const LibraryCard& card2);

} // namespace library

#endif // LIBRARYCARD_HPP