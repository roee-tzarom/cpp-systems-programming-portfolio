# Game Entity System

An ownership-focused exercise with `Entity`, `Scene`, `Resource` and `SmartStack`. The code explores object lifetime, smart pointers, weak references and move semantics in a small scene/entity model.

## What this module demonstrates

RAII, smart pointers, scene composition and resource lifetime.

## Build and inspect

From this directory, use a C++23-capable compiler and Make on Linux or WSL:

```bash
make demo
make test
```

`make demo` builds and runs the example; `make test` runs the included doctest-based checks. Start with `main.cpp` for usage, the matching headers for the public API, and `test.cpp` / `StudentTest.cpp` for examples and expected behavior. The included `doctest.h` is third-party test support.

This is a self-contained learning module within the [C++ portfolio](../README.md), not a deployed service.
