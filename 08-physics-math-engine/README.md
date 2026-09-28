# Physics and Math Templates

A C++23 template exercise combining unit conversions, type-aware formatting, `decltype` utilities and compile-time symbolic expression types. `Derivative.hpp` defines expression templates and derivative rules for supported forms.

## What this module demonstrates

Template specialization, type traits, units and compile-time differentiation.

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

`PhysicsUnits.hpp` contains constexpr conversions and physics formulas. `Formatter.hpp` and `TypeInfo.hpp` specialize behavior for selected types. `DecltypeUtils.hpp` deduces expression result types. `Derivative.hpp` defines expression types such as constants, variables, addition, multiplication and powers with evaluation and derivative rules.

## Design decisions to inspect

The symbolic component builds types at compile time rather than parsing a string at runtime. Start with the demo and then inspect the derivative specializations to see which forms are supported. The formulas and expression types are teaching examples, not a numerical simulation engine.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
