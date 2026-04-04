## Design Decisions

### 1. Ordering key:
The Binary Search Tree (BST) is ordered by **song title**:
- The assignment requires inorder BST traversal to list songs in alphabetical order.
- Titles provide the best sorting key for a music library (Artist search could be added as an option later)
- Titles provide a unique key for simple sorting comparisons.

Both `operator<` and `operator==` in the `Song` class compare the title field for sorting.

---

### 2. Insertion order & balance:
A balanced tree has the best search, add, and remove performance, closer to O(logN) vs an unbalanced tree. 
For this project, songs were inserted using  **middle element first** to approximate a balanced BST.
Specifically: 
- Place a middle value first (root)
- Then insert values that divide the remaining elements into left and right subtrees

This approach results in a tree where the height difference between subtrees is minimized, so that `isBalanced()` returns `true`.

---

### 3. Operator overloading:
The following operators were overloaded in the `Song` class:

- `operator<`  
  Used by the BST to determine whether a node should be placed in the left or right subtree.

- `operator==`  
  Used for search operations such as `contains()` and `getEntry()`.

Both operators compare songs based solely on their **title**, ensuring consistent behavior across all BST operations (add, remove, etc.).

---

### 4. Template implementation:
The `BST<T>` class is implemented as a **header-only template**.

This design was chosen because:
- Templated BST is a rubrik requirement
- C++ templates must be fully visible at compile time
- For a template class, separating implementation into a `.cpp` file would cause compiler erros 
- A header-only approach simplifies compilation and avoids explicit instantiation issues

---

### 5. Remove Strategy:
The `remove()` operation handles three cases:

1. **Leaf node**  
   The node is deleted directly.

2. **Node with one child**  
   The node is replaced by its single child.

3. **Node with two children**  
   The node’s value is replaced with its **inorder successor** (the leftmost node in the right subtree), and that successor node is then removed recursively.

This approach preserves the BST ordering property.

---

### 6. Traversal output format
All traversals use the **Visit-Function Rattern**, where a client-provided function is applied to each node.

Each song is displayed using the format:


Traversal behavior:
- **Inorder** → Produces sorted output by title
- **Preorder** → Visits root before subtrees
- **Postorder** → Visits root after subtrees
- Traversal relies on a **protected recursive helper**, per requirements, implemented in BST.h

---

### 7. Edge cases

- **Empty tree**
  - `isEmpty()` returns true
  - `getHeight()` returns 0
  - Traversals of an empty tree produce no output

- **Duplicates**
  - Duplicate titles are not explicitly prevented
  - If duplicates occur, they are inserted into the right subtree
  - The test dataset avoids duplicates

- **Missing keys**
  - `contains()` returns false
  - `getEntry()` throws `NotFoundException`
  - `remove()` safely returns false without modifying the tree

---

## Correctness Checklist (Required)

- [x] Add at least 8 songs and display the library using all three traversals
- [x] Verify that inorder traversal produces songs in alphabetical order by title
- [x] Search for a song that **exists** using `contains()` — confirm it is found
- [x] Search for a song that **does not exist** using `contains()` — confirm it is not found
- [x] Call `getEntry()` on a title that exists — confirm correct song returned
- [x] Call `getEntry()` on a title that does not exist — confirm `NotFoundException` caught
- [x] Remove a **leaf node** — confirm the song is gone
- [x] Remove a node with **one child** — confirm structure is correct
- [x] Remove a node with **two children** — confirm structure is correct
- [x] Call `remove()` on a title that does not exist — confirm safe handling
- [x] Verify `getNumberOfNodes()` updates correctly after insertions and removals
- [x] Call `isBalanced()` — confirm `true`; print `getHeight()` and `getNumberOfNodes()`
- [x] Verify `isEmpty()` returns true on an empty library





## Tree Structure After Insertions

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