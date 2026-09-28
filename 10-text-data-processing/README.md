# Text and Data Processing

A collection of STL-oriented components: `TextAnalyzer` for character/word statistics, `DataProcessor` for numeric transforms, `SetOperations` and `AlgorithmShowcase`. The demo presents these as independent processing examples.

## What this module demonstrates

Strings, maps, sets, numeric algorithms and transforms.

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

`TextAnalyzer` counts character classes, transforms strings and builds word-frequency maps. `DataProcessor` computes numeric aggregates and accepts predicates or comparators for filtering and ordering. `SetOperations` provides union, intersection and difference. `AlgorithmShowcase` demonstrates permutations, sequences, running totals and other STL patterns.

## Design decisions to inspect

The module is a collection of focused processors, not a single text pipeline. The input is supplied by the demo/tests. Look at method preconditions for empty data and mismatched vector sizes before reusing an algorithm in another application.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
