/**
 * @file BST.h
 * @author Greg Tollefson 
 * @date 3-Apr-2026
 *
 * @brief Templated Binary Search Tree (BST) implementation.
 *
 * This class implements a pointer-based Binary Search Tree (BST) that stores
 * elements of a generic type ItemType. The type ItemType must support
 * comparison via operator< and operator==.
 *
 * The BST maintains the ordering invariant:
 *   - All values in the left subtree of a node are less than the node's value
 *   - All values in the right subtree of a node are greater than the node's value
 *
 * This invariant ensures efficient search, insertion, and removal operations.
 *
 * ------------------------------------------------------------
 * DESIGN OVERVIEW
 * ------------------------------------------------------------
 *
 * - The BST is implemented as a class template: BST<ItemType>
 * - Each node is dynamically allocated and contains:
 *     - ItemType data
 *     - pointer to left child
 *     - pointer to right child
 *
 * - The tree is managed via a root pointer (rootPtr) and a node count (itemCount)
 *
 * - All major operations (insert, remove, search, traversal) are implemented
 *   recursively using private helper functions.
 *
 * ------------------------------------------------------------
 * MEMORY MANAGEMENT
 * ------------------------------------------------------------
 *
 * - Nodes are allocated using new and deallocated using delete
 * - The destructor calls clear() to free all nodes
 * - No memory leaks should occur if all operations are used correctly
 *
 * NOTE:
 * This class manages dynamic memory. The default copy constructor and
 * assignment operator perform shallow copies, which may lead to undefined
 * behavior (e.g., double deletion). Copying is currently not needed, deep 
 * copy is not implemented.    
 *
 * ------------------------------------------------------------
 * PUBLIC OPERATIONS
 * ------------------------------------------------------------
 *
 * - isEmpty()              : returns true if the tree contains no nodes
 * - getHeight()            : returns the height of the tree
 * - getNumberOfNodes()     : returns the total number of nodes
 * - insert()               : inserts a new item while maintaining BST order
 * - remove()               : removes an item using BST deletion rules
 * - contains()             : checks if an item exists in the tree
 * - getEntry()             : retrieves an item or throws NotFoundException
 * - clear()                : removes all nodes from the tree
 *
 * - preorderTraverse()     : root → left → right traversal
 * - inorderTraverse()      : left → root → right (sorted order)
 * - postorderTraverse()    : left → right → root
 *
 * - isBalanced()           : checks if the tree is height-balanced
 *
 * ------------------------------------------------------------
 * BST REMOVAL CASES
 * ------------------------------------------------------------
 *
 * The remove operation handles three cases:
 *
 * 1. Leaf node:
 *    - Node is deleted directly
 *
 * 2. Node with one child:
 *    - Node is replaced with its child
 *
 * 3. Node with two children:
 *    - Node is replaced with its inorder successor
 *    - Inorder successor is the leftmost node of the right subtree
 *
 * ------------------------------------------------------------
 * BALANCE DEFINITION
 * ------------------------------------------------------------
 *
 * A tree is considered balanced if, for every node, the height difference
 * between its left and right subtrees is no greater than 1.
 *
 * The isBalanced() method verifies this condition recursively.
 *
 * ------------------------------------------------------------
 * COMPLEXITY (AVERAGE CASE)
 * ------------------------------------------------------------
 *
 * Operation            Time Complexity
 * ------------------------------------
 * Insert               O(log n)
 * Remove               O(log n)
 * Search               O(log n)
 * Traversal            O(n)
 *
 * Worst-case complexity degrades to O(n) if the tree becomes unbalanced.
 *
 * ------------------------------------------------------------
 * USAGE NOTE
 * ------------------------------------------------------------
 *
 * This BST is used internally by the MusicLibrary class and is not intended
 * to be used directly by clients. It provides the underlying data structure
 * that supports efficient song storage and retrieval.
 */

#ifndef BST_H
#define BST_H

#include "NotFoundException.h"
#include <algorithm> // std:max is used for checking tree height 
#include <cmath> // std:abs used for checking height differences

template <class ItemType>
class BST
{
private:
    struct Node
    {
        ItemType data;
        Node* left;
        Node* right;

        Node(const ItemType& item)
            : data(item), left(nullptr), right(nullptr) {}
    };

    Node* rootPtr;
    int itemCount;

    // Helpers
    Node* insertInorder(Node* subTreePtr, Node* newNodePtr);
    Node* removeValue(Node* subTreePtr, const ItemType& target, bool& success);
    Node* removeNode(Node* nodePtr);
    Node* removeLeftmostNode(Node* subTreePtr, ItemType& inorderSuccessor);
    Node* findNode(Node* treePtr, const ItemType& target) const;

    int getHeightHelper(Node* subTreePtr) const;
    void clearHelper(Node* subTreePtr);
    bool isBalancedHelper(Node* subTreePtr) const;

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

    void preorderTraverse(void visit(ItemType&)) const;
    void inorderTraverse(void visit(ItemType&)) const;
    void postorderTraverse(void visit(ItemType&)) const;

    bool isBalanced() const;
};

//---------------------------------------------------
// Implementations
//---------------------------------------------------

template <class ItemType>
BST<ItemType>::BST() : rootPtr(nullptr), itemCount(0) {}

template <class ItemType>
BST<ItemType>::~BST()
{
    clear();
}

template <class ItemType>
bool BST<ItemType>::isEmpty() const
{
    return itemCount == 0;
}

template <class ItemType>
int BST<ItemType>::getHeight() const
{
    return getHeightHelper(rootPtr);
}

template <class ItemType>
int BST<ItemType>::getNumberOfNodes() const
{
    return itemCount;
}

template <class ItemType>
bool BST<ItemType>::insert(const ItemType& newEntry)
{
    Node* newNodePtr = new Node(newEntry);
    rootPtr = insertInorder(rootPtr, newNodePtr);
    ++itemCount;
    return true;
}

template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::insertInorder(Node* subTreePtr, Node* newNodePtr)
{
    if (subTreePtr == nullptr)
        return newNodePtr;

    if (newNodePtr->data < subTreePtr->data)
        subTreePtr->left = insertInorder(subTreePtr->left, newNodePtr);
    else
        subTreePtr->right = insertInorder(subTreePtr->right, newNodePtr);

    return subTreePtr;
}

template <class ItemType>
bool BST<ItemType>::contains(const ItemType& target) const
{
    return findNode(rootPtr, target) != nullptr;
}

template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::findNode(Node* treePtr, const ItemType& target) const
{
    if (!treePtr)
        return nullptr;

    if (target == treePtr->data)
        return treePtr;

    if (target < treePtr->data)
        return findNode(treePtr->left, target);

    return findNode(treePtr->right, target);
}

template <class ItemType>
ItemType BST<ItemType>::getEntry(const ItemType& target) const
{
    Node* result = findNode(rootPtr, target);

    if (!result)
        throw NotFoundException("Entry not found");

    return result->data;
}

template <class ItemType>
void BST<ItemType>::clear()
{
    clearHelper(rootPtr);
    rootPtr = nullptr;
    itemCount = 0;
}

template <class ItemType>
void BST<ItemType>::clearHelper(Node* subTreePtr)
{
    if (subTreePtr)
    {
        clearHelper(subTreePtr->left);
        clearHelper(subTreePtr->right);
        delete subTreePtr;
    }
}

template <class ItemType>
int BST<ItemType>::getHeightHelper(Node* subTreePtr) const
{
    if (!subTreePtr)
        return 0;

    return 1 + std::max(getHeightHelper(subTreePtr->left),
                        getHeightHelper(subTreePtr->right));
}

//----------------------------------------------------
//Traversals
//----------------------------------------------------

template <class ItemType>
void BST<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
    preorder(visit, rootPtr);
}

template <class ItemType>
void BST<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
    inorder(visit, rootPtr);
}

template <class ItemType>
void BST<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
    postorder(visit, rootPtr);
}

template <class ItemType>
void BST<ItemType>::preorder(void visit(ItemType&), Node* treePtr) const
{
    if (treePtr)
    {
        visit(treePtr->data);
        preorder(visit, treePtr->left);
        preorder(visit, treePtr->right);
    }
}

template <class ItemType>
void BST<ItemType>::inorder(void visit(ItemType&), Node* treePtr) const
{
    if (treePtr)
    {
        inorder(visit, treePtr->left);
        visit(treePtr->data);
        inorder(visit, treePtr->right);
    }
}

template <class ItemType>
void BST<ItemType>::postorder(void visit(ItemType&), Node* treePtr) const
{
    if (treePtr)
    {
        postorder(visit, treePtr->left);
        postorder(visit, treePtr->right);
        visit(treePtr->data);
    }
}

//---------------------------------------------------
// Remove 
//---------------------------------------------------

template <class ItemType>
bool BST<ItemType>::remove(const ItemType& target)
{
    bool success = false;
    rootPtr = removeValue(rootPtr, target, success);

    if (success)
        --itemCount;

    return success;
}

template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::removeValue(Node* subTreePtr,
                                                        const ItemType& target,
                                                        bool& success)
{
    if (!subTreePtr)
    {
        success = false;
        return nullptr;
    }

    if (target == subTreePtr->data)
    {
        success = true;
        return removeNode(subTreePtr);
    }

    if (target < subTreePtr->data)
        subTreePtr->left = removeValue(subTreePtr->left, target, success);
    else
        subTreePtr->right = removeValue(subTreePtr->right, target, success);

    return subTreePtr;
}

template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::removeNode(Node* nodePtr)
{
    // Case 1: leaf
    if (!nodePtr->left && !nodePtr->right)
    {
        delete nodePtr;
        return nullptr;
    }

    // Case 2: one child
    if (!nodePtr->left)
    {
        Node* temp = nodePtr->right;
        delete nodePtr;
        return temp;
    }

    if (!nodePtr->right)
    {
        Node* temp = nodePtr->left;
        delete nodePtr;
        return temp;
    }

    // Case 3: two children (inorder successor)
    ItemType successor;
    nodePtr->right = removeLeftmostNode(nodePtr->right, successor);
    nodePtr->data = successor;

    return nodePtr;
}

template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::removeLeftmostNode(Node* subTreePtr,
                                                               ItemType& inorderSuccessor)
{
    if (!subTreePtr->left)
    {
        inorderSuccessor = subTreePtr->data;
        Node* temp = subTreePtr->right;
        delete subTreePtr;
        return temp;
    }

    subTreePtr->left = removeLeftmostNode(subTreePtr->left, inorderSuccessor);
    return subTreePtr;
}

//---------------------------------------------------
// Balance Check 
//---------------------------------------------------

template <class ItemType>
bool BST<ItemType>::isBalanced() const
{
    return isBalancedHelper(rootPtr);
}

template <class ItemType>
bool BST<ItemType>::isBalancedHelper(Node* subTreePtr) const
{
    if (!subTreePtr)
        return true;

    int left = getHeightHelper(subTreePtr->left);
    int right = getHeightHelper(subTreePtr->right);

    if (std::abs(left - right) > 1)
        return false;

    return isBalancedHelper(subTreePtr->left) &&
           isBalancedHelper(subTreePtr->right);
}

#endif