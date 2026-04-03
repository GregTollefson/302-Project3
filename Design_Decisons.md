## Design Decisions

### 1. Ordering key
The Binary Search Tree (BST) is ordered by **song title**. This decision was made because:
- The assignment requires inorder traversal to produce songs in alphabetical order.
- Titles provide a natural and intuitive sorting key for a music library.
- Titles are sufficiently unique for this dataset and simplify comparisons.

Both `operator<` and `operator==` in the `Song` class compare only the title field to ensure consistent ordering behavior.

---

### 2. Insertion order & balance
Songs were inserted using a **median-first strategy** to approximate a balanced BST.

Instead of inserting songs in alphabetical order (which would produce a degenerate tree), the insertion order was carefully chosen to:
- Place a middle value first (root)
- Then insert values that divide the remaining elements into left and right subtrees

This approach results in a tree where the height difference between subtrees is minimized, allowing `isBalanced()` to return `true`.

---

### 3. Operator overloading
The following operators were overloaded in the `Song` class:

- `operator<`  
  Used by the BST to determine whether a node should be placed in the left or right subtree.

- `operator==`  
  Used for search operations such as `contains()` and `getEntry()`.

Both operators compare songs based solely on their **title**, ensuring consistent behavior across all BST operations.

---

### 4. Template implementation
The `BST<T>` class is implemented as a **header-only template**.

This design was chosen because:
- C++ templates must be fully visible at compile time
- Separating implementation into a `.cpp` file would cause linker errors
- A header-only approach simplifies compilation and avoids explicit instantiation issues

---

### 5. Remove strategy
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
All traversals use the **visit-function pattern**, where a client-provided function is applied to each node.

Each song is displayed using the format:


Traversal behavior:
- **Inorder** → Produces sorted output by title
- **Preorder** → Visits root before subtrees
- **Postorder** → Visits root after subtrees

This consistent formatting makes correctness easy to verify.

---

### 7. Edge cases

- **Empty tree**
  - `isEmpty()` returns true
  - `getHeight()` returns 0
  - Traversals produce no output

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