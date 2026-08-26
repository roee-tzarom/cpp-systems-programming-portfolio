#include "Playlist.hpp"
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <cstddef>

namespace music {

int Playlist::totalPlaylistsCreated = 0;

Playlist::Playlist() : name("Untitled"), capacity(4), count(0) {
    songs = new Song*[static_cast<std::size_t>(capacity)];
    totalPlaylistsCreated++;
}

Playlist::Playlist(const std::string& name, int initialCapacity) : name(name), count(0) {
    if (initialCapacity <= 0) {
        throw std::invalid_argument("Capacity must be greater than zero");
    }
    this->capacity = initialCapacity;
    songs = new Song*[static_cast<std::size_t>(capacity)];
    totalPlaylistsCreated++;
}

Playlist::Playlist(const Playlist& other) : name(other.name), capacity(other.capacity), count(other.count) {
    songs = new Song*[static_cast<std::size_t>(capacity)];
    for (int i = 0; i < count; i++) {
        songs[i] = new Song(*(other.songs[i])); 
    }
    totalPlaylistsCreated++;
}

Playlist& Playlist::operator=(const Playlist& other) {
    if (this != &other) {
        clear();
        delete[] songs;

        name = other.name;
        capacity = other.capacity;
        count = other.count;
        
        songs = new Song*[static_cast<std::size_t>(capacity)];
        for (int i = 0; i < count; i++) {
            songs[i] = new Song(*(other.songs[i]));
        }
    }
    return *this;
}

Playlist::Playlist(Playlist&& other) noexcept 
    : name(std::move(other.name)), songs(other.songs), capacity(other.capacity), count(other.count) {
    other.songs = nullptr;
    other.count = 0;
    other.capacity = 0;
    totalPlaylistsCreated++;
}

Playlist& Playlist::operator=(Playlist&& other) noexcept {
    if (this != &other) {
        clear();
        delete[] songs;

        name = std::move(other.name);
        songs = other.songs;
        capacity = other.capacity;
        count = other.count;

        other.songs = nullptr;
        other.count = 0;
        other.capacity = 0;
    }
    return *this;
}

Playlist::~Playlist() {
    clear();
    delete[] songs;
}

void Playlist::resize() {
    int newCapacity = capacity * 2;
    Song** newSongs = new Song*[static_cast<std::size_t>(newCapacity)];

    for (int i = 0; i < count; i++) {
        newSongs[i] = songs[i];
    }

    delete[] songs;
    songs = newSongs;
    capacity = newCapacity;
}

void Playlist::clear() {
    for (int i = 0; i < count; i++) {
        delete songs[i];
    }
    count = 0;
}

void Playlist::addSong(const Song& song) {
    if (count == capacity) {
        resize();
    }
    songs[count] = new Song(song);
    count++;
}

bool Playlist::removeSong(int index) {
    if (index < 0 || index >= count) {
        return false;
    }

    delete songs[index];

    for (int i = index; i < count - 1; i++) {
        songs[i] = songs[i + 1];
    }
    
    count--;
    songs[count] = nullptr;
    return true;
}

bool Playlist::removeSong(const std::string& title, const std::string& artist) {
    for (int i = 0; i < count; i++) {
        if (songs[i]->getTitle() == title && songs[i]->getArtist() == artist) {
            return removeSong(i);
        }
    }
    return false;
}

Song* Playlist::findSong(const std::string& title) const {
    for (int i = 0; i < count; i++) {
        if (songs[i]->getTitle() == title) {
            return songs[i];
        }
    }
    return nullptr;
}

void Playlist::setName(const std::string& name) {
    this->name = name;
}

int Playlist::getTotalPlaylistsCreated() {
    return totalPlaylistsCreated;
}

int Playlist::getTotalDuration() const {
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += songs[i]->getDuration();
    }
    return total;
}

std::string Playlist::getFormattedTotalDuration() const {
    const int SECONDS_IN_HOUR = 3600;
    const int SECONDS_IN_MINUTE = 60;
    
    int totalSeconds = getTotalDuration();
    int hours = totalSeconds / SECONDS_IN_HOUR;
    int minutes = (totalSeconds % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE;
    int seconds = totalSeconds % SECONDS_IN_MINUTE;

    std::ostringstream oss;

    if (hours > 0) {
        oss << hours << ":" 
            << std::setfill('0') << std::setw(2) << minutes << ":" 
            << std::setfill('0') << std::setw(2) << seconds;
    } 
    else {
        oss << minutes << ":" 
            << std::setfill('0') << std::setw(2) << seconds;
    }

    return oss.str();
}

}