/**
 * @file main.cpp
 * @brief Demo for Game Engine Entity System
 */

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include "Entity.hpp"
#include "Resource.hpp"
#include "Scene.hpp"
#include "SmartStack.hpp"

using namespace gameengine;

int main() {
    std::cout << "===== Game Engine Entity System Demo =====\n\n";

    // ---- Section 1: Entity with Move Semantics ----
    std::cout << "--- Entity: Move Semantics ---\n";

    Entity::resetIdCounter();

    Entity hero("Hero", 0.0, 0.0, 100);
    // Expected: Entity created: Hero (ID: 0)

    hero.addItem("Sword");
    hero.addItem("Shield");
    std::cout << hero.toString() << "\n";
    // Expected: Hero (ID: 0) at (0, 0) HP: 100 Items: 2

    // Move constructor
    Entity movedHero(std::move(hero));
    // Expected: Entity moved: Hero (ID: 0)

    std::cout << "Moved hero: " << movedHero.toString() << "\n";
    // Expected: Moved hero: Hero (ID: 0) at (0, 0) HP: 100 Items: 2

    std::cout << "Original hero alive: " << hero.isAlive() << "\n";
    // Expected: Original hero alive: 0

    std::cout << "Entity count: " << Entity::getEntityCount() << "\n";
    // Expected: Entity count: 1

    // Move assignment
    Entity villain("Villain", 10.0, 5.0, 80);
    // Expected: Entity created: Villain (ID: 1)

    movedHero = std::move(villain);
    // Expected: Entity move-assigned: Villain (ID: 1)

    std::cout << "After move-assign: " << movedHero.toString() << "\n";
    // Expected: After move-assign: Villain (ID: 1) at (10, 5) HP: 80 Items: 0

    std::cout << "Villain alive: " << villain.isAlive() << "\n";
    // Expected: Villain alive: 0

    // ---- Section 2: unique_ptr with Entities ----
    std::cout << "\n--- unique_ptr: Entity Ownership ---\n";

    auto entity1 = std::make_unique<Entity>("Goblin", 5.0, 3.0, 50);
    // Expected: Entity created: Goblin (ID: 2)

    std::cout << "Entity1: " << entity1->toString() << "\n";

    // Transfer ownership
    auto entity2 = std::move(entity1);
    std::cout << "entity1 is null: " << (entity1 == nullptr) << "\n";
    // Expected: entity1 is null: 1

    std::cout << "entity2: " << entity2->toString() << "\n";

    // ---- Section 3: shared_ptr with Resources ----
    std::cout << "\n--- shared_ptr: Shared Resources ---\n";

    auto texture = Resource::create("hero_texture", "texture", 4096);
    // Expected: Resource loaded: hero_texture (texture, 4096 bytes)

    std::cout << "Ref count: " << texture.use_count() << "\n";
    // Expected: Ref count: 1

    {
        auto textureCopy = texture;
        std::cout << "Ref count after copy: " << texture.use_count() << "\n";
        // Expected: Ref count after copy: 2
    }
    // textureCopy goes out of scope

    std::cout << "Ref count after scope: " << texture.use_count() << "\n";
    // Expected: Ref count after scope: 1

    // ---- Section 4: weak_ptr ----
    std::cout << "\n--- weak_ptr: Non-owning Observer ---\n";

    std::weak_ptr<Resource> weakTexture = texture;
    std::cout << "Weak expired: " << weakTexture.expired() << "\n";
    // Expected: Weak expired: 0

    {
        auto locked = weakTexture.lock();
        if (locked) {
            std::cout << "Locked: " << locked->toString() << "\n";
            // Expected: Locked: hero_texture (texture, 4096 bytes)
            std::cout << "Ref count while locked: " << texture.use_count() << "\n";
            // Expected: Ref count while locked: 2
        }
    }

    std::cout << "Ref count after lock released: " << texture.use_count() << "\n";
    // Expected: Ref count after lock released: 1

    texture.reset();
    // Expected: Resource unloaded: hero_texture

    std::cout << "Weak expired after reset: " << weakTexture.expired() << "\n";
    // Expected: Weak expired after reset: 1

    auto lockedAfter = weakTexture.lock();
    std::cout << "Lock after reset is null: " << (lockedAfter == nullptr) << "\n";
    // Expected: Lock after reset is null: 1

    // ---- Section 5: Scene (combining all) ----
    std::cout << "\n--- Scene: Combining Everything ---\n";

    Scene scene("Level 1");
    scene.createEntity("Player", 0, 0, 100);
    scene.createEntity("Enemy", 5, 5, 50);

    auto sharedSound = Resource::create("battle_music", "sound", 8192);
    scene.addResource(sharedSound);
    scene.addObserver("music_monitor", sharedSound);

    std::cout << "Scene entities: " << scene.getEntityCount() << "\n";
    // Expected: Scene entities: 2

    std::cout << "Scene resources: " << scene.getResourceCount() << "\n";
    // Expected: Scene resources: 1

    std::cout << "Music alive: " << scene.isObservedResourceAlive("music_monitor") << "\n";
    // Expected: Music alive: 1

    // Transfer entity out
    auto removed = scene.removeEntity(1);
    std::cout << "Removed: " << removed->toString() << "\n";
    std::cout << "Scene entities after removal: " << scene.getEntityCount() << "\n";
    // Expected: Scene entities after removal: 1

    scene.printSummary(std::cout);

    // ---- Section 6: SmartStack ----
    std::cout << "\n--- SmartStack ---\n";

    SmartStack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Stack: " << stack.toString() << "\n";
    // Expected: Stack: [30, 20, 10]

    std::cout << "Top: " << stack.top() << "\n";
    // Expected: Top: 30

    std::cout << "Pop: " << stack.pop() << "\n";
    // Expected: Pop: 30

    std::cout << "Stack after pop: " << stack.toString() << "\n";
    // Expected: Stack after pop: [20, 10]

    std::cout << "Size: " << stack.size() << "\n";
    // Expected: Size: 2

    // SmartStack with strings (move semantics)
    SmartStack<std::string> strStack;
    std::string item = "Sword of Power";
    strStack.push(item);                    // Copy
    strStack.push(std::move(item));         // Move (item is now empty)
    strStack.push("Magic Shield");          // Move (rvalue literal)

    std::cout << "String stack: " << strStack.toString() << "\n";
    // Expected: String stack: [Magic Shield, Sword of Power, Sword of Power]

    std::cout << "item after move: '" << item << "'\n";
    // Expected: item after move: ''

    // Move the entire stack
    SmartStack<int> stack2(std::move(stack));
    std::cout << "Moved stack2: " << stack2.toString() << "\n";
    // Expected: Moved stack2: [20, 10]

    std::cout << "Original stack empty: " << stack.empty() << "\n";
    // Expected: Original stack empty: 1

    // forEach
    std::cout << "ForEach: ";
    stack2.forEach([](const int& val) { std::cout << val << " "; });
    std::cout << "\n";
    // Expected: ForEach: 20 10

    // Clear
    stack2.clear();
    std::cout << "After clear: " << stack2.toString() << "\n";
    // Expected: After clear: []

    std::cout << "\n===== Demo Complete =====\n";

    return 0;
}