// NotFoundException.h
// CS 302 – Project 3: Music Library (Binary Search Tree)
//
// Exception class thrown by getEntry() when a requested item
// is not found in the binary tree.
//
// Derived from Carrano & Henry, Data Abstraction & Problem
// Solving with C++, 8th ed., Chapter 15.
//
// DO NOT MODIFY THIS FILE.

#ifndef NOT_FOUND_EXCEPTION_H
#define NOT_FOUND_EXCEPTION_H

#include <stdexcept>
#include <string>

class NotFoundException : public std::logic_error
{
public:
    explicit NotFoundException(const std::string& message = "")
        : std::logic_error("Target not found: " + message)
    {
    }
};  // end NotFoundException

#endif
