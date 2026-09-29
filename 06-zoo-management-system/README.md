# Zoo Management System

An in-memory animal catalogue designed around a polymorphic `Animal` base class. A `Zoo` manages a collection while `Mammal`, `Bird` and `Reptile` provide type-specific behavior.

## Object model

```text
Animal (shared identity and age)
   ├─ Mammal  → legs and domestication
   ├─ Bird    → flight and wingspan
   └─ Reptile → venom and body length

Zoo → add, find, inspect and remove animals
```

The base class defines virtual sound, type and diet behavior. Each concrete animal overrides those operations, so the zoo can work through the common interface. The collection supports lookup by name and indexed access.

## What to inspect

- `Animal.hpp` defines the public contract and shared state.
- `Mammal.hpp`, `Bird.hpp` and `Reptile.hpp` show specialized fields and overridden behavior.
- `Zoo.cpp` contains collection management, growth and removal.
- `main.cpp` shows a working catalogue; `test.cpp` covers behavior and object relationships.

The interesting design question is how derived objects are stored and accessed through the base type. Follow `Zoo::addAnimal`, `findAnimal` and destruction to understand the ownership path.

## Build and run

With Make and a C++23-capable compiler:

```bash
make demo
./demo
make test
```

This is a domain model and terminal demo; it has no GUI, database or animal-care scheduling system.

[Back to the C++ portfolio](../README.md).
