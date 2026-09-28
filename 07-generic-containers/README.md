# Generic Containers

A template-focused module containing a generic `Container`, `Stack`, `Queue` and reusable operations in `Algorithms.hpp`. It demonstrates how a common type parameter supports multiple data structures and algorithms.

## What this module demonstrates

Templates, stacks, queues and generic algorithms.

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

`Container<T>` manages resizable storage and exposes an iterator. `Stack<T>` wraps last-in-first-out operations; `Queue<T>` wraps first-in-first-out operations. `Algorithms.hpp` adds generic print, find, count, contains and sum helpers.

## Design decisions to inspect

This module shows how one storage abstraction can support different interfaces. Inspect bounds and empty-container exceptions in the headers. The queue removes its front element from a sequential container, which is simple for teaching but not the constant-time queue design used in a performance-oriented implementation.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
