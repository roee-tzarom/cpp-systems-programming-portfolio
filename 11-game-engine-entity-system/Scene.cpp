#include "Scene.hpp"
#include <stdexcept>

namespace gameengine {

Scene::Scene(const std::string& sceneName) : name(sceneName) {}

std::string Scene::getName() const { return name; }
size_t Scene::getEntityCount() const { return entities.size(); }
size_t Scene::getResourceCount() const { return resources.size(); }
size_t Scene::getObserverCount() const { return observers.size(); }

Entity* Scene::createEntity(const std::string& entName, double x, double y, int health) {
    auto newEntity = std::make_unique<Entity>(entName, x, y, health);
    Entity* ptr = newEntity.get(); // Keep a raw pointer for return
    entities.push_back(std::move(newEntity)); // Transfer the actual ownership to the vector
    return ptr;
}

void Scene::addEntity(std::unique_ptr<Entity> e) {
    entities.push_back(std::move(e));
}

std::unique_ptr<Entity> Scene::removeEntity(size_t index) {
    if (index >= entities.size()) throw std::out_of_range("Invalid entity index");
    auto removed = std::move(entities[index]); // Take ownership out of the vector
    entities.erase(entities.begin() + static_cast<long>(index));
    return removed;
}

Entity* Scene::getEntity(size_t index) const {
    if (index >= entities.size()) throw std::out_of_range("Invalid entity index");
    return entities[index].get();
}

Entity* Scene::findEntity(const std::string& entName) const {
    for (const auto& e : entities) {
        if (e->getName() == entName) return e.get();
    }
    return nullptr;
}

void Scene::addResource(std::shared_ptr<Resource> r) {
    // No std::move here because shared_ptr is meant to be copied (to increase the reference count)
    resources.push_back(r);
}

std::shared_ptr<Resource> Scene::getResource(size_t index) const {
    if (index >= resources.size()) throw std::out_of_range("Invalid resource index");
    return resources[index];
}

std::shared_ptr<Resource> Scene::findResource(const std::string& resName) const {
    for (const auto& r : resources) {
        if (r->getName() == resName) return r;
    }
    return nullptr;
}

long Scene::getResourceRefCount(size_t index) const {
    if (index >= resources.size()) throw std::out_of_range("Invalid resource index");
    return resources[index].use_count();
}

void Scene::addObserver(const std::string& obsName, std::weak_ptr<Resource> r) {
    observers[obsName] = r;
}

bool Scene::isObservedResourceAlive(const std::string& obsName) const {
    auto it = observers.find(obsName);
    if (it == observers.end()) throw std::invalid_argument("Observer not found");
    // expired checks if the original resource pointed to by the weak_ptr has already been deleted from memory
    return !it->second.expired(); 
}

std::shared_ptr<Resource> Scene::lockObservedResource(const std::string& obsName) const {
    auto it = observers.find(obsName);
    if (it == observers.end()) throw std::invalid_argument("Observer not found");
    // lock tries to upgrade the weak_ptr to a temporary shared_ptr. If the resource was deleted, we get nullptr.
    return it->second.lock(); 
}

void Scene::printSummary(std::ostream& os) const {
    os << "Scene: " << name << "\n";
    os << "Entities: " << entities.size() << "\n";
    for (const auto& e : entities) {
        os << " - " << e->getName() << "\n";
    }
    os << "Resources: " << resources.size() << "\n";
    for (const auto& r : resources) {
        os << " - " << r->getName() << " (Refs: " << r.use_count() << ")\n";
    }
    os << "Observers: " << observers.size() << "\n";
    for (const auto& pair : observers) {
        os << " - " << pair.first << "\n";
    }
}

} // namespace gameengine