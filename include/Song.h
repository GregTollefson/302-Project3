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