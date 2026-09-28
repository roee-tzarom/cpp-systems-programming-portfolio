# Course Registration

An in-memory student/course model. `CourseManager` coordinates student records, enrollment, grades and queries such as course intersections and averages; supporting files cover string and type-trait utilities.

## What this module demonstrates

STL containers, enrollment queries, grades and type traits.

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

`CourseManager` maintains student records, courses, enrollments and assigned grades in memory. It answers questions such as students in both courses, students in either course, a student’s course list and a course average. `StudentRecord.hpp`, `StringUtils.hpp` and `TypeTraitsUtils.hpp` provide separate supporting exercises.

## Design decisions to inspect

The intersection/union queries make the choice of STL collections visible. Explore the public manager API first, then the utility files. No database or persistence layer is present, so registrations last only for the process lifetime.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
