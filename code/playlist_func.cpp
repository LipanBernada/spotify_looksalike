#include "list_func.hpp"
using namespace std;

void addSongToPlaylist(vector <Playlist>& ply, const Node* song, int index) {
    // Tambahkan lagu ke playlist
    ply[index].songs.push_back(*song);

    // Konfirmasi penambahan
    cout << "Lagu \"" << song->title << "\" telah ditambahkan ke playlist \"" << ply[index].title << "\"." << endl;
}
int findIndex(const vector<Playlist>& ply, string title){
    for(int i = 0; i < ply.size(); i++){
        if(ply[i].title == title){
            return i;
        }
    }
    return -1;
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


void printPlaylist(const vector<Playlist>& ply, int index) {
    if (ply[index].songs.empty()) {
        cout << "Playlist \"" << ply[index].title << "\" is empty!" << endl;
        return;
    }

    cout << "Playlist \"" << ply[index].title << "\":" << endl;
    for (size_t i = 0; i < ply[index].songs.size(); i++) {
        const Node& song = ply[index].songs[i];
        cout << i + 1 << ". Title: " << song.title
             << ", Artist: " << song.artist
             << ", Album: " << song.album
             << ", Duration: " << song.duration << endl;
    }
}

void plyToFile(const Playlist& playlist) {
    string filename = "./file/PlayLists/" + playlist.title + ".txt"; // Nama file dari judul playlist
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }


    for (size_t i = 0; i < playlist.songs.size(); ++i) {
        file << playlist.songs[i].title  << "," << playlist.songs[i].artist << "," <<playlist.songs[i].album << "," << playlist.songs[i].duration << endl;
    }
    file.close();
}

    