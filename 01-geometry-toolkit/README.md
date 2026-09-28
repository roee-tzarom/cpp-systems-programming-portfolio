# Geometry Toolkit

A focused C++23 geometry exercise built around `Point`, `Circle` and reusable utility functions. The source separates data types (`Point.*`, `Circle.*`) from operations (`Utilities.*`), with `main.cpp` demonstrating the API.

## What this module demonstrates

Points, circles and geometry calculations; value types and small reusable functions.

## Build and inspect

From this directory, use a C++23-capable compiler and Make on Linux or WSL:

```bash
make demo
make test
```

`make demo` builds and runs the example; `make test` runs the included doctest-based checks. Start with `main.cpp` for usage, the matching headers for the public API, and `test.cpp` / `StudentTest.cpp` for examples and expected behavior. The included `doctest.h` is third-party test support.

This is a self-contained learning module within the [C++ portfolio](../README.md), not a deployed service.
