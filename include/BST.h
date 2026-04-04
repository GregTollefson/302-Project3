/**
 * @file BST.h
 * @author Greg Tollefson
 * @date 04-April 2026
 * @brief Binary Search Tree (BST) implementation (templated).
 *
 * This class implements a generic Binary Search Tree that stores elements
 * of type ItemType and maintains the BST ordering property:
 *
 *      For any node N:
 *          all elements in the left subtree  < N
 *          all elements in the right subtree > N
 *
 * The BST supports standard operations including insertion, removal,
 * search, traversal, and structural queries (height, node count, balance).
 *
 * ------------------------------------------------------------
 * DESIGN OVERVIEW
 * ------------------------------------------------------------
 * - The BST is implemented as a linked structure using dynamically
 *   allocated nodes.
 *
 * - A private nested Node structure is used to represent tree nodes.
 *   This structure is not exposed outside the BST, ensuring proper
 *   encapsulation of the tree’s internal representation.
 *
 * - Memory management is handled internally by the BST (via clear()
 *   and destructor), preventing memory leaks.
 *
 * ------------------------------------------------------------
 * TRAVERSALS AND VISIT FUNCTION
 * ------------------------------------------------------------
 * - Traversal functions (preorder, inorder, postorder) are implemented
 *   using a two-level design:
 *
 *      1. Public wrapper (e.g., inorderTraverse)
 *         - Called by client code
 *         - Starts traversal at the root
 *
 *      2. Private recursive helper (e.g., inorder)
 *         - Performs the actual traversal using Node pointers
 *
 * - Traversals accept a function parameter:
 *
 *          void visit(ItemType&)
 *
 *   This function is provided by the caller and is applied to each
 *   node’s data during traversal.
 *
 * - This design keeps the BST generic and reusable, allowing client
 *   code to define custom behavior (e.g., printing, modifying data)
 *   without changing the BST implementation.
 *
 * ------------------------------------------------------------
 * REMOVAL STRATEGY
 * ------------------------------------------------------------
 * - Node removal follows standard BST rules:
 *
 *      1. Leaf node:
 *         - Node is simply deleted.
 *
 *      2. Node with one child:
 *         - Node is replaced by its child.
 *
 *      3. Node with two children:
 *         - Node is replaced by its inorder successor
 *           (smallest value in the right subtree).
 *
 * ------------------------------------------------------------
 * COMPLEXITY (AVERAGE CASE)
 * ------------------------------------------------------------
 * - Insert, Remove, Search:   O(log n)
 * - Traversals:               O(n)
 *
 * Worst case (unbalanced tree):
 * - Insert, Remove, Search:   O(n)
 *
 * ------------------------------------------------------------
 * NOTES
 * ------------------------------------------------------------
 * - The BST does not enforce self-balancing.
 * - Tree shape depends on insertion order.
 * - A balanced tree yields optimal performance.
 *
 */

#ifndef BST_H
#define BST_H

#include "NotFoundException.h"
#include <algorithm> // std::max used for height calculation
#include <cmath>     // std::abs used for balance checking

template <class ItemType>
class BST
{
private:
    // Node structure representing each element in the tree
    struct Node
    {
        ItemType data_;  // value stored in node
        Node* left_;     // pointer to left child
        Node* right_;    // pointer to right child

        // Constructor initializes node with data and null children
        Node(const ItemType& item)
            : data_(item), left_(nullptr), right_(nullptr) {}
    };

    Node* root_ptr_;   // pointer to root of the tree
    int item_count_;   // total number of nodes in the tree

    // ----------- Helper Functions (Recursive Core Logic) -----------

    // Inserts node in correct BST position and returns updated subtree root
    Node* insertInorder(Node* subTreePtr, Node* newNodePtr);

    // Recursively searches for target and removes it if found
    Node* removeValue(Node* subTreePtr, const ItemType& target, bool& success);

    // Removes a specific node and restructures tree (3 cases handled)
    Node* removeNode(Node* nodePtr);

    // Finds and removes leftmost node (inorder successor)
    Node* removeLeftmostNode(Node* subTreePtr, ItemType& inorderSuccessor);

    // Searches for a node containing target
    Node* findNode(Node* treePtr, const ItemType& target) const;

    // Returns height of subtree
    int getHeightHelper(Node* subTreePtr) const;

    // Deletes all nodes in subtree (postorder deletion)
    void clearHelper(Node* subTreePtr);

    // Checks if subtree is balanced
    bool isBalancedHelper(Node* subTreePtr) const;

    // Privage Traversal helpers
    void preorder(void visit(ItemType&), Node* treePtr) const;
    void inorder(void visit(ItemType&), Node* treePtr) const;
    void postorder(void visit(ItemType&), Node* treePtr) const;

public:
    BST();
    ~BST();

    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;

    bool insert(const ItemType& newEntry);
    bool remove(const ItemType& target);
    bool contains(const ItemType& target) const;
    ItemType getEntry(const ItemType& target) const;
    void clear();

    //Public wrappers for recursive traversals
    void preorderTraverse(void visit(ItemType&)) const;
    void inorderTraverse(void visit(ItemType&)) const;
    void postorderTraverse(void visit(ItemType&)) const;

    bool isBalanced() const;
};

//---------------------------------------------------
// Implementations
//---------------------------------------------------

// Constructor initializes empty tree
template <class ItemType>
BST<ItemType>::BST() : root_ptr_(nullptr), item_count_(0) {}

// Destructor ensures all dynamically allocated nodes are freed
template <class ItemType>
BST<ItemType>::~BST()
{
    clear(); // prevents memory leaks
}

// Returns true if tree has no nodes
template <class ItemType>
bool BST<ItemType>::isEmpty() const
{
    return item_count_ == 0;
}

// Public wrapper for recursive height calculation
template <class ItemType>
int BST<ItemType>::getHeight() const
{
    return getHeightHelper(root_ptr_);
}

// Returns total number of nodes tracked by itemCount
template <class ItemType>
int BST<ItemType>::getNumberOfNodes() const
{
    return item_count_;
}

// Inserts new value into BST
template <class ItemType>
bool BST<ItemType>::insert(const ItemType& newEntry)
{
    Node* newNodePtr = new Node(newEntry);           // allocate new node
    root_ptr_ = insertInorder(root_ptr_, newNodePtr); // update root if needed
    ++item_count_;                                  // maintain count invariant
    return true;
}

// Recursive insertion maintaining BST ordering property
template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::insertInorder(Node* subTreePtr, Node* newNodePtr)
{
    // Base case: found insertion point
    if (subTreePtr == nullptr)
        return newNodePtr;

    // Recurse left or right depending on ordering
    if (newNodePtr->data_ < subTreePtr->data_)
        subTreePtr->left_ = insertInorder(subTreePtr->left_, newNodePtr);
    else
        subTreePtr->right_ = insertInorder(subTreePtr->right_, newNodePtr);

    return subTreePtr; // return unchanged root of subtree
}

// Returns true if target exists in tree
template <class ItemType>
bool BST<ItemType>::contains(const ItemType& target) const
{
    return findNode(root_ptr_, target) != nullptr;
}

// Recursive search following BST ordering
template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::findNode(Node* treePtr, const ItemType& target) const
{
    if (!treePtr) // base case: not found
        return nullptr;

    if (target == treePtr->data_) // found
        return treePtr;

    // recurse left or right depending on comparison
    if (target < treePtr->data_)
        return findNode(treePtr->left_, target);

    return findNode(treePtr->right_, target);
}

// Retrieves value or throws exception if not found
template <class ItemType>
ItemType BST<ItemType>::getEntry(const ItemType& target) const
{
    Node* result = findNode(root_ptr_, target);

    if (!result)
        throw NotFoundException("Entry not found");

    return result->data_;
}

// Clears entire tree
template <class ItemType>
void BST<ItemType>::clear()
{
    clearHelper(root_ptr_); // delete all nodes
    root_ptr_ = nullptr;    // reset root
    item_count_ = 0;        // reset count
}

// Postorder deletion ensures children are deleted before parent
template <class ItemType>
void BST<ItemType>::clearHelper(Node* subTreePtr)
{
    if (subTreePtr)
    {
        clearHelper(subTreePtr->left_);
        clearHelper(subTreePtr->right_);
        delete subTreePtr; // safe after children removed
    }
}

// Computes height recursively
template <class ItemType>
int BST<ItemType>::getHeightHelper(Node* subTreePtr) const
{
    if (!subTreePtr)
        return 0;

    // height = 1 + max(left height, right height)
    return 1 + std::max(
        getHeightHelper(subTreePtr->left_),
        getHeightHelper(subTreePtr->right_)
    );
}

//----------------------------------------------------
// Traversals
//----------------------------------------------------

// Public wrappers call recursive helpers
template <class ItemType>
void BST<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
    preorder(visit, root_ptr_);
}

template <class ItemType>
void BST<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
    inorder(visit, root_ptr_);
}

template <class ItemType>
void BST<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
    postorder(visit, root_ptr_);
}

// Private recursive helpers

// Root → Left → Right
template <class ItemType>
void BST<ItemType>::preorder(void visit(ItemType&), Node* treePtr) const
{
    if (treePtr)
    {
        visit(treePtr->data_);
        preorder(visit, treePtr->left_);
        preorder(visit, treePtr->right_);
    }
}

// Left → Root → Right (sorted order for BST)
template <class ItemType>
void BST<ItemType>::inorder(void visit(ItemType&), Node* treePtr) const
{
    if (treePtr)
    {
        inorder(visit, treePtr->left_);
        visit(treePtr->data_);
        inorder(visit, treePtr->right_);
    }
}

// Left → Right → Root
template <class ItemType>
void BST<ItemType>::postorder(void visit(ItemType&), Node* treePtr) const
{
    if (treePtr)
    {
        postorder(visit, treePtr->left_);
        postorder(visit, treePtr->right_);
        visit(treePtr->data_);
    }
}

//---------------------------------------------------
// Remove
//---------------------------------------------------

// Public remove interface
template <class ItemType>
bool BST<ItemType>::remove(const ItemType& target)
{
    bool success = false;
    root_ptr_ = removeValue(root_ptr_, target, success);

    if (success)
        --item_count_; // maintain count consistency

    return success;
}

// Recursive search + removal
template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::removeValue(
    Node* subTreePtr, const ItemType& target, bool& success)
{
    if (!subTreePtr)
    {
        success = false; // not found
        return nullptr;
    }

    if (target == subTreePtr->data_)
    {
        success = true;
        return removeNode(subTreePtr); // remove this node
    }

    // recurse to correct subtree
    if (target < subTreePtr->data_)
        subTreePtr->left_ = removeValue(subTreePtr->left_, target, success);
    else
        subTreePtr->right_ = removeValue(subTreePtr->right_, target, success);

    return subTreePtr;
}

// Handles the 3 deletion cases
template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::removeNode(Node* nodePtr)
{
    // Case 1: leaf node
    if (!nodePtr->left_ && !nodePtr->right_)
    {
        delete nodePtr;
        return nullptr;
    }

    // Case 2: one child (right only)
    if (!nodePtr->left_)
    {
        Node* temp = nodePtr->right_;
        delete nodePtr;
        return temp;
    }

    // Case 2: one child (left only)
    if (!nodePtr->right_)
    {
        Node* temp = nodePtr->left_;
        delete nodePtr;
        return temp;
    }

    // Case 3: two children
    // Replace node with inorder successor
    ItemType successor;
    nodePtr->right_ = removeLeftmostNode(nodePtr->right_, successor);
    nodePtr->data_ = successor;

    return nodePtr;
}

// Finds and removes leftmost node (smallest value)
template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::removeLeftmostNode(
    Node* subTreePtr, ItemType& inorderSuccessor)
{
    if (!subTreePtr->left_)
    {
        inorderSuccessor = subTreePtr->data_;
        Node* temp = subTreePtr->right_;
        delete subTreePtr;
        return temp;
    }

    subTreePtr->left_ = removeLeftmostNode(subTreePtr->left_, inorderSuccessor);
    return subTreePtr;
}

//---------------------------------------------------
// Balance Check
//---------------------------------------------------

// Public interface
template <class ItemType>
bool BST<ItemType>::isBalanced() const
{
    return isBalancedHelper(root_ptr_);
}

// Checks height difference at every node
template <class ItemType>
bool BST<ItemType>::isBalancedHelper(Node* subTreePtr) const
{
    if (!subTreePtr)
        return true;

    int left = getHeightHelper(subTreePtr->left_);
    int right = getHeightHelper(subTreePtr->right_);

    // If difference > 1 → not balanced
    if (std::abs(left - right) > 1)
        return false;

    // Check recursively for all nodes
    return isBalancedHelper(subTreePtr->left_) &&
           isBalancedHelper(subTreePtr->right_);
}

#endif