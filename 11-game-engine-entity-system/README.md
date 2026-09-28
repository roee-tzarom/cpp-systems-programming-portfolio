# Game Entity System

An ownership-focused exercise with `Entity`, `Scene`, `Resource` and `SmartStack`. The code explores object lifetime, smart pointers, weak references and move semantics in a small scene/entity model.

## What this module demonstrates

RAII, smart pointers, scene composition and resource lifetime.

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

`Scene` owns entities with `unique_ptr`, shares resources with `shared_ptr` and observes resources with `weak_ptr`. `Entity` is move-only and carries position, health and inventory. `Resource` exposes load state and shared creation. `SmartStack<T>` uses a linked chain of `unique_ptr` nodes.

## Design decisions to inspect

The ownership graph is the central lesson: removing an entity transfers unique ownership, while a weak observer can detect when a shared resource is gone without keeping it alive. These types model scene state and lifetime; they do not render graphics or run a complete game loop.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
