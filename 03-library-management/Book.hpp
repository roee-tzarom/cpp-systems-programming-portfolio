/**
 * @file Book.hpp
 * @brief Header file for the Book class
 *
 * This file contains the declaration of the Book class which represents
 * a library book with title, author, ISBN, and pages.
 *
 * Students must implement the corresponding Book.cpp file.
 *
 * Topics covered:
 * - Composition (Book HAS-A Author)
 * - Constructors (default, parameterized, copy)
 * - Destructor
 * - Inline vs outline implementations
 * - Static members
 * - Friend functions
 * - Reference parameters and Reference-return
 */

#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <iostream>

namespace library {

    // ============ Composition Struct ============
    
    struct Author {
        std::string name;
        std::string country;
        int birthYear;

        Author() : name("Unknown"), country("Unknown"), birthYear(0) {}
        Author(const std::string& name, const std::string& country, int birthYear) 
            : name(name), country(country), birthYear(birthYear) {}
    };

    // ============ Main Class ============

    class Book {
    private:
        std::string title;
        Author author;      // Composition
        std::string ISBN;
        int pages;
        bool available;

        // Static members to track objects
        static int totalBooksCreated;
        static int currentBookCount;

    public:
        // ============ Constructors ============

        /**
         * @brief Default constructor
         * Creates an "Unknown" book with 0 pages.
         */
        Book();

        /**
         * @brief Parameterized constructor (Version 1 - Author as string)
         */
        Book(const std::string& title, const std::string& authorName, const std::string& ISBN, int pages);

        /**
         * @brief Parameterized constructor (Version 2 - Author as object)
         */
        Book(const std::string& title, const Author& authorObject, const std::string& ISBN, int pages);

        /**
         * @brief Copy constructor
         */
        Book(const Book& other);

        /**
         * @brief Destructor
         */
        ~Book();

        // ============ Getters (inline implementations) ============

        inline std::string getTitle() const { return title; }
        inline std::string getISBN() const { return ISBN; }
        inline int getPages() const { return pages; }
        inline bool getAvailability() const { return available; }
        inline const Author& getAuthor() const { return author; }
        inline Author& getAuthorReference() { return author; }

        // ============ Setters & Outline Methods ============

        void setTitle(const std::string& newTitle);
        void setAvailability(bool isAvailable);
        void setAuthor(const std::string& newAuthorName);
        void setAuthor(const Author& newAuthorObject);

        std::string getAuthorName() const;
        std::string getCategory() const;
        bool isLargeBook() const;
        
        /**
         * @brief Print book details to output stream
         */
        void print(std::ostream& outStream) const;

        // ============ Static methods ============

        static int getTotalBooksCreated();
        static int getCurrentBookCount();

        // ============ Friend functions ============

        /**
         * @brief Compare two books by their page count
         */
        friend bool compareByPages(const Book& book1, const Book& book2);

        /**
         * @brief Check if two books have the exact same author name
         */
        friend bool haveSameAuthor(const Book& book1, const Book& book2);
    };

    // Outside declarations of friend functions
    bool compareByPages(const Book& book1, const Book& book2);
    bool haveSameAuthor(const Book& book1, const Book& book2);

} // namespace library

#endif // BOOK_HPP