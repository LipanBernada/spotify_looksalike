#include "list_func.hpp"
using namespace std;

void addSongToPlaylist(Playlist& playlist, const Node& song) {
    // Tambahkan lagu ke playlist
    playlist.songs.push_back(song);

    // Konfirmasi penambahan
    cout << "Lagu \"" << song.title << "\" telah ditambahkan ke playlist \"" << playlist.title << "\"." << endl;
}


Node* chooseSong(Node* head, int index) {
    int current = 1; // Penomoran dimulai dari 1
    while (head != nullptr) {
        if (current == index) {
            return head; // Mengembalikan pointer ke lagu yang dipilih
        }
        head = head->next; // Lanjut ke node berikutnya
        current++;
    }
    return nullptr; // Jika indeks tidak valid
}


void printPlaylist(const Playlist& playlist) {
    if (playlist.songs.empty()) {
        cout << "Playlist \"" << playlist.title << "\" is empty!" << endl;
        return;
    }

    cout << "Playlist \"" << playlist.title << "\":" << endl;
    for (size_t i = 0; i < playlist.songs.size(); i++) {
        const Node& song = playlist.songs[i];
        cout << i + 1 << ". Title: " << song.title
             << ", Artist: " << song.artist
             << ", Album: " << song.album
             << ", Duration: " << song.duration << endl;
    }
}
