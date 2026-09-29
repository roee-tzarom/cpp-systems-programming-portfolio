# Library Management Model

A C++23 model of books and borrowing cards. It keeps author and book information separate from the card that tracks borrowed items, so the rules for lending state can be read in one place.

## Core objects

- `Author` is a value associated with a `Book`.
- `Book` keeps a title, author, ISBN, page count and availability state. It exposes comparison helpers and category information.
- `LibraryCard` associates a member with a resizable borrowed-book collection. It supports borrowing, returning, searching, clearing and totaling pages.

```text
Author → Book → LibraryCard's borrowed collection
```

The model works entirely in memory. Copying is important because a card owns its collection; two cards should not share one raw allocation after a copy.

## Where to read

| File | Focus |
| --- | --- |
| `Book.hpp`, `Book.cpp` | Book metadata, availability and comparisons |
| `LibraryCard.hpp`, `LibraryCard.cpp` | Member state and borrow/return operations |
| `main.cpp` | Example lending workflow |
| `test.cpp` | Behavior and copy-related checks |

## Build and run

With a C++23-capable compiler and Make:

```bash
make demo
./demo
make test
```

The module demonstrates domain rules and ownership. It does not include a catalogue server, database or persistent circulation history.

[Back to the C++ portfolio](../README.md).
