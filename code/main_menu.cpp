#include "list_func.hpp"
using namespace std;
// Fungsi menampilkan menu awal
void displayMainMenu() {
    cout << CYAN << "======= Spotipi =======" << RESET << endl;
    cout << GREEN << "Main Menu:" << RESET << endl;
    cout << YELLOW << "  /songmenu      " << RESET << "- Manage songs" << endl;
    cout << YELLOW << "  /playlistmenu  " << RESET << "- Manage playlists" << endl;
    cout << YELLOW << "  /exit          " << RESET << "- Exit the application" << endl;
    cout << CYAN << "=======================" << RESET << endl;
}

// Fungsi menampilkan menu untuk song management
void displaySongMenu() {
    cout << CYAN << "======= Song Menu =======" << RESET << endl;
    cout << GREEN << "Available Commands:" << RESET << endl;
    cout << YELLOW << "  /show      " << RESET << "- Show all songs" << endl;
    cout << YELLOW << "  /add       " << RESET << "- Add a new song" << endl;
    cout << YELLOW << "  /delete    " << RESET << "- Delete a song" << endl;
    cout << YELLOW << "  /sort      " << RESET << "- Sort songs" << endl;
    cout << YELLOW << "  /back      " << RESET << "- Back to main menu" << endl;
    cout << CYAN << "=========================" << RESET << endl;
}

// Fungsi menampilkan menu untuk playlist management
void displayPlaylistMenu() {
    cout << CYAN << "======= Playlist Menu =======" << RESET << endl;
    cout << GREEN << "Available Commands:" << RESET << endl;
    cout << YELLOW << "  /create " << RESET << "- Create a new playlist" << endl;
    cout << YELLOW << "  /add    " << RESET << "- Add song to a playlist" << endl;
    cout << YELLOW << "  /show   " << RESET << "- Show all playlists" << endl;
    cout << YELLOW << "  /delete " << RESET << "- Delete song from playlist" << endl;
    cout << YELLOW << "  /sort   " << RESET << "- Sort songs in a playlist" << endl;
    cout << YELLOW << "  /back   " << RESET << "- Back to main menu" << endl;
    cout << CYAN << "=============================" << RESET << endl;
}
