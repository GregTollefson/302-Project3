#include "Song.h"

// Default constructor
// Initializes an empty song with default values
Song::Song() : title_(""), artist_(""), year_(0)
{
}

// Parameterized constructor
// Initializes a song with given title, artist, and year
Song::Song(const std::string& title, const std::string& artist, int year)
    : title_(title), artist_(artist), year_(year)
{
}

// Getter for song title
std::string Song::getTitle() const
{
    return title_;
}

// Getter for artist name
std::string Song::getArtist() const
{
    return artist_;
}

// Getter for release year
int Song::getYear() const
{
    return year_;
}

// Setter for title
void Song::setTitle(const std::string& newTitle)
{
    title_ = newTitle;
}

// Setter for artist
void Song::setArtist(const std::string& newArtist)
{
    artist_ = newArtist;
}

// Setter for year
void Song::setYear(int newYear)
{
    year_ = newYear;
}

// Displays song in formatted output
// Example: "Time" by Pink Floyd (1973)
void Song::display(std::ostream& out) const
{
    out << "\"" << title_ << "\" by " << artist_ << " (" << year_ << ")";
}

// Less-than operator
// Defines BST ordering: songs are ordered by title
// This is critical for maintaining BST structure
bool Song::operator<(const Song& rhs) const
{
    return title_ < rhs.title_;
}

// Equality operator
// Defines when two songs are considered the same in the BST
// Currently based solely on title (assumes titles are unique)
bool Song::operator==(const Song& rhs) const
{
    return title_ == rhs.title_;
}