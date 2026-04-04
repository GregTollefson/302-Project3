/**
 * @file BST.h
 * @author Greg Tollefson 
 * @date 3-Apr-2026
 *
 * @brief Templated Binary Search Tree (BST) implementation.
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
        ItemType data;   // value stored in node
        Node* left;      // pointer to left child 
        Node* right;     // pointer to right child 

        // Constructor initializes node with data and null children
        Node(const ItemType& item)
            : data(item), left(nullptr), right(nullptr) {}
    };

    Node* rootPtr;   // pointer to root of the tree
    int itemCount;   // total number of nodes in the tree

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

    // Traversal helpers
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

// Constructor initializes empty tree
template <class ItemType>
BST<ItemType>::BST() : rootPtr(nullptr), itemCount(0) {}

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
    return itemCount == 0;
}

// Public wrapper for recursive height calculation
template <class ItemType>
int BST<ItemType>::getHeight() const
{
    return getHeightHelper(rootPtr);
}

// Returns total number of nodes tracked by itemCount
template <class ItemType>
int BST<ItemType>::getNumberOfNodes() const
{
    return itemCount;
}

// Inserts new value into BST
template <class ItemType>
bool BST<ItemType>::insert(const ItemType& newEntry)
{
    Node* newNodePtr = new Node(newEntry);  // allocate new node
    rootPtr = insertInorder(rootPtr, newNodePtr); // update root if needed
    ++itemCount; // maintain count invariant
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
    if (newNodePtr->data < subTreePtr->data)
        subTreePtr->left = insertInorder(subTreePtr->left, newNodePtr);
    else
        subTreePtr->right = insertInorder(subTreePtr->right, newNodePtr);

    return subTreePtr; // return unchanged root of subtree
}

// Returns true if target exists in tree
template <class ItemType>
bool BST<ItemType>::contains(const ItemType& target) const
{
    return findNode(rootPtr, target) != nullptr;
}

// Recursive search following BST ordering
template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::findNode(Node* treePtr, const ItemType& target) const
{
    if (!treePtr) // base case: not found
        return nullptr;

    if (target == treePtr->data) // found
        return treePtr;

    // recurse left or right depending on comparison
    if (target < treePtr->data)
        return findNode(treePtr->left, target);

    return findNode(treePtr->right, target);
}

// Retrieves value or throws exception if not found
template <class ItemType>
ItemType BST<ItemType>::getEntry(const ItemType& target) const
{
    Node* result = findNode(rootPtr, target);

    if (!result)
        throw NotFoundException("Entry not found");

    return result->data;
}

// Clears entire tree
template <class ItemType>
void BST<ItemType>::clear()
{
    clearHelper(rootPtr); // delete all nodes
    rootPtr = nullptr;    // reset root
    itemCount = 0;        // reset count
}

// Postorder deletion ensures children are deleted before parent
template <class ItemType>
void BST<ItemType>::clearHelper(Node* subTreePtr)
{
    if (subTreePtr)
    {
        clearHelper(subTreePtr->left);
        clearHelper(subTreePtr->right);
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
        getHeightHelper(subTreePtr->left),
        getHeightHelper(subTreePtr->right)
    );
}

//----------------------------------------------------
// Traversals
//----------------------------------------------------

// Public wrappers call recursive helpers
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

// Root → Left → Right
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

// Left → Root → Right (sorted order for BST)
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

// Left → Right → Root
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

// Public remove interface
template <class ItemType>
bool BST<ItemType>::remove(const ItemType& target)
{
    bool success = false;
    rootPtr = removeValue(rootPtr, target, success);

    if (success)
        --itemCount; // maintain count consistency

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

    if (target == subTreePtr->data)
    {
        success = true;
        return removeNode(subTreePtr); // remove this node
    }

    // recurse to correct subtree
    if (target < subTreePtr->data)
        subTreePtr->left = removeValue(subTreePtr->left, target, success);
    else
        subTreePtr->right = removeValue(subTreePtr->right, target, success);

    return subTreePtr;
}

// Handles the 3 deletion cases
template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::removeNode(Node* nodePtr)
{
    // Case 1: leaf node
    if (!nodePtr->left && !nodePtr->right)
    {
        delete nodePtr;
        return nullptr;
    }

    // Case 2: one child (right only)
    if (!nodePtr->left)
    {
        Node* temp = nodePtr->right;
        delete nodePtr;
        return temp;
    }

    // Case 2: one child (left only)
    if (!nodePtr->right)
    {
        Node* temp = nodePtr->left;
        delete nodePtr;
        return temp;
    }

    // Case 3: two children
    // Replace node with inorder successor
    ItemType successor;
    nodePtr->right = removeLeftmostNode(nodePtr->right, successor);
    nodePtr->data = successor;

    return nodePtr;
}

// Finds and removes leftmost node (smallest value)
template <class ItemType>
typename BST<ItemType>::Node* BST<ItemType>::removeLeftmostNode(
    Node* subTreePtr, ItemType& inorderSuccessor)
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

// Public interface
template <class ItemType>
bool BST<ItemType>::isBalanced() const
{
    return isBalancedHelper(rootPtr);
}

// Checks height difference at every node
template <class ItemType>
bool BST<ItemType>::isBalancedHelper(Node* subTreePtr) const
{
    if (!subTreePtr)
        return true;

    int left = getHeightHelper(subTreePtr->left);
    int right = getHeightHelper(subTreePtr->right);

    // If difference > 1 → not balanced
    if (std::abs(left - right) > 1)
        return false;

    // Check recursively for all nodes
    return isBalancedHelper(subTreePtr->left) &&
           isBalancedHelper(subTreePtr->right);
}

#endif