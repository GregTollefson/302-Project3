// SongInterface.h
// CS 302 – Project 3: Music Library (Binary Search Tree)
//
// Pure abstract interface for a Song record.
// Specifies the public contract that any Song implementation must fulfill:
// accessors for each field and a stream output operator.
//
// Your concrete Song class must inherit from this interface and
// implement every method below.
//
// DO NOT MODIFY THIS FILE.

#ifndef SONG_INTERFACE_H
#define SONG_INTERFACE_H

#include <string>
#include <iostream>

using namespace std;

class SongInterface
{
public:

    virtual ~SongInterface() {}

    /** Returns the song's title.
        @return The title as a string. */
    virtual string getTitle() const = 0;

    /** Returns the song's artist.
        @return The artist as a string. */
    virtual string getArtist() const = 0;

    /** Returns the year the song was released.
        @return The release year as an integer. */
    virtual int getYear() const = 0;

    /** Sets the song's title.
        @param title  The new title. */
    virtual void setTitle(const string& title) = 0;

    /** Sets the song's artist.
        @param artist  The new artist name. */
    virtual void setArtist(const string& artist) = 0;

    /** Sets the song's release year.
        @param year  The new release year. */
    virtual void setYear(int year) = 0;

    /** Writes a human-readable representation of this song to the
        output stream. Called by operator<<.
        @param out  The output stream to write to. */
    virtual void display(ostream& out) const = 0;

};  // end SongInterface

/** Stream insertion operator for any SongInterface object.
    Calls the virtual display() method so the correct
    implementation is invoked at runtime. */
inline ostream& operator<<(ostream& out, const SongInterface& song)
{
    song.display(out);
    return out;
}

#endif
