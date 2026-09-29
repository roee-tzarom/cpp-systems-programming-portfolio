# Modern C++ Systems Programming Portfolio

Eleven self-contained C++23 projects developed during Computer Science studies at Ariel University. The collection moves from domain modeling and value semantics to templates, STL algorithms, compile-time techniques and explicit resource ownership. Each directory has its own demo, build configuration and tests.

## Explore by topic

| Project | What the implementation shows |
| --- | --- |
| [Geometry Toolkit](01-geometry-toolkit/) | Points, circles, distance and reusable geometry helpers |
| [Music Library](02-music-library/) | Songs, playlists, dynamic ownership and collection operations |
| [Library Management](03-library-management/) | Books, authors, lending state and deep-copy behavior |
| [Grade Management](04-grade-management/) | Grade values, operator overloads and transcript modeling |
| [Complex Number Toolkit](05-complex-number-toolkit/) | Complex arithmetic, arrays and copy semantics |
| [Zoo Management](06-zoo-management-system/) | An animal hierarchy, virtual behavior and polymorphism |
| [Generic Containers](07-generic-containers/) | Templated containers, stack, queue and generic algorithms |
| [Physics & Math Engine](08-physics-math-engine/) | Unit helpers, type-aware formatting and compile-time symbolic derivatives |
| [Course Registration](09-course-registration/) | STL-backed enrollment, grades and set-style queries |
| [Text & Data Processing](10-text-data-processing/) | Text statistics, numeric transformations, sets and algorithms |
| [Game Entity System](11-game-engine-entity-system/) | Smart pointers, scene ownership, resources and move semantics |

The projects are independent. Their numbered directory names provide a stable browsing order; there is no single executable that combines all eleven.

## Build a project

Use a C++23-capable compiler and Make on Linux or WSL. From the selected directory:

```bash
make demo
./demo
make test
```

The local `Makefile` defines the exact targets and compiler flags. `main.cpp` demonstrates the public API, while `test.cpp` contains doctest-based checks; `doctest.h` is included so a separate test package is not needed. Use `make clean` to remove generated binaries.

The Text & Data Processing demo currently contains an ambiguous empty-brace constructor call when compiled with `clang++` in C++23 mode. Its `make demo` target fails until that source line is resolved. Its `make test` target passes all 98 included test cases. Other directories can be built independently.

## A guided code review

- For **ownership and lifetime**, start with [Game Entity System](11-game-engine-entity-system/): follow the `Scene` to `Entity` and `Resource` relationships and the use of `unique_ptr`, `shared_ptr` and `weak_ptr`.
- For **generic programming**, inspect [Generic Containers](07-generic-containers/): template-based storage, stack and queue behavior, and algorithms over reusable types.
- For **compile-time reasoning**, open [Physics & Math Engine](08-physics-math-engine/): its expression types and derivative rules are represented in C++ templates.
- For **algorithms and data modeling**, compare [Course Registration](09-course-registration/) with [Text & Data Processing](10-text-data-processing/).

These are focused code projects rather than one production application. The demos and tests show the supported behavior, while each project's README explains its own design and boundaries.
