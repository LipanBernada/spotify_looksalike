#include "list_func.hpp"
using namespace std;

vector<Node*> cariLagu(Node* head, const string& kataKunci) {
    vector<Node*> res;
    Node* current = head;
    while (current != nullptr) {
        if (current->title.find(kataKunci) != string::npos) {
            res.push_back(current);
        }
        current = current->next;
    }
    return res;
}

void deleteSong(Node*& head, Node* toDelete) {
    if (head == nullptr || toDelete == nullptr) return;

    if (head == toDelete) {
        head = head->next;
        delete toDelete;
        return;
    }

    Node* prev = head;
    while (prev->next != nullptr && prev->next != toDelete) {
        prev = prev->next;
    }

    if (prev->next == toDelete) {
        prev->next = toDelete->next;
        delete toDelete;
    }
}

void deleteSongFromPlaylist(Playlist* playlist, Node* songToDelete) {
    if (playlist == nullptr) {
        cout << "Playlist tidak valid." << endl;
        return;
    }

    // Cari node lagu di linked list berdasarkan pointer
    Node* currentSong = playlist->songs;
    Node* prevSong = nullptr;

    while (currentSong != nullptr && currentSong->title != songToDelete->title) {
        prevSong = currentSong;
        currentSong = currentSong->next;
    }

    // Jika node lagu tidak ditemukan
    if (currentSong == nullptr) {
        return;
    }

    // Hapus node lagu
    if (prevSong == nullptr) {
        // Jika lagu adalah head
        playlist->songs = currentSong->next;
    } else {
        // Jika lagu bukan head
        prevSong->next = currentSong->next;
    }

    // Bebaskan memori
    delete currentSong;


    cout << "Lagu berhasil dihapus dari playlist " << playlist->title << "." << endl;
}
