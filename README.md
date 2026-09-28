# Modern C++ Programming Portfolio

Eleven self-contained C++ modules that progress from domain modeling and operator overloading to generic containers, STL algorithms, compile-time techniques and ownership-aware design. Each module has its own `Makefile`, demo program and tests.

## Modules

| Module | What to inspect |
| --- | --- |
| [01 — Geometry toolkit](01-geometry-toolkit/) | Points, circles and geometry utilities |
| [02 — Music library](02-music-library/) | Songs, playlists and library operations |
| [03 — Library management](03-library-management/) | Books and library-card state |
| [04 — Grade management](04-grade-management/) | Students, grade records and aggregation |
| [05 — Complex numbers](05-complex-number-toolkit/) | Complex arithmetic, arrays and copy semantics |
| [06 — Zoo system](06-zoo-management-system/) | Animal hierarchy and polymorphism |
| [07 — Generic containers](07-generic-containers/) | Templated container, stack, queue and algorithms |
| [08 — Physics/math engine](08-physics-math-engine/) | Units, formatting, type traits and compile-time symbolic differentiation |
| [09 — Course registration](09-course-registration/) | Student/course records, enrollment and grades |
| [10 — Text/data processing](10-text-data-processing/) | Text analysis, numeric data transforms and set operations |
| [11 — Entity system](11-game-engine-entity-system/) | Entities, scenes, resources and smart-pointer ownership |

## Build and test one module

Use a C++23-capable compiler and Make on Linux or WSL:

```bash
cd 07-generic-containers
make demo
./demo
make test
```

Each module's `Makefile` is the source of truth for its targets and flags. The included `doctest.h` is a vendored test framework. Modules are exercises with independent demos, not a single integrated application.

The strongest systems concepts are visible in modules 07–11: generic programming, algorithms, compile-time expression types and explicit resource lifetimes. See each module's README and source for its exact API and examples.
