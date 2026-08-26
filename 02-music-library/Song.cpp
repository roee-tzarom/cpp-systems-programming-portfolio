#include "Song.hpp"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <utility>

namespace music {

    int Song::songCount = 0;

    Song::Song() : title("Unknown"), artist("Unknown"), durationSeconds(0) {
        songCount++;
    }

    Song::Song(const std::string& title, const std::string& artist, int durationSeconds) : title(title), artist(artist){
        if (durationSeconds < 0) {
            throw std::invalid_argument("Duration cannot be negative");
        }

        this->durationSeconds = durationSeconds;
        songCount++;
    }

    Song::Song(const Song& other) : title(other.title), artist(other.artist), durationSeconds(other.durationSeconds) {
        songCount++;
    }

    Song& Song::operator=(const Song& other){
        if (this != &other){
            title = other.title;
            artist = other.artist;
            durationSeconds = other.durationSeconds;
        }
        return *this;
    }

    Song::Song(Song&& other) noexcept : title(std::move(other.title)), artist(std::move(other.artist)), durationSeconds(other.durationSeconds){
        other.durationSeconds = 0;
        songCount++;
    }

    Song& Song::operator=(Song&& other) noexcept {
        if (this != &other){
            title = std::move(other.title);
            artist = std::move(other.artist);
            durationSeconds = other.durationSeconds;
        
            other.durationSeconds = 0;
        }
        return *this;
    }

    Song::~Song() {
        songCount--;
    }

    void Song::setTitle(const std::string& title){
        this->title = title;
    }

    void Song::setArtist(const std::string& artist){
        this->artist = artist;
    }

    void Song::setDuration(int seconds) {
        if (seconds < 0) {
            throw std::invalid_argument("Duration cannot be negative");
        }
        this->durationSeconds = seconds;
    }

    int Song::getSongCount() {
        return songCount;
    }

    std::string Song::getFormattedDuration() const {
        const int SECONDS_IN_MINUTE = 60;
        int minutes = durationSeconds / SECONDS_IN_MINUTE;
        int seconds = durationSeconds % SECONDS_IN_MINUTE;

        std::ostringstream oss;

        oss << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
    
        return oss.str();
    }
    
}