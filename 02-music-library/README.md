# Music Library

An object-oriented catalogue built from `Song`, `Playlist` and `MusicLibrary`. The module exercises relationships between domain objects and collection operations through a command-line demo.

## What this module demonstrates

Songs, playlists and library-level operations; class design and collections.

## Build and inspect

From this directory, use a C++23-capable compiler and Make on Linux or WSL:

```bash
make demo
make test
```

`make demo` builds and runs the example; `make test` runs the included doctest-based checks. Start with `main.cpp` for usage, the matching headers for the public API, and `test.cpp` / `StudentTest.cpp` for examples and expected behavior. The included `doctest.h` is third-party test support.

This is a self-contained learning module within the [C++ portfolio](../README.md), not a deployed service.
