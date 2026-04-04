#include "MusicLibrary.h"

// Default constructor
// Initializes an empty MusicLibrary.
// The underlying BST (libraryTree) is default-constructed automatically.
MusicLibrary::MusicLibrary() {}

// Destructor
// No explicit cleanup needed here because libraryTree's destructor
// handles all dynamic memory (via BST::clear()).
MusicLibrary::~MusicLibrary() {}

// Returns true if the library contains no songs
bool MusicLibrary::isEmpty() const
{
    return libraryTree.isEmpty(); // delegate to BST
}

// Returns the height of the underlying BST
// Height reflects the longest path from root to leaf
int MusicLibrary::getHeight() const
{
    return libraryTree.getHeight();
}

// Returns total number of songs stored in the library
int MusicLibrary::getNumberOfNodes() const
{
    return libraryTree.getNumberOfNodes();
}

// Adds a new song to the library
// Maintains BST ordering based on Song comparison operators
bool MusicLibrary::add(const Song& newData)
{
    return libraryTree.insert(newData);
}

// Removes a song from the library (if it exists)
// Uses BST removal logic (3 cases: leaf, one child, two children)
bool MusicLibrary::remove(const Song& data)
{
    return libraryTree.remove(data);
}

// Clears all songs from the library
// Frees all dynamically allocated nodes in the BST
void MusicLibrary::clear()
{
    libraryTree.clear();
}

// Retrieves a song matching the given key
// Throws NotFoundException if the song is not found
Song MusicLibrary::getEntry(const Song& anEntry) const
{
    return libraryTree.getEntry(anEntry);
}

// Returns true if the given song exists in the library
bool MusicLibrary::contains(const Song& anEntry) const
{
    return libraryTree.contains(anEntry);
}

// Preorder traversal: root → left → right
// Applies the provided visit function to each Song
void MusicLibrary::preorderTraverse(void visit(Song&)) const
{
    libraryTree.preorderTraverse(visit);
}

// Inorder traversal: left → root → right
// Produces songs in sorted order (by BST key)
void MusicLibrary::inorderTraverse(void visit(Song&)) const
{
    libraryTree.inorderTraverse(visit);
}

// Postorder traversal: left → right → root
// Useful for deletion or bottom-up processing
void MusicLibrary::postorderTraverse(void visit(Song&)) const
{
    libraryTree.postorderTraverse(visit);
}

// Returns true if the underlying BST is height-balanced
// Balance condition: height difference ≤ 1 at every node
bool MusicLibrary::isBalanced() const
{
    return libraryTree.isBalanced();
}