# Course Registration

An in-memory C++23 model for students, courses, enrollment and grades. The core `CourseManager` API supports both ordinary updates and questions that combine information across collections.

## Typical workflow

```text
add student → create course → enroll → assign grade
                                ↓
                     counts, averages and set queries
```

`StudentRecord` stores student details. `CourseManager` can add or remove enrollment, list students in a course, list a student's courses, assign grades and calculate a course average. It also answers intersection and union style questions, such as which students are in both of two courses. String and type-trait utilities live in separate supporting files.

## Code map

| File | Responsibility |
| --- | --- |
| `CourseManager.hpp`, `CourseManager.cpp` | Registration, grades and queries |
| `StudentRecord.hpp`, `StudentRecord.cpp` | Student data |
| `StringUtils.hpp`, `StringUtils.cpp` | String transformations |
| `TypeTraitsUtils.hpp` | Compile-time type utilities |
| `main.cpp`, `test.cpp` | Usage and behavioral checks |

Inspect the manager's public API first, then follow its STL collections through enrollment and set-style queries. Data is held only in memory; restarting the program clears the registrations.

## Build and run

From this directory with Make and a C++23-capable compiler:

```bash
make demo
./demo
make test
```

This is a data-model demonstration, not a deployed registration service or student-information database.

[Back to the C++ portfolio](../README.md).
