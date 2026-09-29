# Generic Containers and Algorithms

A template-based C++23 collection library with a resizable `Container<T>`, stack and queue adapters, and algorithms that work over the generic container. The project makes data-structure behavior visible instead of hiding it behind a standard-library container.

## Components

| Component | Role |
| --- | --- |
| `Container<T>` | Dynamic storage, indexed access, removal and iterator support |
| `Stack<T>` | Last-in, first-out operations built on the container |
| `Queue<T>` | First-in, first-out operations built on the container |
| `Algorithms.hpp` | Generic search, formatting and transformation helpers |

The stack uses the end of the underlying collection as its top; the queue uses the front. Read their `pop` and `dequeue` paths to see how each policy affects the same storage abstraction. `Container<T>` exposes an iterator so values can participate in familiar iteration patterns.

## Reading path

Start with `main.cpp` to see the types in use, then inspect `Container.hpp` for capacity growth and bounds behavior. Next compare `Stack.hpp` and `Queue.hpp`. Finish with `Algorithms.hpp` to see how templates make operations reusable across element types.

## Build and run

From this directory:

```bash
make demo
./demo
make test
```

Requires Make and a C++23-capable compiler. This code emphasizes implementation and semantics; it is not presented as a performance replacement for `std::vector`, `std::stack` or `std::queue`.

[Back to the C++ portfolio](../README.md).
