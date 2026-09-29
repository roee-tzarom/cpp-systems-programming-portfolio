# Geometry Toolkit

A small C++23 geometry library built from explicit value types and free functions. It models points and circles, then uses them in distance, containment and aggregate calculations. The compact API makes the numeric behavior easy to inspect.

## Capabilities

- `Point` stores two-dimensional coordinates, and `distance` measures separation between points.
- `Circle` combines a center and radius; helpers calculate area, circumference and point containment.
- `Utilities` can select the point closest to the origin, construct a circle and average a numeric array.

```text
Point coordinates → distance / origin search
        ↓
Circle(center, radius) → area / circumference / containment
```

## Source layout

| File | Responsibility |
| --- | --- |
| `Point.hpp`, `Point.cpp` | Point type and distance calculation |
| `Circle.hpp`, `Circle.cpp` | Circle type and geometric operations |
| `Utilities.hpp`, `Utilities.cpp` | Helpers that combine or summarize values |
| `main.cpp` | Usage examples |
| `test.cpp` | Boundary and numeric checks |

The functions accept small value objects rather than maintaining a global geometry scene. That design keeps each calculation independently callable.

## Build and verify

From this directory, with a C++23-capable compiler and Make:

```bash
make demo
./demo
make test
```

The demo prints example results; the doctest suite checks calculations and boundary behavior. This module provides in-memory geometry operations, not graphics rendering or a spatial index.

[Back to the C++ portfolio](../README.md).
