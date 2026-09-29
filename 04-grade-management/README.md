# Grade Management

A C++23 academic-record model that separates a single grade value from a student's collection of course results. It provides a concrete setting for value constraints, operator overloading and owned collection storage.

## Model and behavior

`Grade` wraps a numeric score. Its API bounds values, supports arithmetic and comparison operators, converts to several representations and derives letter, passing and GPA-point information. `Student` associates `Grade` values with `Course` records and provides insertion, removal and lookup by index or course name.

```text
Student → owned course/grade records → summaries and lookup
              ↑
          Grade value rules
```

The `Grade` and `Student` classes have different responsibilities: the former defines score behavior, while the latter manages a record set. The student collection grows dynamically, so copying behavior is part of the implementation.

## Review path

1. Read `Grade.hpp` for the public operators and conversion methods.
2. Follow `Grade.cpp` to see bounds and how special cases are handled.
3. Inspect `Student.hpp` and `Student.cpp` for collection ownership and record operations.
4. Run `main.cpp` and inspect `test.cpp` for concrete scenarios.

## Build and run

From this directory:

```bash
make demo
./demo
make test
```

Requires Make and a C++23-capable compiler. Records live only for the process lifetime; there is no transcript file format or database.

[Back to the C++ portfolio](../README.md).
