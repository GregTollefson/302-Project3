# Project 3 Rubric: Music Library (Binary Search Tree)
**Total: 100 points**

---

## 1. Project Structure & Build (10 points)

**Makefile (5 pts)**
- Builds successfully using `make`
- Uses required flags (`-std=c++17 -Wall -Wextra -pedantic`)
- `make clean` removes generated files
- `make run` builds and runs the program

**File Organization (5 pts)**
- Proper `.h` / `.cpp` separation for `Song` and `MusicLibrary`
- `BST.h` contains the complete template (declaration and definition)
- `MusicLibrary` inherits from `BinaryTreeInterface<Song>`
- Provided files (`BinaryTreeInterface.h`, `NotFoundException.h`, `driver.cpp`) included unmodified

---

## 2. Song Record (5 points)

- `Song` inherits from both `SongInterface` and `Comparable<Song>` **(1 pt)**
- All getters and setters implemented; accessors marked `const` **(1 pt)**
- `operator<` compares by title (satisfies `Comparable<Song>`) **(1 pt)**
- `operator==` compares by title (satisfies `Comparable<Song>`) **(1 pt)**
- `display()` implemented; `operator<<` in `SongInterface` calls it correctly **(1 pt)**

---

## 3. Templated BST (`BST<T>`) (20 points)

- `Node<T>` struct/class defined with data, left, and right pointer fields **(3 pts)**
- `BST<T>` is a class template constrained to `Comparable<T>` — no hardcoded `Song` type anywhere in `BST.h` **(4 pts)**
- `add()` places items correctly, maintaining BST ordering invariant **(4 pts)**
- `contains()` / `getEntry()` search correctly and handle missing entries **(3 pts)**
- `getHeight()` computed correctly via recursion **(3 pts)**
- `getNumberOfNodes()` accurate after all operations **(2 pts)**
- Template implementation is fully visible to the compiler (header-only or `#include` approach) **(1 pt)**

---

## 4. BST Remove — All Three Cases (20 points)

- **Leaf node removal** — node deleted, parent pointer set to `nullptr` **(6 pts)**
- **One-child removal** — node replaced by its sole child **(6 pts)**
- **Two-children removal** — replaced with inorder successor; successor correctly found and deleted **(8 pts)**

Partial credit awarded per case. A case earns 0 pts if it crashes, corrupts the tree, or is not attempted.

---

## 5. Traversals & Balance (20 points)

**Traversals — Visit-Function Pattern (15 pts)**
- Each of the three traversals accepts a `void visit(Song&)` function parameter **(3 pts)**
- **Preorder** visits Root → Left → Right correctly **(3 pts)**
- **Inorder** visits Left → Root → Right correctly; produces alphabetical output on a valid BST **(5 pts)**
- **Postorder** visits Left → Right → Root correctly **(3 pts)**
- Each public traversal delegates to a **protected recursive helper**; clients never access the helper directly **(1 pt)**

**Balance (5 pts)**
- `isBalanced()` implemented recursively — checks that every node's left and right subtrees differ in height by no more than 1 **(3 pts)**
- Driver calls `isBalanced()` and prints the result alongside `getHeight()` and `getNumberOfNodes()` **(1 pt)**
- `Design_Decisions.md` explains the insertion order chosen and why it produces a balanced tree **(1 pt)**

---

## 6. MusicLibrary & Interface Conformance (5 points)

- `MusicLibrary` inherits from `BinaryTreeInterface<Song>` with correct template syntax **(1 pt)**
- All pure virtual methods implemented with correct signatures **(2 pts)**
- `MusicLibrary` uses `BST<Song>` via composition (has-a relationship) **(1 pt)**
- `clear()` correctly removes all songs and resets state **(1 pt)**

---

## 7. Memory Management (5 points)

- Destructor frees all dynamically allocated nodes **(3 pts)**
- No memory leaks detected (verified by running with valgrind or equivalent) **(2 pts)**

---

## 8. ADT Design Document (5 points)

`ADT_Design.md` must include:

- Clear statement of purpose **(1 pt)**
- Logical data model — no mention of nodes, pointers, or memory layout **(1 pt)**
- All interface methods documented with behavior and edge-case handling **(2 pts)**
- BST ordering invariant explicitly stated; behavior on empty tree and missing keys described **(1 pt)**

---

## 9. Coding Standards (10 points)

All five course coding standards must be followed throughout the project.

**Naming Conventions (2 pts)**
- Classes use `PascalCase`
- Functions and variables use `camelCase`
- Constants use `ALL_CAPS`
- Names are self-documenting

**Indentation and Bracing (2 pts)**
- Consistent 3- or 4-space indentation throughout
- Braces always used, even for single-line bodies
- Open and close braces on their own lines

**Comments (2 pts)**
- Every class has a header comment
- Every public method has a header comment
- Inline comments explain *why*, not *what*

**`const` Correctness (2 pts)**
- All accessor methods marked `const`
- All non-mutating reference parameters marked `const`

**Header Guards (2 pts)**
- Every `.h` file has a proper `#ifndef` / `#define` / `#endif` guard
- Guard names match filenames

---

## 10. Driver & Correctness Checklist (5 points)

Each checklist item is worth ~0.42 pts. All items must be demonstrated with clearly labeled output.

- [ ] Insert at least 8 songs and display with all three traversals
- [ ] Inorder output is in alphabetical order by title
- [ ] `contains()` returns true for an existing song
- [ ] `contains()` returns false for a non-existent song
- [ ] `getEntry()` returns the correct song when found
- [ ] `getEntry()` handles the not-found case safely (NotFoundException caught)
- [ ] Leaf node removed correctly
- [ ] One-child node removed correctly
- [ ] Two-children node removed correctly
- [ ] `remove()` on a non-existent title is handled safely
- [ ] `getNumberOfNodes()` reflects correct count after insertions and removals
- [ ] `isBalanced()` returns true; `getHeight()` and `getNumberOfNodes()` printed
- [ ] `isEmpty()` returns true on an empty library

---

# Submission Requirements

- `Design_Decisions.md` covers: ordering key and insertion order chosen for balance, operator overloading rationale, template implementation choice, remove strategy, traversal output format, edge case handling
- `README.md` present with build instructions and program overview
- ZIP named correctly (`project_03_lastname.zip`); no compiled files or IDE artifacts

---

# Grading Philosophy

This project emphasizes **recursive thinking, hierarchical structure, and invariant maintenance**.

Remove is the hardest operation. Students who skip it or only partially implement it will lose up to 20 points. Warn students early: do not leave remove for the last weekend.

If the BST ordering invariant is broken after insert, remove credit will be reduced — a corrupted tree makes traversal results meaningless.

Code that does not follow the CS 302 Coding Standards will lose points regardless of whether it compiles and runs correctly.
