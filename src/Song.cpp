#include "Song.h"

Song::Song() : title(""), artist(""), year(0)
{
}

Song::Song(const std::string& title, const std::string& artist, int year)
    : title(title), artist(artist), year(year)
{
}

std::string Song::getTitle() const
{
    return title;
}

std::string Song::getArtist() const
{
    return artist;
}

int Song::getYear() const
{
    return year;
}

void Song::setTitle(const std::string& newTitle)
{
    title = newTitle;
}

void Song::setArtist(const std::string& newArtist)
{
    artist = newArtist;
}

void Song::setYear(int newYear)
{
    year = newYear;
}

void Song::display(std::ostream& out) const
{
    out << "\"" << title << "\" by " << artist << " (" << year << ")";
}

bool Song::operator<(const Song& rhs) const
{
    return title < rhs.title;
}

bool Song::operator==(const Song& rhs) const
{
    return title == rhs.title;
}