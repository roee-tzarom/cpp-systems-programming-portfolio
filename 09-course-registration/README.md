# Course Registration

An in-memory student/course model. `CourseManager` coordinates student records, enrollment, grades and queries such as course intersections and averages; supporting files cover string and type-trait utilities.

## What this module demonstrates

STL containers, enrollment queries, grades and type traits.

## Build and inspect

From this directory, use a C++23-capable compiler and Make on Linux or WSL:

```bash
make demo
make test
```

`make demo` builds and runs the example; `make test` runs the included doctest-based checks. Start with `main.cpp` for usage, the matching headers for the public API, and `test.cpp` / `StudentTest.cpp` for examples and expected behavior. The included `doctest.h` is third-party test support.

This is a self-contained learning module within the [C++ portfolio](../README.md), not a deployed service.
