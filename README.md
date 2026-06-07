# File Reconstruction System (FRS)

A C++ console application that simulates **digital forensic file recovery**. Files in a local directory are indexed in an **AVL tree**, and deleted file metadata is tracked on a **recovery stack** so the most recently deleted entry can be restored.

This repository is organized as a staged coursework project. **Deliverable 3** is the current, complete implementation.

## Overview

The system scans a `Temp/` folder for regular files, assigns each one a unique integer ID, and stores metadata (`name`, `id`, `path`, `status`) in a self-balancing AVL tree. When a file is logically deleted, its metadata is pushed onto a stack before being removed from the tree. Recovery pops the stack and re-inserts or updates the file entry.

Supported file statuses: `Active`, `Deleted`, `Recovered`.

## Project Structure

```
File-Reconstruction-System/
├── Deliverable-2/          # Earlier prototype (linked list + vector-based stack)
│   ├── main.cpp
│   ├── include/DataStructures.h
│   ├── src/DataStructures.cpp
│   ├── build.sh
│   └── Temp/               # Sample files for scanning
│
└── Deliverable-3/          # Current implementation
    ├── main.cpp
    ├── include/DataStructures.h
    ├── src/DataStructures.cpp
    ├── build.sh
    ├── todo.txt
    └── Temp/               # Sample files for scanning
```

## Deliverable 3 — Architecture

### Data Structures

| Structure | Role | Key Operations |
|-----------|------|----------------|
| **AVL Tree** | Stores active file metadata, sorted by `id` | `insert`, `search` O(log n), `deleteById` with rotations |
| **Recovery Stack** | Linked-list stack of deleted file metadata | `push`, `pop`, `displayHistory` — all O(1) |
| **File struct** | Metadata record | `name`, `id`, `path`, `status` |

### FileManager

The `FileManager` class ties everything together:

- `scanDirectory(path)` — walks `Temp/` and inserts each file into the AVL tree
- `logicalDelete(id)` — searches the tree, pushes metadata to the stack, removes the node
- `recoverLastFile()` — pops the stack and re-inserts the file with status `Recovered`
- `printActiveList()` — in-order traversal of the AVL tree
- Interactive menu: **Delete**, **Recover**, **List**, **Quit**

### AVL Tree Details

The tree is keyed on file `id` and handles all four imbalance cases (LL, RR, LR, RL) via left and right rotations. Deletion supports nodes with zero, one, or two children using the in-order successor.

## Build and Run

Requirements: **g++** with C++17 support (`std::filesystem`).

```bash
cd Deliverable-3
./build.sh
./FRS
```

The program scans `Deliverable-3/Temp/` relative to the working directory. Place sample text files there before running.

## Usage

```
File Reconstruction System
1. Delete
2. Recover
3. List
4. Quit
```

1. **List** — shows all active files (sorted by ID via in-order traversal)
2. **Delete** — enter a file ID; metadata is saved to the recovery stack and removed from the tree
3. **Recover** — restores the most recently deleted file from the stack
4. **Quit** — exits the program

## Progression: Deliverable 2 → Deliverable 3

| Feature | Deliverable 2 | Deliverable 3 |
|---------|---------------|---------------|
| Active file storage | Singly linked list | AVL tree (sorted by ID) |
| Recovery stack | `std::vector` | Linked-list stack |
| File identification | Filename / path only | Unique integer `id` |
| User interface | Directory scan + print only | Full interactive menu |
| Encapsulation | Global `activeHead` pointer | `FileManager` class |

## Language and Tooling

- **Language:** C++17
- **Build:** `g++` via `build.sh`
- **Headers:** `include/DataStructures.h`
- **Implementation:** `src/DataStructures.cpp`
