#include "MusicLibrary.h"

MusicLibrary::MusicLibrary() {}

MusicLibrary::~MusicLibrary() {}

bool MusicLibrary::isEmpty() const
{
    return libraryTree.isEmpty();
}

int MusicLibrary::getHeight() const
{
    return libraryTree.getHeight();
}

int MusicLibrary::getNumberOfNodes() const
{
    return libraryTree.getNumberOfNodes();
}

bool MusicLibrary::add(const Song& newData)
{
    return libraryTree.insert(newData);
}

bool MusicLibrary::remove(const Song& data)
{
    return libraryTree.remove(data);
}

void MusicLibrary::clear()
{
    libraryTree.clear();
}

Song MusicLibrary::getEntry(const Song& anEntry) const
{
    return libraryTree.getEntry(anEntry);
}

bool MusicLibrary::contains(const Song& anEntry) const
{
    return libraryTree.contains(anEntry);
}

void MusicLibrary::preorderTraverse(void visit(Song&)) const
{
    libraryTree.preorderTraverse(visit);
}

void MusicLibrary::inorderTraverse(void visit(Song&)) const
{
    libraryTree.inorderTraverse(visit);
}

void MusicLibrary::postorderTraverse(void visit(Song&)) const
{
    libraryTree.postorderTraverse(visit);
}

bool MusicLibrary::isBalanced() const
{
    return libraryTree.isBalanced();
}