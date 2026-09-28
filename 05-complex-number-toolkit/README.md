# Complex Number Toolkit

A numerical exercise with `Complex` and `ComplexArray` classes. It covers arithmetic-style operations, array ownership and copy behavior using a small demonstration program.

## What this module demonstrates

Complex arithmetic and arrays; value semantics and copy behavior.

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

`Complex` implements rectangular complex values, magnitude, conjugate, arithmetic and explicit conversions. `ComplexArray` owns a dynamic sequence with add/remove, search, sum, average and maximum operations.

## Design decisions to inspect

This module connects numerical operators to container ownership. Its copy constructor and assignment operator are important when arrays share-looking values but must own separate storage. The demo and tests show the supported arithmetic and array semantics.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
