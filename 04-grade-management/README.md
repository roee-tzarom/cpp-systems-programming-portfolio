# Grade Management

A student/grade model with `Student` and `Grade` classes. The module explores recording and aggregating academic results through an object-oriented API and a terminal demo.

## What this module demonstrates

Grade records and summaries; class invariants and operator-oriented exercises.

## Build and inspect

From this directory, use a C++23-capable compiler and Make on Linux or WSL:

```bash
make demo
make test
```

`make demo` builds and runs the example; `make test` runs the included doctest-based checks. Start with `main.cpp` for usage, the matching headers for the public API, and `test.cpp` / `StudentTest.cpp` for examples and expected behavior. The included `doctest.h` is third-party test support.

This is a self-contained learning module within the [C++ portfolio](../README.md), not a deployed service.
