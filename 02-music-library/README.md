# Music Library

An in-memory music catalogue with three layers: songs, playlists and a library that manages multiple playlists. The project emphasizes object relationships, dynamic storage and correct ownership when collections are copied or moved.

## Domain model

```text
MusicLibrary
   └─ Playlists
        └─ Songs
```

`Song` records title, artist and duration. `Playlist` maintains a resizable collection of songs and supports adding, removing, finding and calculating total play time. `MusicLibrary` organizes playlists by name and reports totals across the collection.

## Design to inspect

The playlist and library classes own dynamic storage. Their copy and move operations show how to keep two catalogues independent after a copy and how ownership transfers during a move. Static counters provide additional lifetime and activity information.

| Start with | Follow into | Why |
| --- | --- | --- |
| `main.cpp` | `MusicLibrary.hpp` | See the public catalogue workflow |
| `MusicLibrary.cpp` | `Playlist.cpp` | Follow collection growth and lookup |
| `Playlist.cpp` | `Song.cpp` | Follow song values and duration aggregation |
| `test.cpp` | Copy/move implementations | Check ownership cases |

## Build and run

Use a C++23-capable compiler and Make from this directory:

```bash
make demo
./demo
make test
```

The demo demonstrates the catalogue in memory; there is no audio playback, file import or persistent database.

[Back to the C++ portfolio](../README.md).
