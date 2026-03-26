#ifndef BST_H
#define BST_H

#include "NotFoundException.h"
#include <algorithm>
#include <cmath>

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

/////////////////////////////////////////////////////
// IMPLEMENTATION
/////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////
// Traversals
/////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////
// Remove (CRITICAL FOR GRADING)
/////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////
// Balance
/////////////////////////////////////////////////////

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