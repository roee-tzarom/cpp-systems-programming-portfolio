#include "MusicLibrary.hpp"
#include <stdexcept>
#include <utility>
#include <cstddef>

namespace music {

    int MusicLibrary::totalSongsAddedEver = 0;

    MusicLibrary::MusicLibrary() : ownerName("Anonymous"), capacity(2), count(0) {
        playlists = new Playlist*[static_cast<std::size_t>(capacity)];
    }

    MusicLibrary::MusicLibrary(const std::string& ownerName, int initialCapacity) : ownerName(ownerName), count(0) {
        if (initialCapacity <= 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }

        this->capacity = initialCapacity;
        playlists = new Playlist*[static_cast<std::size_t>(capacity)];
    }

    MusicLibrary::MusicLibrary(const MusicLibrary& other) : ownerName(other.ownerName), capacity(other.capacity), count(other.count) {
        playlists = new Playlist*[static_cast<std::size_t>(capacity)];

        for (int i = 0; i < count; i++) {
            playlists[i] = new Playlist(*(other.playlists[i]));
        }
    }

    MusicLibrary& MusicLibrary::operator=(const MusicLibrary& other) {
        if (this != &other) {
            clear();
            delete[] playlists;

            ownerName = other.ownerName;
            capacity = other.capacity;
            count = other.count;

            playlists = new Playlist*[static_cast<std::size_t>(capacity)];
            for (int i = 0; i < count; i++) {
                playlists[i] = new Playlist(*(other.playlists[i]));
            }
        }
        return *this;
    }

    MusicLibrary::MusicLibrary(MusicLibrary&& other) noexcept : ownerName(std::move(other.ownerName)), playlists(other.playlists), capacity(other.capacity), count(other.count) {
        other.playlists = nullptr;
        other.capacity = 0;
        other.count = 0;
    }

    MusicLibrary& MusicLibrary::operator=(MusicLibrary&& other) noexcept {
        if (this != &other) {
            clear();
            delete[] playlists;

            ownerName = std::move(other.ownerName);
            playlists = other.playlists;
            capacity = other.capacity;
            count = other.count;
            
            other.playlists = nullptr;
            other.capacity = 0;
            other.count = 0;
        }
        return *this;
    }

    MusicLibrary::~MusicLibrary() {
        clear();
        delete[] playlists;
    }

    void MusicLibrary::resize() {
        int newCapacity = capacity * 2;
        Playlist** newPlaylists = new Playlist*[static_cast<std::size_t>(newCapacity)];

        for (int i = 0; i < count; i++) {
            newPlaylists[i] = playlists[i];
        }

        delete[] playlists;
        playlists = newPlaylists;
        capacity = newCapacity;
    }

    void MusicLibrary::clear() {
        for (int i = 0; i < count; i++) {
            delete playlists[i];
        }
        count = 0;
    }

    void MusicLibrary::setOwnerName(const std::string& newOwnerName) {
        this->ownerName = newOwnerName;
    }

    int MusicLibrary::getTotalSongsAddedEver() {
        return totalSongsAddedEver;
    }

    void MusicLibrary::incrementTotalSongs() {
        totalSongsAddedEver++;
    }

    Playlist& MusicLibrary::createPlaylist(const std::string& name) {
        if (count == capacity) {
            resize(); 
        }

        playlists[count] = new Playlist(name);
        count++;

        return *(playlists[count - 1]);
    }

    void MusicLibrary::addPlaylist(const Playlist& playlist) {
        if (count == capacity) {
            resize(); 
        }

        playlists[count] = new Playlist(playlist);
        count++;
    }

    bool MusicLibrary::removePlaylist(int index) {
        if (index < 0 || index >= count) {
            return false;
        }

        delete playlists[index];

        for (int i = index; i < count - 1; i++) {
            playlists[i] = playlists[i + 1];
        }

        count--;
        playlists[count] = nullptr;
        return true;
    }

    bool MusicLibrary::removePlaylist(const std::string& name) {
        for (int i = 0; i < count; i++) {
            if (playlists[i]->getName() == name) {
                return removePlaylist(i);
            }
        }

        return false;
    }

    Playlist* MusicLibrary::findPlaylist(const std::string& name) const {
        for (int i = 0; i < count; i++) {
            if (playlists[i]->getName() == name) {
                return playlists[i];
            }
        }

        return nullptr;
    }

    int MusicLibrary::getTotalDuration() const {
        int total = 0;
        for (int i = 0; i < count; i++) {
            total += playlists[i]->getTotalDuration();
        }

        return total;
    }

    int MusicLibrary::getTotalSongCount() const {
        int total = 0;
        for (int i = 0; i < count; i++) {
            total += playlists[i]->getCount();
        }

        return total;
    }

}