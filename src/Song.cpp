#include "Song.h"

// Default constructor
// Initializes an empty song with default values
Song::Song() : title(""), artist(""), year(0)
{
}

// Parameterized constructor
// Initializes a song with given title, artist, and year
Song::Song(const std::string& title, const std::string& artist, int year)
    : title(title), artist(artist), year(year)
{
}

// Getter for song title
std::string Song::getTitle() const
{
    return title;
}

// Getter for artist name
std::string Song::getArtist() const
{
    return artist;
}

// Getter for release year
int Song::getYear() const
{
    return year;
}

// Setter for title
void Song::setTitle(const std::string& newTitle)
{
    title = newTitle;
}

// Setter for artist
void Song::setArtist(const std::string& newArtist)
{
    artist = newArtist;
}

// Setter for year
void Song::setYear(int newYear)
{
    year = newYear;
}

// Displays song in formatted output
// Example: "Time" by Pink Floyd (1973)
void Song::display(std::ostream& out) const
{
    out << "\"" << title << "\" by " << artist << " (" << year << ")";
}

// Less-than operator
// Defines BST ordering: songs are ordered by title
// This is critical for maintaining BST structure
bool Song::operator<(const Song& rhs) const
{
    return title < rhs.title;
}

// Equality operator
// Defines when two songs are considered the same in the BST
// Currently based solely on title (assumes titles are unique)
bool Song::operator==(const Song& rhs) const
{
    return title == rhs.title;
}