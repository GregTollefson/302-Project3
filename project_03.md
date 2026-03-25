# CS 302 – Project 3
## Music Library (Binary Search Tree)

**Assigned:** Monday Mar 16
**Due:** Thursday Apr 3

---

## Overview

In this project, you will design and implement a **Music Library**: a system that organizes songs so they can be inserted, searched, and displayed efficiently.

The focus of this project is on **hierarchical data organization** using a Binary Search Tree (BST). You will:

- Design and implement a templated BST that stores `Song` objects
- Enforce the BST ordering invariant
- Implement recursive insert, search, and remove
- Implement all three standard traversals using the visit-function pattern
- Implement `isBalanced()` and demonstrate that your tree is balanced
- Demonstrate correctness using a required checklist
- Build and compile your project using a **Makefile**

---

## How This Builds on Previous Projects

### From Project 1

Project 1 established your development workflow:

- Multi-file C++ with `.h` and `.cpp` separation
- Makefile builds
- Interface-driven design

All of those expectations carry forward here.

### From Project 2

Project 2 introduced ADT design discipline and two representations of the same behavior.

Project 3 builds on that foundation:

- You are still designing an ADT before coding
- You are still separating logical behavior from physical representation
- The structure is now **hierarchical** rather than linear

The key shift is this:

> In Project 2, ordering was controlled by access policy (FIFO or LIFO).
> In Project 3, ordering is enforced by **where items are placed** in the structure.

---

## Conceptual Grounding

A **Binary Search Tree** is a hierarchical structure in which:

- Every node stores a value
- All values in a node's **left subtree** are less than the node's value
- All values in a node's **right subtree** are greater than the node's value

This invariant makes search efficient, and it means that an **inorder traversal** of a BST always visits nodes in sorted order.

Your Music Library stores `Song` objects in a BST, ordered **alphabetically by title**.

---

## The Song Record

Your `Song` class must inherit from **both** `SongInterface` and `Comparable<Song>`:

```cpp
class Song : public SongInterface, public Comparable<Song>
```

`SongInterface` defines the record contract — getters, setters, and `display()`.
`Comparable<Song>` defines the ordering contract — `operator<` and `operator==`.

The BST does not know about `Song` directly. It only requires that its item type satisfies `Comparable<T>`. This is what makes `BST<Song>` work.

Each `Song` object must contain at minimum:

```cpp
string title;
string artist;
int year;
```

Appropriate accessor functions should be marked `const`.

Comparison between `Song` objects must be based on **title** (case-sensitive or case-insensitive — your choice, documented in `Design_Decisions.md`).

You must implement at least one meaningful operator overload for `Song`. Useful examples:

```cpp
bool operator<(const Song& other) const;    // Compare by title
bool operator==(const Song& other) const;   // Match by title
ostream& operator<<(ostream& out, const Song& s); // Display a song
```

---

## Templates

Your BST must be implemented as a **class template** (`BST<T>`). The tree logic — insert, remove, search, and traversal — does not depend on the stored type being a `Song`. It only requires that `T` supports comparison via `operator<` and `operator==`.

This means:

- Your **node** should be templated: `Node<T>` holds a `T` value and left/right child pointers
- Your **BST** should be templated: `BST<T>` implements insert, remove, contains, and traversals generically
- Your **MusicLibrary** class uses `BST<Song>` internally via composition (`MusicLibrary` *has a* `BST<Song>`)

The `Song` class satisfies `Comparable<Song>` — it provides `operator<` and `operator==` — which is what makes it compatible with `BST<Song>`. The BST only requires `Comparable<T>`; it never knows it is storing songs. This is the connection point: the BST doesn't know about songs, and the song doesn't know about trees.

---

## The Design Chain

Here is the full architecture you are building and how the pieces connect:

```
Provided interfaces (do not modify):

  Comparable<T>         SongInterface
        └──── Song ──────────┘         ← you implement Song

  BinaryTreeInterface<Song>
        └──── MusicLibrary             ← you implement MusicLibrary

  BST<T>  (T must satisfy Comparable<T>)
        └──── MusicLibrary has-a BST<Song>   ← you implement BST
```

- `Song` satisfies two contracts: the **record contract** (`SongInterface` — getters, setters, display) and the **ordering contract** (`Comparable<Song>` — `operator<`, `operator==`).
- `BST<T>` is generic. It never mentions `Song`. It only requires that `T` supports `Comparable<T>`. Plugging `Song` in gives you `BST<Song>`.
- `MusicLibrary` is the public face of the library. It inherits `BinaryTreeInterface<Song>` (the ADT contract) and owns a `BST<Song>` internally (composition). Clients call `MusicLibrary` — they never touch the BST directly.

This separation — interface from implementation, generic structure from concrete data — is the central design lesson of Project 3.

### Template Implementation Note

Because C++ templates are compiled at instantiation time, the **template implementation must be visible to the compiler** at the point of use. The standard approach is:

- Declare and define `BST<T>` entirely in `BST.h` (no separate `.cpp` file), **or**
- Place definitions in `BST.cpp` and `#include "BST.cpp"` at the bottom of `BST.h`

Either approach is acceptable. Document your choice in `Design_Decisions.md`.

---

## The BST Interface

Your `MusicLibrary` must implement the following interface. This interface is modeled directly on the textbook's `BinaryTreeInterface` (Chapter 15, Listing 15-1) and the BST operations defined in Chapter 15.3.

**This file is provided to you in the project ZIP. Do not modify the public method signatures.**

```cpp
// BinaryTreeInterface.h
#ifndef MUSIC_LIBRARY_INTERFACE_H
#define MUSIC_LIBRARY_INTERFACE_H

#include "Song.h"
#include "NotFoundException.h"

class BinaryTreeInterface<Song>
{
public:
    virtual ~BinaryTreeInterface<Song>() {}

    /** Returns true if the library contains no songs. */
    virtual bool isEmpty() const = 0;

    /** Returns the height of the BST. */
    virtual int getHeight() const = 0;

    /** Returns the number of songs in the library. */
    virtual int getNumberOfNodes() const = 0;

    /** Adds a song into the library maintaining BST order.
        @param newSong  The song to insert.
        @return True if successful, false otherwise. */
    virtual bool add(const Song& newSong) = 0;

    /** Removes a song from the library by title.
        @param aSong  A Song whose title identifies what to remove.
        @return True if successful, false if not found. */
    virtual bool remove(const Song& aSong) = 0;

    /** Removes all songs from the library. */
    virtual void clear() = 0;

    /** Retrieves a song by title.
        @param aSong  A Song whose title is used for lookup.
        @return The matching Song.
        @throw NotFoundException if not found. */
    virtual Song getEntry(const Song& anEntry) const = 0;

    /** Returns true if the library contains a song matching the given title.
        @param aSong  A Song whose title is used for lookup. */
    virtual bool contains(const Song& aSong) const = 0;

    /** Traverses the library in preorder, calling visit() on each song. */
    virtual void preorderTraverse(void visit(Song&)) const = 0;

    /** Traverses the library in inorder (alphabetical by title),
        calling visit() on each song. */
    virtual void inorderTraverse(void visit(Song&)) const = 0;

    /** Traverses the library in postorder, calling visit() on each song. */
    virtual void postorderTraverse(void visit(Song&)) const = 0;

    /** Tests whether the BST is height-balanced.
        A tree is balanced if every node's left and right subtrees
        differ in height by no more than 1.
        @return True if balanced; false otherwise. */
    virtual bool isBalanced() const = 0;
};

#endif
```

Your `MusicLibrary` class must inherit from `BinaryTreeInterface<Song>` and implement every method above:

```cpp
class MusicLibrary : public BinaryTreeInterface<Song>
```

---

## The Visit Function Pattern

The traversal methods accept a **client-defined function** as a parameter. This is the same design the textbook uses in Chapter 15 for `BinaryTreeInterface`.

The `visit` function defines what happens at each node. This keeps traversal logic inside the tree and display logic in `main` — exactly as the I/O rule requires.

**Example visit function and usage in `driver.cpp`:**

```cpp
void displaySong(Song& song)
{
    cout << song << endl;  // uses operator<< defined on Song
}

// In main:
library.inorderTraverse(displaySong);
```

Your traversal implementations should follow this structure:

```cpp
// Protected recursive helper — clients never call this directly
void MusicLibrary::inorder(void visit(Song&), Node<Song>* nodePtr) const
{
    if (nodePtr != nullptr)
    {
        inorder(visit, nodePtr->left);
        Song theSong = nodePtr->data;
        visit(theSong);
        inorder(visit, nodePtr->right);
    }
}

// Public method — matches the interface signature
void MusicLibrary::inorderTraverse(void visit(Song&)) const
{
    inorder(visit, root);
}
```

Public traversal methods are in the interface. The recursive helpers are **protected** — they are not visible to clients.

---

## ADT Design Document

Create: `ADT_Design.md`

Your ADT design must include:

### 1) Purpose
What problem your Music Library BST solves.

### 2) Logical Data Model
Describe the data stored logically. Do **not** mention nodes, pointers, or memory layout.

### 3) Operations
Document each method from the interface above. For each one, state:
- What it does
- What it returns
- What happens in edge cases (empty tree, not found, etc.)

### 4) Behavioral Guarantees
Clearly state:

- What ordering rule determines where a song is placed
- What `remove()` does when the title is not found
- What `contains()` and `getEntry()` do when a title is not found
- Why the BST ordering invariant is maintained after every insert and remove

---

## Implementation Requirements

### BST Structure

- Implement your BST as a class template `BST<T>` using **linked nodes** (pointer-based)
- Each node stores a `T` value and pointers to left and right children
- `MusicLibrary` uses `BST<Song>` via composition
- Do **not** use STL containers (`set`, `map`, `multimap`, etc.)

### Traversals

You must implement all three standard traversals using the visit-function pattern described above:

| Traversal | Visit Order | Result on a BST |
|-----------|-------------|-----------------|
| Preorder  | Root → Left → Right | Useful for copying the tree |
| Inorder   | Left → Root → Right | Visits nodes in sorted (alphabetical) order |
| Postorder | Left → Right → Root | Useful for deleting the tree |

Each traversal has:
- A **public method** matching the interface signature (accepts a `visit` function)
- A **protected recursive helper** that does the actual tree walking

### Remove

BST removal has three cases:

1. **Leaf node** — simply delete it
2. **One child** — replace the node with its child
3. **Two children** — replace with the inorder successor (leftmost node of right subtree), then delete the successor

You must handle all three cases correctly.

### Balance

Your `MusicLibrary` must produce a **balanced BST**. You are not required to implement AVL rotations. Instead:

- **Choose your insertion order deliberately** — think about what order of `add()` calls produces a balanced tree. A sorted insertion produces a degenerate linear tree (worst case). A median-first or level-order insertion produces a balanced one.
- **Implement `isBalanced()`** — recursively verify that no node's subtrees differ in height by more than 1.
- **Document your strategy** in `Design_Decisions.md`.

For a balanced tree of *n* nodes, the expected height is ⌊log₂(n)⌋ + 1. Your driver must print the height, node count, and `isBalanced()` result so the grader can verify.

### Memory Management

Because this is a pointer-based implementation:

- Your destructor must free all dynamically allocated nodes
- No memory leaks are acceptable

---

## Design Decisions

Create: `Design_Decisions.md`

Include:

1. **Ordering key** — why you chose title (or another field) as the comparison key
2. **Insertion order & balance** — what order you chose for `add()` calls and why it produces a balanced tree
3. **Operator overloading** — which operators you overloaded and why
4. **Template implementation** — whether you used header-only or the `#include` approach, and why
5. **Remove strategy** — how you handle the two-children case
6. **Traversal output format** — what each traversal prints and how it is formatted
7. **Edge cases** — how your implementation handles empty trees, duplicates, and missing keys

---

## Correctness Checklist (Required)

Your driver must demonstrate the following, with clearly labeled output:

- [ ] Add at least 8 songs and display the library using all three traversals
- [ ] Verify that inorder traversal produces songs in alphabetical order by title
- [ ] Search for a song that **exists** using `contains()` — confirm it is found
- [ ] Search for a song that **does not exist** using `contains()` — confirm it is not found
- [ ] Call `getEntry()` on a title that exists — confirm correct song returned
- [ ] Call `getEntry()` on a title that does not exist — confirm `NotFoundException` caught
- [ ] Remove a **leaf node** — confirm the song is gone
- [ ] Remove a node with **one child** — confirm structure is correct
- [ ] Remove a node with **two children** — confirm structure is correct
- [ ] Call `remove()` on a title that does not exist — confirm safe handling
- [ ] Verify `getNumberOfNodes()` updates correctly after insertions and removals
- [ ] Call `isBalanced()` — confirm `true`; print `getHeight()` and `getNumberOfNodes()`
- [ ] Verify `isEmpty()` returns true on an empty library

---

## Required Written Documentation

All written components must be submitted as **Markdown (`.md`) files**.

| File | Contents |
|------|----------|
| `ADT_Design.md` | ADT purpose, logical model, operations, behavioral guarantees |
| `Design_Decisions.md` | Ordering key, template approach, removal strategy, traversal format, edge cases |
| `README.md` | How to build and run, program overview, notable design decisions |

No PDFs or Word documents will be accepted for documentation.

---

## Directory Structure

Your project must use the following directory layout to keep source, headers, and build artifacts separate:

```
project_03/
├── include/                    <- Header files (.h)
│   ├── BinaryTreeInterface.h    (provided — do not modify)
│   ├── NotFoundException.h        (provided — do not modify)
│   ├── Song.h
│   ├── BST.h
│   └── MusicLibrary.h
├── src/                        <- Source files (.cpp)
│   ├── driver.cpp                 (provided — fill in TODOs)
│   ├── Song.cpp
│   └── MusicLibrary.cpp
├── build/                      <- Compiled output (generated by make)
├── Makefile
├── ADT_Design.md
├── Design_Decisions.md
└── README.md
```

- **`include/`** contains all `.h` files. The compiler flag `-Iinclude` tells g++ to look here when resolving `#include "Song.h"` and similar directives — so your `#include` statements do not need a path prefix.
- **`src/`** contains all `.cpp` files.
- **`build/`** is created automatically by `make`. All compiled output — `.o` files and the final executable — **must** go here, not in the project root or in `src/`. The provided Makefile already handles this. This directory is cleaned by `make clean`.

> **The provided Makefile handles all of this for you.** Read through it — every section is commented so you can understand what each part does. When you create a new `.cpp` file, the only change you need to make is adding it to the `SRCS` list in the Makefile.

---

## Files and Build Requirements

**Provided to you** (do not modify):
- `include/BinaryTreeInterface.h` — the pure abstract interface your `MusicLibrary` must implement

- `src/driver.cpp` — scaffolded test driver with `TODO` sections for you to fill in
- `Makefile` — pre-configured build system (read the comments to understand how it works)

**You must create:**
- `include/Song.h` / `src/Song.cpp` — inherits `SongInterface` and `Comparable<Song>`; implements all methods
- `include/BST.h` — the templated BST class (declaration and definition)
- `include/MusicLibrary.h` / `src/MusicLibrary.cpp` — uses `BST<Song>`, inherits from `BinaryTreeInterface<Song>`
- `ADT_Design.md`
- `Design_Decisions.md`
- `README.md`

### Build Requirements

```bash
make        # Builds the executable
make clean  # Removes build artifacts
make run    # Builds and runs the program
```

Compiler flags must include:

```bash
-std=c++17 -Wall -Wextra -pedantic
```

---

## Driver Program

> **Scaffolded driver provided.** A starter `driver.cpp` is included in the project ZIP. It contains the full test sequence matching the correctness checklist above, with labeled output sections and `TODO` placeholders. You must choose your own songs (at least 8) and fill in the song titles used for search and removal tests. Sketch your tree on paper so you know which nodes are leaves, which have one child, and which have two. The `getEntry()` section is also left as a `TODO` for you to complete based on your design. You may modify the driver (add songs, change formatting, add extra tests), but **all checklist items must remain covered**.

Your `driver.cpp` must:

- Build a `MusicLibrary` and populate it with at least **8 songs**
- Define a `displaySong(Song&)` visit function and use it with all three traversals
- Demonstrate `contains()` and `getEntry()`
- Demonstrate `remove()` for all three removal cases
- Demonstrate safe handling of edge cases (empty tree, missing title)
- Report `getNumberOfNodes()` and `isEmpty()` at key points

All console output should occur in `main` (via your visit function or direct calls). The tree itself should not print anything.

---

## File Submission Instructions

Submit **one ZIP file** named exactly:

```
project_03_lastname.zip
```

### Files to Include

- `include/` directory with all `.h` files
- `src/` directory with all `.cpp` files
- `Makefile`
- `ADT_Design.md`
- `Design_Decisions.md`
- `README.md`

> Note: `coding_standards.md` is provided — do not delete it from your submission.

### Files to Exclude

- `build/` directory (compiled `.o` files and executable)
- IDE-specific files or folders (`.vscode/`, `.idea/`, `.DS_Store`)
- Unrelated or temporary files

### Before Submitting

1. Run `make clean`
2. Verify `make` builds successfully
3. Verify the program runs correctly and output is clear

---

## Coding Standards

The following standards apply to this project and every project in this course. Code that does not meet these standards **will lose points**, regardless of whether the program compiles and runs correctly.

| # | Standard | Rule |
|---|---|---|
| 1 | **Naming** | Classes `PascalCase`, functions/variables `camelCase`, constants `ALL_CAPS` |
| 2 | **Bracing** | Always use `{}`, braces on their own lines, consistent 3- or 4-space indent |
| 3 | **Comments** | Every class and public method has a header comment; comments explain *why*, not *what* |
| 4 | **`const`** | Accessor methods and non-mutating reference parameters must be marked `const` |
| 5 | **Header Guards** | Every `.h` file uses `#ifndef` / `#define` / `#endif` |

See `coding_standards.md`, included in the project ZIP, for full details and examples.

---

## Final Notes

This project emphasizes **recursive thinking, tree structure, and invariant maintenance**.

The BST ordering invariant is your responsibility to uphold on every insert and remove. Traversals are your primary tool for verifying that the invariant holds.

Ask and answer questions in Canvas!

Go Team.
