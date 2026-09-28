# Library Management

A book and library-card model using separate `Book` and `LibraryCard` classes. The demo explores borrowing-related state and comparison helpers rather than a database-backed library service.

## What this module demonstrates

Books, card state and comparison helpers; encapsulation and domain rules.

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

`Book` holds a title, ISBN, page count and an `Author` value. `LibraryCard` maintains a member identity and resizable borrowed-book collection. Its API can borrow, return by index or title, search, clear and total borrowed pages.

## Design decisions to inspect

Availability and borrowing are represented in memory. Read the copy constructor and assignment operator to see how card-owned storage is handled; then check the demo for ordinary borrow/return flow. This is a model, not a library database or circulation service.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
