# Complex Number Toolkit

A C++23 numerical model with a `Complex` value type and a dynamically sized `ComplexArray`. It combines familiar arithmetic with the less visible problem of owning and copying a collection correctly.

## Capabilities

`Complex` stores real and imaginary components, exposes magnitude and supports arithmetic-style operations and comparisons. `ComplexArray` holds multiple values, grows as needed and supports insertion, removal, search and indexed access.

```text
Complex values → arithmetic and magnitude
       ↓
ComplexArray → owned storage, growth, search and copies
```

Both types expose counters that make object and collection lifetimes observable in the demo. The array's copying operations are especially useful to inspect: two arrays should own independent storage after a copy.

## Source map

| File | Focus |
| --- | --- |
| `Complex.hpp`, `Complex.cpp` | Numeric value behavior |
| `ComplexArray.hpp`, `ComplexArray.cpp` | Resizable ownership and collection operations |
| `main.cpp` | Demonstration of values and arrays |
| `test.cpp` | Arithmetic, indexing and copy checks |

## Build and run

From this directory with Make and a C++23-capable compiler:

```bash
make demo
./demo
make test
```

This is an in-memory numerical component. It does not implement arbitrary-precision complex arithmetic or external data formats.

[Back to the C++ portfolio](../README.md).
