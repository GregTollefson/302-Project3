
# CS 302 Project 3 — Music Library (BST)

## Overview

This project implements a **Music Library** using a **Binary Search Tree (BST)**.  
The library stores songs and supports insertion, remove, and traverse operations.

Songs are organized according to their **title**, allowing:
- efficient lookup
- alphabetical display via inorder traversal
- structured traversal (preorder, inorder, postorder)

The project demonstrates:
- templated BST implementation
- operator overloading
- recursive tree algorithms
- abstraction via interfaces

---


#### Build and Run 

To build - From the project root directory:

```bash
make
```
To run - From the project root directory:

```bash
make run
```
Prior to submitting: 
```bash
make clean
```

## Song List and Insertion Order: 

- Karn Evil 9, Emerson, Lake & Palmer, 1973
- Close to the Edge, Yes, 1972
- Aqualung, Jethro Tull, 1971
- Firth of Fifth, Genesis, 1973
- Shine On You Crazy Diamond, Pink Floyd, 1975
- Roundabout, Yes, 1971
- Supper's Ready, Genesis, 1972
- Tme, Pink Floyd, 1973

## Tree Structure After Insertions:

The BST produced by the chosen insertion order is:
```

            Karn Evil 9
           /            \
     Firth of Fifth   Shine On You Crazy Diamond
        /              /                    \
Close to the Edge  Roundabout         Supper's Ready
      /                                         \
Aqualung                                         Time
```
This structure was chosen to create a balanced tree. 

## Program Features

The Music Library supports the following operations:

- Add songs to the library
- Remove songs (leaf, one-child, two-children cases)
- Search for songs using `contains()`
- Retrieve songs using `getEntry()`
- Traverse the library:
  - preorder
  - inorder
  - postorder
- Check tree properties:
  - `getHeight()`
  - `getNumberOfNodes()`
  - `isBalanced()`
  - `isEmpty()`

---

## Notable Design Decisions

### 1. Ordering by Title
Songs are ordered by title using overloaded comparison operators.  
This ensures that inorder traversal produces alphabetical output.

---

### 2. Controlled Insertion Order
Because the BST is not self-balancing, insertion order was selected to create a balanced tree.  
This improves performance by keeping tree height close to **O(log n)**.

---

### 3. Template-Based BST
The BST is implemented as a **templated class**, allowing it to store any comparable data type.  
All template code is implemented in the header file to satisfy C++ compilation requirements.

---

### 4. Separation of Concerns (as mentioned in lecture)
- `Song` handles data representation  
- `BST<T>` handles tree structure and algorithms  
- `MusicLibrary` provides a user-facing interface  

This separation improves readability, modularity, and maintainability.

---

### 5. Recursive Helper Functions
Traversal and removal operations use **private recursive helper functions**, keeping recursion hidden from the public interface and maintaining abstraction.

---

### 6. Robust Error Handling
- `getEntry()` throws `NotFoundException` when a song is not found  
- `contains()` and `remove()` safely handle missing values without modifying the tree  

---

## Summary

This project demonstrates how a Binary Search Tree can be used to manage an ordered collection efficiently.  
By combining careful insertion order with BST properties, the program maintains both correctness and performance.

## Expected Output
```text

========================================
  1. Empty Library Check
========================================
isEmpty():          true
getNumberOfNodes(): 0
getHeight():        0

========================================
  2. Adding Songs (at least 8)
========================================
Songs added.
getNumberOfNodes(): 8

========================================
  3. Inorder Traversal (alphabetical by title)
========================================
  "Aqualung" by Jethro Tull (1971)
  "Close to the Edge" by Yes (1972)
  "Firth of Fifth" by Genesis (1973)
  "Karn Evil 9" by Emerson, Lake & Palmer (1973)
  "Roundabout" by Yes (1971)
  "Shine On You Crazy Diamond" by Pink Floyd (1975)
  "Supper's Ready" by Genesis (1972)
  "Time" by Pink Floyd (1973)

========================================
  4. Preorder Traversal (Root → Left → Right)
========================================
  "Karn Evil 9" by Emerson, Lake & Palmer (1973)
  "Close to the Edge" by Yes (1972)
  "Aqualung" by Jethro Tull (1971)
  "Firth of Fifth" by Genesis (1973)
  "Shine On You Crazy Diamond" by Pink Floyd (1975)
  "Roundabout" by Yes (1971)
  "Supper's Ready" by Genesis (1972)
  "Time" by Pink Floyd (1973)

========================================
  5. Postorder Traversal (Left → Right → Root)
========================================
  "Aqualung" by Jethro Tull (1971)
  "Firth of Fifth" by Genesis (1973)
  "Close to the Edge" by Yes (1972)
  "Roundabout" by Yes (1971)
  "Time" by Pink Floyd (1973)
  "Supper's Ready" by Genesis (1972)
  "Shine On You Crazy Diamond" by Pink Floyd (1975)
  "Karn Evil 9" by Emerson, Lake & Palmer (1973)

========================================
  6. Balance Check
========================================
getNumberOfNodes(): 8
getHeight():        4
isBalanced():       true

For a balanced tree of n nodes, expected height = floor(log2(n)) + 1

========================================
  7. Search — Song That Exists
========================================
Searching for "Roundabout"...
contains(): true

========================================
  8. Search — Song That Does Not Exist
========================================
Searching for "Brown Sugar"...
contains(): false

========================================
  9. getEntry() — Song That Exists
========================================
getEntry() found: "Roundabout" by Yes (1971)

========================================
  10. getEntry() — Song That Does Not Exist
========================================
NotFoundException caught (expected): Target not found: Entry not found

========================================
  11. Remove — Leaf Node
========================================
Removing "Time" (leaf)...
remove() returned: true
contains() after:  false
getNumberOfNodes(): 7

Inorder after removal:
  "Aqualung" by Jethro Tull (1971)
  "Close to the Edge" by Yes (1972)
  "Firth of Fifth" by Genesis (1973)
  "Karn Evil 9" by Emerson, Lake & Palmer (1973)
  "Roundabout" by Yes (1971)
  "Shine On You Crazy Diamond" by Pink Floyd (1975)
  "Supper's Ready" by Genesis (1972)

========================================
  12. Remove — Node With One Child
========================================
Removing "Supper's Ready" (one child)...
remove() returned: true
contains() after:  false
getNumberOfNodes(): 6

Inorder after removal:
  "Aqualung" by Jethro Tull (1971)
  "Close to the Edge" by Yes (1972)
  "Firth of Fifth" by Genesis (1973)
  "Karn Evil 9" by Emerson, Lake & Palmer (1973)
  "Roundabout" by Yes (1971)
  "Shine On You Crazy Diamond" by Pink Floyd (1975)

========================================
  13. Remove — Node With Two Children
========================================
Removing "Close to the Edge" (two children)...
remove() returned: true
contains() after:  false
getNumberOfNodes(): 5

Inorder after removal:
  "Aqualung" by Jethro Tull (1971)
  "Firth of Fifth" by Genesis (1973)
  "Karn Evil 9" by Emerson, Lake & Palmer (1973)
  "Roundabout" by Yes (1971)
  "Shine On You Crazy Diamond" by Pink Floyd (1975)

========================================
  14. Remove — Non-Existent Song (safe handling)
========================================
Removing "Brown Sugar" (not in library)...
remove() returned: false
getNumberOfNodes(): 5

========================================
  15. Final State
========================================
getNumberOfNodes(): 5
getHeight():        3
isEmpty():          false

Final inorder traversal:
  "Aqualung" by Jethro Tull (1971)
  "Firth of Fifth" by Genesis (1973)
  "Karn Evil 9" by Emerson, Lake & Palmer (1973)
  "Roundabout" by Yes (1971)
  "Shine On You Crazy Diamond" by Pink Floyd (1975)

========================================
  All checklist items demonstrated.
========================================
```

## Valgrind output: 
```text
=======================================
  All checklist items demonstrated.
========================================
==618122==
==618122== HEAP SUMMARY:
==618122==     in use at exit: 0 bytes in 0 blocks
==618122==   total heap usage: 39 allocs, 39 frees, 76,585 bytes allocated
==618122==
==618122== All heap blocks were freed -- no leaks are possible
==618122==
==618122== For lists of detected and suppressed errors, rerun with: -s
==618122== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Notes on Valgrind: 
- Valgrind is enabled with some minor changes to the make file, e.g. compiler flags. 
- After make, make run to get Valgrind output type **make valgrind**