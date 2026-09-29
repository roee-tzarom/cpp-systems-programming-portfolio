# Physics & Math Engine

A C++23 collection of compile-time and type-aware numerical components. Its most distinctive part represents symbolic expressions as C++ types and derives supported forms through template specializations rather than parsing a formula string at runtime.

## What is inside

| Header | Focus |
| --- | --- |
| `Derivative.hpp` | Expression types such as constants, variables, sums, products and powers, plus derivative rules |
| `PhysicsUnits.hpp` | Unit-oriented calculations and conversions |
| `Formatter.hpp` | Type-specific formatting through template specialization |
| `MySwap.hpp` | Generic and specialized swap behavior |
| `TypeInfo.hpp`, `DecltypeUtils.hpp` | Type traits and deduced result types |

For the symbolic component, an expression like a sum or product is assembled from types. `Derive<...>` selects a matching derivative rule at compile time. The resulting type can then be evaluated for a numeric input or rendered as text. This illustrates how templates can encode a computation's structure.

## Build and inspect

Use Make and a C++23-capable compiler from this directory:

```bash
make demo
./demo
make test
```

`main.cpp` demonstrates the components. `test.cpp` checks the supported behavior; the project includes its own `doctest.h` header. The complete source set was restored from the original repository, and the 57 included test cases passed in the verified build.

The symbolic rules cover the expression forms implemented in `Derivative.hpp`. This is not a general algebra parser or a numerical physics simulator.

[Back to the C++ portfolio](../README.md).
