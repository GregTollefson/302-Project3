// Comparable.h
// CS 302 – Project 3: Music Library (Binary Search Tree)
//
// Interface for objects that can be compared with each other.
// Any class that stores items in a BST must implement this interface
// so the tree can determine ordering and equality.
//
// Modeled on the Comparable contract common in typed ADT design.
// Your Song class must inherit from Comparable<Song>.
//
// DO NOT MODIFY THIS FILE.

#ifndef COMPARABLE_H
#define COMPARABLE_H

template <class T>
class Comparable
{
public:

    virtual ~Comparable() {}

    /** Returns true if this object is less than rhs.
        Used by BST to determine left/right placement.
        @param rhs  The object to compare against.
        @return True if this < rhs; false otherwise. */
    virtual bool operator<(const T& rhs) const = 0;

    /** Returns true if this object is equal to rhs.
        Used by BST for search and retrieval.
        @param rhs  The object to compare against.
        @return True if this == rhs; false otherwise. */
    virtual bool operator==(const T& rhs) const = 0;

};  // end Comparable

#endif
