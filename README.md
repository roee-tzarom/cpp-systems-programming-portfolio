# Modern C++ Systems Programming Portfolio

A curated collection of modern C++ projects that progresses from object-oriented design and operator overloading to templates, STL, compile-time techniques, and safe resource management.

Each numbered module is self-contained and includes source code, tests, and a `Makefile` where applicable. The projects are kept as separate modules so that individual concepts are easy to explore and build.

## Modules

| Module | Focus |
| --- | --- |
| `01-geometry-toolkit` | Geometry types, utility functions, and composition |
| `02-music-library` | Songs, playlists, and library management with OOP |
| `03-library-management` | Books, authors, library cards, and domain modeling |
| `04-grade-management` | Grade records, aggregation, and operator overloading |
| `05-complex-number-toolkit` | Complex numbers, conversions, and copy semantics |
| `06-zoo-management-system` | Inheritance, polymorphism, and animal hierarchies |
| `07-generic-containers` | Templates, generic algorithms, stacks, and queues |
| `08-physics-math-engine` | Template specialisation, metaprogramming, and symbolic math |
| `09-course-registration` | STL-based course registration and type traits |
| `10-text-data-processing` | Text analysis and structured data processing |
| `11-game-engine-entity-system` | Smart pointers, move semantics, and entity lifetimes |

## Build a module

On Linux or WSL, open any module directory and run:

```bash
make clean
make demo
```

The repository intentionally excludes build products and editor-specific files.

## Skills demonstrated

- Modern C++ (C++20/C++23)
- Object-oriented design and polymorphism
- Templates, concepts, type traits, and metaprogramming
- STL containers and algorithms
- RAII, smart pointers, and move semantics
- Unit-oriented testing and Make-based builds
