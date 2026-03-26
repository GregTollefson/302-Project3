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