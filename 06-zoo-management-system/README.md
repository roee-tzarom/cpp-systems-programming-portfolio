# Zoo Management System

An inheritance and polymorphism exercise with a base `Animal` type, `Bird`, `Mammal` and `Reptile` specializations, and a `Zoo` collection. The demo shows the types working together.

## What this module demonstrates

Animal hierarchy and zoo collection; virtual dispatch and object-oriented design.

## Build and inspect

From this directory, use a C++23-capable compiler and Make on Linux or WSL:

```bash
make demo
./demo
make test
```

`make demo` builds the example; `./demo` runs it; `make test` runs the included doctest-based checks. Start with `main.cpp` for usage, the matching headers for the public API, and `test.cpp` / `StudentTest.cpp` for examples and expected behavior. The included `doctest.h` is third-party test support.

This is a self-contained learning module within the [C++ portfolio](../README.md), not a deployed service.

## Component walkthrough

`Animal` defines common identity and virtual sound, type and diet behavior. `Bird`, `Mammal` and `Reptile` provide specialized data and overrides. `Zoo` stores animals, supports lookup and removal, and can print descriptions or invoke sounds across the collection.

## Design decisions to inspect

The point of the hierarchy is runtime dispatch through the base type. Inspect `Zoo::addAnimal` and copy operations to understand how concrete animal types are retained; the base class is abstract and cannot be instantiated directly.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
