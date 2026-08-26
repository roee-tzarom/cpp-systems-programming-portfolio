/**
 * @file Scene.hpp
 * @brief Header file for the Scene class
 *
 * This file contains the Scene class which manages game entities
 * using unique_ptr and shared resources using shared_ptr/weak_ptr.
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "Entity.hpp"
#include "Resource.hpp"

namespace gameengine {

    class Scene {
    private:
        std::string name;
        // unique_ptr לישויות (בעלות מוחלטת ובלעדית - הסצנה היא הבעלים היחיד)
        std::vector<std::unique_ptr<Entity>> entities;
        // shared_ptr למשאבים (בעלות משותפת עם אובייקטים אחרים במשחק)
        std::vector<std::shared_ptr<Resource>> resources;
        // weak_ptr לצופים (לא מגדיל reference count, מונע דליפות זיכרון ממעגלי הצבעה)
        std::map<std::string, std::weak_ptr<Resource>> observers;

    public:
        explicit Scene(const std::string& sceneName);
        
        // שימוש ב-default מייצר אוטומטית בנאי העברה שעושה std::move לכל האיברים הפנימיים
        Scene(Scene&& other) noexcept = default;
        Scene& operator=(Scene&& other) noexcept = default;

        std::string getName() const;
        size_t getEntityCount() const;
        size_t getResourceCount() const;
        size_t getObserverCount() const;

        Entity* createEntity(const std::string& entName, double x, double y, int health);
        void addEntity(std::unique_ptr<Entity> e);
        std::unique_ptr<Entity> removeEntity(size_t index);
        Entity* getEntity(size_t index) const;
        Entity* findEntity(const std::string& entName) const;

        void addResource(std::shared_ptr<Resource> r);
        std::shared_ptr<Resource> getResource(size_t index) const;
        std::shared_ptr<Resource> findResource(const std::string& resName) const;
        long getResourceRefCount(size_t index) const;

        void addObserver(const std::string& obsName, std::weak_ptr<Resource> r);
        bool isObservedResourceAlive(const std::string& obsName) const;
        std::shared_ptr<Resource> lockObservedResource(const std::string& obsName) const;

        void printSummary(std::ostream& os) const;
    };

} // namespace gameengine

#endif // SCENE_HPP