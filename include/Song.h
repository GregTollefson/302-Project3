/**
 * @file Song.h
 * @author Greg Tollefson
 * @date 3-Apr-2026
 *
 * @brief Represents a song entity used in the Music Library.
 *
 * This class models a song with three attributes:
 *   - title  (std::string)
 *   - artist (std::string)
 *   - year   (int)
 *
 * The Song class implements both the SongInterface and Comparable<Song>
 * interfaces, allowing it to:
 *   - Provide standardized accessors/mutators (SongInterface)
 *   - Be stored in ordered data structures such as a Binary Search Tree
 *     via comparison operators (Comparable)
 *
 * ------------------------------------------------------------
 * DESIGN OVERVIEW
 * ------------------------------------------------------------
 *
 * - Each Song object encapsulates basic metadata about a musical track.
 * - The class provides getters and setters for controlled access.
 * - A display() function outputs a formatted representation of the song.
 *
 * - Comparison operators are overloaded to support ordering and equality:
 *     - operator<  : defines ordering for BST insertion
 *     - operator== : defines equality for search and removal
 *
 * ------------------------------------------------------------
 * ORDERING AND UNIQUENESS
 * ------------------------------------------------------------
 *
 * Songs are ordered and identified **by title only**.
 *
 * This means:
 *   - operator< compares only the title field
 *   - operator== compares only the title field
 *
 * ASSUMPTION:
 *   Song titles are unique within the MusicLibrary.
 *
 * NOTE:
 *   If multiple songs share the same title (e.g., covers or remasters),
 *   this implementation will treat them as identical, which may lead to
 *   unintended behavior (duplicates not allowed or overwritten).
 *
 * ------------------------------------------------------------
 * USAGE IN MUSIC LIBRARY
 * ------------------------------------------------------------
 *
 * - Song objects are stored in a BST within the MusicLibrary class.
 * - The ordering defined here directly determines the tree structure.
 * - Efficient search, insertion, and removal depend on consistent
 *   comparison logic.
 *
 * ------------------------------------------------------------
 * COMPLEXITY NOTES
 * ------------------------------------------------------------
 *
 * - Getter/Setter operations: O(1)
 * - Comparison operations:    O(1) (string comparison depends on length)
 * - Display operation:       O(1)
 *
 */

#ifndef SONG_H
#define SONG_H

#include "SongInterface.h"
#include "Comparable.h"
#include <string>
#include <ostream>

class Song : public SongInterface, public Comparable<Song>
{
private:
    std::string title;
    std::string artist;
    int year;

public:
    Song();
    Song(const std::string& title, const std::string& artist, int year);

    std::string getTitle() const override;
    std::string getArtist() const override;
    int getYear() const override;

    void setTitle(const std::string& title) override;
    void setArtist(const std::string& artist) override;
    void setYear(int year) override;

    void display(std::ostream& out) const override;

    bool operator<(const Song& rhs) const override;
    bool operator==(const Song& rhs) const override;
};

#endif