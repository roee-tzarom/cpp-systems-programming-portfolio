# Text and Data Processing

A collection of STL-oriented components: `TextAnalyzer` for character/word statistics, `DataProcessor` for numeric transforms, `SetOperations` and `AlgorithmShowcase`. The demo presents these as independent processing examples.

## What this module demonstrates

Strings, maps, sets, numeric algorithms and transforms.

## Build and inspect

From this directory, use a C++23-capable compiler and Make on Linux or WSL:

```bash
make demo
make test
```

`make demo` builds and runs the example; `make test` runs the included doctest-based checks. Start with `main.cpp` for usage, the matching headers for the public API, and `test.cpp` / `StudentTest.cpp` for examples and expected behavior. The included `doctest.h` is third-party test support.

This is a self-contained learning module within the [C++ portfolio](../README.md), not a deployed service.
