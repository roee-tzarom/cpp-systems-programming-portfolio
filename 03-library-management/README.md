# Library Management

A book and library-card model using separate `Book` and `LibraryCard` classes. The demo explores borrowing-related state and comparison helpers rather than a database-backed library service.

## What this module demonstrates

Books, card state and comparison helpers; encapsulation and domain rules.

## Build and inspect

From this directory, use a C++23-capable compiler and Make on Linux or WSL:

```bash
make demo
make test
```

`make demo` builds and runs the example; `make test` runs the included doctest-based checks. Start with `main.cpp` for usage, the matching headers for the public API, and `test.cpp` / `StudentTest.cpp` for examples and expected behavior. The included `doctest.h` is third-party test support.

This is a self-contained learning module within the [C++ portfolio](../README.md), not a deployed service.
