# Music Library

An object-oriented catalogue built from `Song`, `Playlist` and `MusicLibrary`. The module exercises relationships between domain objects and collection operations through a command-line demo.

## What this module demonstrates

Songs, playlists and library-level operations; class design and collections.

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

`Song` represents title, artist and duration. `Playlist` owns a resizable collection of songs, supports add/remove/find operations and reports total duration. `MusicLibrary` collects playlists, searches them by name and aggregates song count and playing time.

## Design decisions to inspect

The classes implement copy and move operations around owned dynamic storage. That makes this a useful module for discussing deep copies, moved-from state and destruction. Static counters track created playlists or songs added across instances.

## Repository tour

`main.cpp` is the executable example. The matching headers describe callable methods and data contracts; `.cpp` files contain out-of-line implementations where used. `test.cpp` and `StudentTest.cpp` are the available behavioral checks. Use `make demo` followed by `./demo` for the demonstration, `make test` for checks and `make clean` to remove generated build output. The folder is independent of the other ten modules, so build it from its own directory.
