# Game Entity System

An ownership-focused C++23 model for entities, scenes and resources. It explores what happens when objects are created, transferred, shared, observed and destroyed, without requiring a graphics engine.

## Ownership model

```text
Scene
  ├─ unique_ptr<Entity>  → exclusive entity ownership
  ├─ shared_ptr<Resource> → shared resource lifetime
  └─ weak_ptr<Resource>   → observation without extending lifetime
```

`Entity` is move-only and carries identity, position, health and an inventory. `Scene` manages entities and resources. `Resource` tracks loading and shared creation. `SmartStack<T>` implements a linked stack whose nodes are owned through `unique_ptr`.

The distinction between shared and weak ownership is central: a weak observer can discover that a resource has expired without keeping it alive. Removing an entity also makes ownership transfer explicit.

## Explore the code

| File | Focus |
| --- | --- |
| `Entity.hpp`, `Entity.cpp` | Move-only state, health and inventory |
| `Scene.hpp`, `Scene.cpp` | Entity and resource relationships |
| `Resource.hpp`, `Resource.cpp` | Shared resource state |
| `SmartStack.hpp` | Linked ownership through smart pointers |
| `main.cpp`, `test.cpp` | Example flow and checks |

Start at `main.cpp`, then follow the `Scene` methods that add and remove entities. Inspect a resource's strong and weak references to understand when it can be destroyed.

## Build and run

With Make and a C++23-capable compiler:

```bash
make demo
./demo
make test
```

This module models lifetimes and state. It does not render graphics, process player input or implement a full game loop.

[Back to the C++ portfolio](../README.md).
