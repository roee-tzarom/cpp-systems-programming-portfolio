# Geometry Toolkit

A focused C++23 geometry exercise built around `Point`, `Circle` and reusable utility functions. The source separates data types (`Point.*`, `Circle.*`) from operations (`Utilities.*`), with `main.cpp` demonstrating the API.

## What this module demonstrates

Points, circles and geometry calculations; value types and small reusable functions.

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

`Point` stores coordinates; `distance` measures separation between two points. `Circle` adds a center and radius, with functions for area, circumference and point containment. `Utilities` includes closest-to-origin selection, circle construction and an average helper.

## Design decisions to inspect

The API uses small value types and free functions. Start with `main.cpp` to see how coordinates flow into a circle and how the result is printed. Check `test.cpp` for edge cases such as boundary points and distances.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
