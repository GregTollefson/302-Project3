/**
 * @file MusicLibrary.h
 * @author Greg Tollefson  
 * @date  03-Apr-2026
 *
 * @brief Public interface implementation for a Music Library using a Binary Search Tree.
 *
 * The MusicLibrary class represents a collection of Song objects organized
 * using a Binary Search Tree (BST). It provides the user-facing interface
 * for inserting, removing, searching, and traversing songs while maintaining
 * sorted order by title.
 *
 * This class implements the BinaryTreeInterface<Song> contract and delegates
 * all internal storage and tree operations to a BST<Song> instance.
 *
 * ------------------------------------------------------------
 * DESIGN OVERVIEW
 * ------------------------------------------------------------
 *
 * - MusicLibrary is the public-facing Abstract Data Type (ADT)
 * - It inherits from BinaryTreeInterface<Song>, ensuring all required
 *   operations are implemented
 * - It uses composition:
 *       MusicLibrary "has-a" BST<Song>
 *
 * - The underlying BST enforces ordering based on Song comparison
 *   (operator< and operator==), which are defined using song titles
 *
 * - Clients interact only with MusicLibrary; the BST implementation
 *   is hidden as an internal detail
 *
 * ------------------------------------------------------------
 * BEHAVIORAL GUARANTEES
 * ------------------------------------------------------------
 *
 * - Songs are stored in alphabetical order by title (BST invariant)
 *
 * - add():
 *     Inserts a song while preserving BST ordering
 *
 * - remove():
 *     Removes a song identified by title
 *     Returns false if the song is not found
 *
 * - contains():
 *     Returns true if a song with the given title exists
 *
 * - getEntry():
 *     Returns the matching Song if found
 *     Throws NotFoundException if not found
 *
 * - Traversals:
 *     preorder  → Root → Left → Right
 *     inorder   → Left → Root → Right (alphabetical order)
 *     postorder → Left → Right → Root
 *
 * - isBalanced():
 *     Returns true if the BST is height-balanced (subtree height
 *     difference ≤ 1 at every node)
 *
 * ------------------------------------------------------------
 * COMPLEXITY (AVERAGE CASE)
 * ------------------------------------------------------------
 *
 * Operation            Time Complexity
 * ------------------------------------
 * add                  O(log n)
 * remove               O(log n)
 * contains             O(log n)
 * getEntry             O(log n)
 * traversal            O(n)
 *
 * Worst-case complexity degrades to O(n) if the tree becomes unbalanced.
 *
 * ------------------------------------------------------------
 * USAGE NOTES
 * ------------------------------------------------------------
 *
 * - All operations are delegated to the internal BST<Song> instance
 * - The ordering of songs depends on Song::operator<
 * - The tree structure depends on insertion order; a carefully chosen
 *   insertion sequence is required to maintain balance
 *
 * - This class does not expose tree structure directly; interaction
 *   occurs through defined ADT operations only
 */

#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include "BinaryTreeInterface.h"
#include "BST.h"
#include "Song.h"

class MusicLibrary : public BinaryTreeInterface<Song>
{
private:
    BST<Song> libraryTree;

public:
    MusicLibrary();
    ~MusicLibrary();

    // State queries
    bool isEmpty() const override;
    int getHeight() const override;
    int getNumberOfNodes() const override;

    // Mutators
    bool add(const Song& newData) override;
    bool remove(const Song& data) override;
    void clear() override;

    // Search / retrieval
    Song getEntry(const Song& anEntry) const override;
    bool contains(const Song& anEntry) const override;

    // Traversals
    void preorderTraverse(void visit(Song&)) const override;
    void inorderTraverse(void visit(Song&)) const override;
    void postorderTraverse(void visit(Song&)) const override;

    // Balance
    bool isBalanced() const override;
};

#endif