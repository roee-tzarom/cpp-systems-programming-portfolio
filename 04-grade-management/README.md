# Grade Management

A student/grade model with `Student` and `Grade` classes. The module explores recording and aggregating academic results through an object-oriented API and a terminal demo.

## What this module demonstrates

Grade records and summaries; class invariants and operator-oriented exercises.

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

`Grade` wraps a bounded numeric result and overloads arithmetic and comparison. `Student` associates grades with `Course` records, supports adding and removing entries and exposes indexed or course-name access.

## Design decisions to inspect

The two classes separate grade arithmetic from a student transcript. Inspect `Grade::bound` and the operator implementations before assuming how out-of-range inputs or division are handled. The student collection uses resizable owned storage, so copy behavior matters.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
