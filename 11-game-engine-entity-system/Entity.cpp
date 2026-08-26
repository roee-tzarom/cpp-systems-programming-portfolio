#include "Entity.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace gameengine {

int Entity::idCounter = 0;
int Entity::totalEntities = 0;

Entity::Entity(const std::string& entityName, double startX, double startY, int startHealth)
    : name(entityName), x(startX), y(startY), health(startHealth), id(idCounter++), alive(true) {
    if (health < 0) throw std::invalid_argument("Health cannot be negative");
    totalEntities++;
    std::cout << "Entity created: " << name << " (ID: " << id << ")\n";
}

Entity::~Entity() {
    // Decrease the counter only if the entity is "real" and not one emptied by Move (the code -1 indicates it is empty)
    if (id != -1) {
        totalEntities--;
    }
}

// Move Constructor
Entity::Entity(Entity&& other) noexcept
    // Use std::move to transfer ownership of the strings and vector without copying heavy data
    : name(std::move(other.name)), x(other.x), y(other.y), 
      health(other.health), id(other.id), alive(other.alive),
      inventory(std::move(other.inventory)) {
    
    // Reset the old object (Moved-from state) according to the test requirements
    other.name = "";
    other.health = 0;
    other.id = -1;
    other.alive = false;
    
    std::cout << "Entity moved: " << name << " (ID: " << id << ")\n";
}

// Move Assignment
Entity& Entity::operator=(Entity&& other) noexcept {
    // Prevent self-assignment (e.g., x = std::move(x)) to avoid accidentally clearing the object itself
    if (this != &other) {
        // If the current entity existed before, it is about to be overwritten, so we decrement the counter
        if (id != -1) totalEntities--;

        name = std::move(other.name);
        x = other.x;
        y = other.y;
        health = other.health;
        id = other.id;
        alive = other.alive;
        inventory = std::move(other.inventory);

        // Reset the source
        other.name = "";
        other.health = 0;
        other.id = -1;
        other.alive = false;

        std::cout << "Entity move-assigned: " << name << " (ID: " << id << ")\n";
    }
    return *this;
}

void Entity::resetIdCounter() { idCounter = 0; }
int Entity::getEntityCount() { return totalEntities; }

std::string Entity::getName() const { return name; }
double Entity::getX() const { return x; }
double Entity::getY() const { return y; }
int Entity::getHealth() const { return health; }
bool Entity::isAlive() const { return alive; }
int Entity::getId() const { return id; }

void Entity::addItem(const std::string& item) {
    inventory.push_back(item);
}

void Entity::addItem(std::string&& item) {
    // Move version: takes ownership of the string directly instead of creating a copy in memory
    inventory.push_back(std::move(item));
}

size_t Entity::getInventorySize() const { return inventory.size(); }

bool Entity::hasItem(const std::string& item) const {
    return std::find(inventory.begin(), inventory.end(), item) != inventory.end();
}

void Entity::takeDamage(int amount) {
    if (amount <= 0) throw std::invalid_argument("Damage must be positive");
    health -= amount;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

void Entity::heal(int amount) {
    if (amount <= 0) throw std::invalid_argument("Heal must be positive");
    if (alive) health += amount;
}

void Entity::setPosition(double newX, double newY) {
    x = newX; y = newY;
}

std::string Entity::toString() const {
    std::ostringstream oss;
    oss << name << " (ID: " << id << ") at (" << x << ", " << y << ") HP: " << health << " Items: " << inventory.size();
    return oss.str();
}

} // namespace gameengine