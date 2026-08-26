/**
 * @file Resource.hpp
 * @brief Header file for the Resource class
 *
 * This file contains the Resource class which is shared among 
 * multiple entities using std::shared_ptr.
 */

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>
#include <memory>

namespace gameengine {

    class Resource {
    private:
        std::string name;
        std::string type;
        int sizeBytes;
        bool loaded;
        static int resourceCount; // מעקב אחר כמות המשאבים הכוללת

        // הבנאי פרטי כדי להכריח שימוש ב-factory method (create)
        Resource(const std::string& resName, const std::string& resType, int size);

    public:
        ~Resource();

        // חוק ה-5: מניעת העתקה רגילה כדי לאלץ שימוש ב-shared_ptr בלבד
        Resource(const Resource&) = delete;
        Resource& operator=(const Resource&) = delete;

        // Factory method ליצירת המשאב ישירות כ-shared_ptr
        static std::shared_ptr<Resource> create(const std::string& name, const std::string& type, int sizeBytes);
        static int getResourceCount();

        std::string getName() const;
        std::string getType() const;
        int getSizeBytes() const;
        bool isLoaded() const;
        std::string toString() const;
    };

} // namespace gameengine

#endif // RESOURCE_HPP