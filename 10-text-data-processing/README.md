# Text & Data Processing

A set of C++23 components for manipulating text, numeric sequences and mathematical sets with the standard library. The components are independent, so each can be reviewed by the algorithm and data structure it uses.

## Components

| Component | Capabilities |
| --- | --- |
| `TextAnalyzer` | Character and word statistics, text transformations and frequency maps |
| `DataProcessor` | Aggregates, numeric transforms, filtering, ordering and generated sequences |
| `SetOperations` | Union, intersection and difference |
| `AlgorithmShowcase` | Permutations, running totals, dot products and iterator-based operations |

The design favors named operations over one large pipeline. `main.cpp` supplies example inputs, while `test.cpp` checks behavior and edge cases. Read the header of a component first to see its preconditions, then follow the corresponding implementation.

## Build status

Use Make and a C++23-capable compiler. The test target can be run from this directory:

```bash
make test
```

The current `main.cpp` contains `DataProcessor dp10({});`. In C++23 mode this empty-brace call is ambiguous between the vector constructor and copy/move constructors with the Clang compiler used during verification, so `make demo` does not currently build. The library components and their tests remain available for review. Resolve that constructor call in the source before using the demo target.

The `make test` target was verified locally: 98 test cases and 147 assertions passed.

## Repository tour

`TextAnalyzer.*` is a good start for string and map operations. `DataProcessor.*` shows algorithms parameterized by predicates and comparators. `SetOperations.*` isolates set algebra, while `AlgorithmShowcase.*` collects reusable sequence operations.

These are local in-memory algorithms. There is no file-ingestion service, external data source or persistent storage.

[Back to the C++ portfolio](../README.md).
