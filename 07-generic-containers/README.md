# Generic Containers

A template-focused module containing a generic `Container`, `Stack`, `Queue` and reusable operations in `Algorithms.hpp`. It demonstrates how a common type parameter supports multiple data structures and algorithms.

## What this module demonstrates

Templates, stacks, queues and generic algorithms.

## Build and inspect

From this directory, use a C++23-capable compiler and Make on Linux or WSL:

```bash
make demo
make test
```

`make demo` builds and runs the example; `make test` runs the included doctest-based checks. Start with `main.cpp` for usage, the matching headers for the public API, and `test.cpp` / `StudentTest.cpp` for examples and expected behavior. The included `doctest.h` is third-party test support.

This is a self-contained learning module within the [C++ portfolio](../README.md), not a deployed service.
