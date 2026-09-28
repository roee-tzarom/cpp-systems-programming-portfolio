# Physics and Math Templates

A C++23 template exercise combining unit conversions, type-aware formatting, `decltype` utilities and compile-time symbolic expression types. `Derivative.hpp` defines expression templates and derivative rules for supported forms.

## What this module demonstrates

Template specialization, type traits, units and compile-time differentiation.

## Build and inspect

From this directory, use a C++23-capable compiler and Make on Linux or WSL:

```bash
make demo
make test
```

`make demo` builds and runs the example; `make test` runs the included doctest-based checks. Start with `main.cpp` for usage, the matching headers for the public API, and `test.cpp` / `StudentTest.cpp` for examples and expected behavior. The included `doctest.h` is third-party test support.

This is a self-contained learning module within the [C++ portfolio](../README.md), not a deployed service.
