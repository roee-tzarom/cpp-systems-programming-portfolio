/**
 * @file Entity.hpp
 * @brief Header file for the Entity class
 *
 * This file contains the Entity class representing a game object.
 * It demonstrates move semantics, rule of five, and unique ownership.
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <vector>

namespace gameengine {

    class Entity {
    private:
        std::string name;
        double x, y;
        int health;
        int id;
        bool alive;
        std::vector<std::string> inventory;

        static int idCounter;
        static int totalEntities;

    public:
        Entity(const std::string& entityName, double startX, double startY, int startHealth);
        ~Entity();

        // חוק ה-5: חוסמים העתקה (Copy), מאפשרים רק העברה (Move)
        Entity(const Entity&) = delete;
        Entity& operator=(const Entity&) = delete;

        // Move Semantics (בנאי ואופרטור העברה) - חובה להגדיר noexcept כדי שוקטורים יעבירו במקום להעתיק
        Entity(Entity&& other) noexcept;
        Entity& operator=(Entity&& other) noexcept;

        static void resetIdCounter();
        static int getEntityCount();

        std::string getName() const;
        double getX() const;
        double getY() const;
        int getHealth() const;
        bool isAlive() const;
        int getId() const;

        void addItem(const std::string& item);
        void addItem(std::string&& item); // גרסת Move שחוסכת העתקה של המחרוזת
        size_t getInventorySize() const;
        bool hasItem(const std::string& item) const;

        void takeDamage(int amount);
        void heal(int amount);
        void setPosition(double newX, double newY);

        std::string toString() const;
    };

} // namespace gameengine

#endif // ENTITY_HPP