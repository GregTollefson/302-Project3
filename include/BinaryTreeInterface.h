// BinaryTreeInterface.h
// CS 302 – Project 3: Music Library (Binary Search Tree)
//
// Pure abstract interface for the ADT binary tree.
// Derived directly from Carrano & Henry, Data Abstraction & Problem
// Solving with C++, 8th ed., Chapter 15, Listing 15-1.
//
// Method names, signatures, and contracts match the textbook exactly.
// isBalanced() is a P3-specific addition not in the original listing.
//
// Your MusicLibrary class must inherit from BinaryTreeInterface<Song>
// and implement every method below.
//
// DO NOT MODIFY THIS FILE.

#ifndef BINARY_TREE_INTERFACE_H
#define BINARY_TREE_INTERFACE_H

#include "NotFoundException.h"

template <class ItemType>
class BinaryTreeInterface
{
public:

    virtual ~BinaryTreeInterface() {}

    // -----------------------------------------------------------
    // State queries
    // -----------------------------------------------------------

    /** Tests whether this binary tree is empty.
        @return True if the binary tree is empty; false otherwise. */
    virtual bool isEmpty() const = 0;

    /** Gets the height of this binary tree.
        @return The height of the binary tree; 0 if empty. */
    virtual int getHeight() const = 0;

    /** Gets the number of nodes in this binary tree.
        @return The number of nodes in the binary tree. */
    virtual int getNumberOfNodes() const = 0;

    // -----------------------------------------------------------
    // Mutators
    // -----------------------------------------------------------

    /** Adds a new node containing the given data to this binary tree.
        @param newData  The data item to add.
        @return True if the addition is successful; false otherwise. */
    virtual bool add(const ItemType& newData) = 0;

    /** Removes the node containing the given data from this binary tree.
        @param data  The data item to remove.
        @return True if the removal is successful; false otherwise. */
    virtual bool remove(const ItemType& data) = 0;

    /** Removes all nodes from this binary tree.
        @post The binary tree is empty. */
    virtual void clear() = 0;

    // -----------------------------------------------------------
    // Search and retrieval
    // -----------------------------------------------------------

    /** Gets a specific entry in this binary tree.
        @param anEntry  The desired data item.
        @return The entry in the binary tree that matches anEntry.
        @throw NotFoundException if the entry is not found. */
    virtual ItemType getEntry(const ItemType& anEntry) const = 0;

    /** Tests whether the given data item occurs in this binary tree.
        @param anEntry  The data item to search for.
        @return True if found; false otherwise. */
    virtual bool contains(const ItemType& anEntry) const = 0;

    // -----------------------------------------------------------
    // Traversals — visit-function pattern (textbook Ch. 15)
    //
    // Each traversal accepts a client-defined function that is
    // called once per node in the specified order.
    //
    // Example:
    //   void displaySong(Song& s) { cout << s << endl; }
    //   library.inorderTraverse(displaySong);
    // -----------------------------------------------------------

    /** Traverses this binary tree in preorder (Root → Left → Right),
        calling visit() once for each node.
        @param visit  Client-defined function called at each node. */
    virtual void preorderTraverse(void visit(ItemType&)) const = 0;

    /** Traverses this binary tree in inorder (Left → Root → Right),
        calling visit() once for each node.
        On a valid BST, visits nodes in sorted order.
        @param visit  Client-defined function called at each node. */
    virtual void inorderTraverse(void visit(ItemType&)) const = 0;

    /** Traverses this binary tree in postorder (Left → Right → Root),
        calling visit() once for each node.
        @param visit  Client-defined function called at each node. */
    virtual void postorderTraverse(void visit(ItemType&)) const = 0;

    // -----------------------------------------------------------
    // Balance — P3 addition (not in textbook Listing 15-1)
    // -----------------------------------------------------------

    /** Tests whether this binary tree is height-balanced.
        A tree is balanced if, for every node, the heights of its
        left and right subtrees differ by no more than 1.
        @return True if balanced; false otherwise. */
    virtual bool isBalanced() const = 0;

};  // end BinaryTreeInterface

#endif
