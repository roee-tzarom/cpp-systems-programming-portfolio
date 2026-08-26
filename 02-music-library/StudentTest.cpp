#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Song.hpp"
#include "Playlist.hpp"
#include "MusicLibrary.hpp"
#include <stdexcept>
#include <string>

using namespace music;

TEST_CASE("1. Song: Default info") {
    Song s;
    CHECK(s.getTitle() == "Unknown");
    CHECK(s.getDuration() == 0);
}

TEST_CASE("2. Song: Custom info") {
    Song s("Michtav LeAhi", "Kobi Aflalo", 215);
    CHECK(s.getTitle() == "Michtav LeAhi");
    CHECK(s.getDuration() == 215);
}

TEST_CASE("3. Song: Update info") {
    Song s;
    s.setTitle("Tel Aviv");
    s.setArtist("Omer Adam");
    CHECK(s.getTitle() == "Tel Aviv");
}

TEST_CASE("4. Song: Print time") {
    Song s("Melody", "Skazi", 205);
    CHECK(s.getFormattedDuration() == "3:25");
}

TEST_CASE("5. Playlist: Create empty") {
    Playlist p;
    CHECK(p.isEmpty() == true);
    CHECK(p.getCount() == 0);
}

TEST_CASE("6. Playlist: Add song") {
    Playlist p("Israeli Pop", 5);
    p.addSong(Song("Matanot Ktanot", "Rami Kleinstein", 231));
    CHECK(p.getCount() == 1);
}

TEST_CASE("7. Playlist: Find song") {
    Playlist p("Classics", 5);
    p.addSong(Song("Darkenu", "Dani Litani", 265));
    CHECK(p.findSong("Darkenu") != nullptr);
}

TEST_CASE("8. Playlist: Remove song") {
    Playlist p("Test", 5);
    p.addSong(Song("Einech Yechola", "HaHalonot HaGvohim", 191));
    p.removeSong("Einech Yechola", "HaHalonot HaGvohim");
    CHECK(p.isEmpty() == true);
}

TEST_CASE("9. Playlist: Sum time") {
    Playlist p;
    p.addSong(Song("Shnei Meshugaim", "Omer Adam", 171));
    p.addSong(Song("Mamriim", "Mosh Ben Ari", 218));
    CHECK(p.getTotalDuration() == 389);
}

TEST_CASE("10. Library: Create empty") {
    MusicLibrary lib;
    CHECK(lib.getPlaylistCount() == 0);
}

TEST_CASE("11. Library: Create playlist") {
    MusicLibrary lib;
    lib.createPlaylist("Galgalatz Hits");
    CHECK(lib.getPlaylistCount() == 1);
}

TEST_CASE("12. Library: Remove playlist") {
    MusicLibrary lib;
    lib.createPlaylist("P1");
    lib.removePlaylist("P1");
    CHECK(lib.getPlaylistCount() == 0);
}

TEST_CASE("13. Library: Count songs") {
    MusicLibrary lib;
    lib.createPlaylist("Eurovision").addSong(Song("A-Ba-Ni-Bi", "Izhar Cohen", 179));
    CHECK(lib.getTotalSongCount() == 1);
}

TEST_CASE("14. Library: Sum time") {
    MusicLibrary lib;
    lib.createPlaylist("P1").addSong(Song("Leshem", "Miri Mesika", 238));
    lib.createPlaylist("P2").addSong(Song("Hallelujah", "Milk and Honey", 202));
    CHECK(lib.getTotalDuration() == 440);
}

TEST_CASE("15. Special: Negative time error") {
    CHECK_THROWS_AS(Song("Rakevet Laila", "Mashina", -10), std::invalid_argument);
}

TEST_CASE("16. Special: Zero size error") {
    CHECK_THROWS_AS(Playlist("Fails", 0), std::invalid_argument);
}

TEST_CASE("17. Special: Dynamic resize") {
    Playlist p("Small", 1);
    p.addSong(Song("Mehozakim LeOlam", "Avraham Tal", 204));
    p.addSong(Song("Shiro Shel Shafshaf", "Meir Banai", 235));
    CHECK(p.getCapacity() >= 2);
    CHECK(p.getCount() == 2);
}

TEST_CASE("18. Special: Shift array gap") {
    Playlist p("Test", 5);
    p.addSong(Song("Tel Aviv", "Omer Adam", 201));
    p.addSong(Song("Matanot Ktanot", "Rami Kleinstein", 231));
    p.addSong(Song("Leshem", "Miri Mesika", 238));
    
    p.removeSong(0);
    CHECK(p.findSong("Tel Aviv") == nullptr);
    CHECK(p.findSong("Matanot Ktanot") != nullptr);
    CHECK(p.getCount() == 2);
}

TEST_CASE("19. Special: Deep copy") {
    MusicLibrary lib;
    Playlist externalList("External", 5);
    externalList.addSong(Song("Tutim", "Hanan Ben Ari", 203));
    
    lib.addPlaylist(externalList);
    CHECK(lib.getPlaylistCount() == 1);
}

TEST_CASE("20. Special: Time over hour") {
    Playlist p;
    p.addSong(Song("Mix", "Various", 4000));
    CHECK(p.getFormattedTotalDuration() == "1:06:40");
}