#include <iostream>
#include <fstream>
#include "list_func.hpp"

using namespace std;

void save(Node* head) {
    ofstream file("file/song_list.txt", ios::trunc);
    if (!file) {
        cerr << "Error: Tidak dapat membuka file untuk ditulis.\n";
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        file << temp->title << "," << temp->artist << "," << temp->album << "," << temp->duration << "\n";
        temp = temp->next;
    }
    file.close();
}

bool isFileEmpty(const string& filename) {
    ifstream file(filename);
    // Cek apakah file dapat dibuka
    if (!file.is_open()) {
        ofstream newFile(filename);
                if (!newFile.is_open()) {
            cerr << "Error: Could not create file." << endl;
            return false;
        }
        newFile.close();
        return true;
    }
    // Cek apakah file kosong
    return file.peek() == ifstream::traits_type::eof();
}


void load(Node*& head) { // Gunakan Node*&
    clear(head); // Kosongkan linked list terlebih dahulu

    ifstream file("file/song_list.txt");
    if (!file) {
        cerr << "Error: Tidak dapat membuka file.\n";
        return;
    }

    string line, title, artist, album, duration;
while (getline(file, line)) {
    size_t pos1 = line.find(','); // Posisi koma pertama
    size_t pos2 = line.find(',', pos1 + 1); // Posisi koma kedua
    size_t pos3 = line.find(',', pos2 + 1); // Posisi koma ketiga

    if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
        title = line.substr(0, pos1);
        artist = line.substr(pos1 + 1, pos2 - pos1 - 1);
        album = line.substr(pos2 + 1, pos3 - pos2 - 1);
        duration = line.substr(pos3 + 1);

        append(head, title, artist, album, duration); // Tambahkan elemen baru
    } else {
        cerr << "Invalid line format: " << line << endl;
    }
}
    file.close();
}
void print_ply(Playlist* head) {
                                cout << "Masuk";

    ofstream file("file/ply_list.txt", ios::trunc);
    if (!file) {
        cerr << "Error: Tidak dapat membuka file untuk ditulis.\n";
        return;
    }

    Playlist* temp = head;
    while (temp != nullptr) {
        file << temp->title << endl;

        // Periksa apakah file playlist kosong, jika ya, buat file kosong
        string filename = "./file/PlayLists/" + temp->title + ".txt";
        if (isFileEmpty(filename)) {
            ofstream playlistFile(filename);
            playlistFile.close();
        }

        temp = temp->next;
    }

    file.close();
}
 

    void clearAllPlaylists(Playlist*& head) {
    while (head != nullptr) {
        Playlist* temp = head;
        head = head->next;

        // Bersihkan semua lagu dalam playlist
        clear(temp->songs);
        delete temp;
    }
}

    
void loadPly(Playlist*& head) {
    // Hapus semua playlist sebelumnya
    clearAllPlaylists(head);

    ifstream file("./file/ply_list.txt");
    if (!file) {
        cerr << "Error: Tidak dapat membuka file untuk dibaca.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        // Buat playlist baru
        Playlist* newPlaylist = new Playlist;
        newPlaylist->title = line; // Nama playlist
        newPlaylist->songs = nullptr; // Inisialisasi linked list lagu
        newPlaylist->next = nullptr;

        string filename = "./file/PlayLists/" + line + ".txt";
        ifstream playlistFile(filename);
        if (!playlistFile) {
            cerr << "Error: Tidak dapat membuka file playlist " << filename << ".\n";
            delete newPlaylist; // Hapus playlist jika tidak bisa memuat file
            continue;
        }

        string lines;
        while (getline(playlistFile, lines)) {
            size_t pos1 = lines.find(',');        // Posisi koma pertama
            size_t pos2 = lines.find(',', pos1 + 1); // Posisi koma kedua
            size_t pos3 = lines.find(',', pos2 + 1); // Posisi koma ketiga

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                // Buat node lagu baru
                Node* newNode = new Node;
                newNode->title = lines.substr(0, pos1);
                newNode->artist = lines.substr(pos1 + 1, pos2 - pos1 - 1);
                newNode->album = lines.substr(pos2 + 1, pos3 - pos2 - 1);
                newNode->duration = lines.substr(pos3 + 1);
                newNode->next = nullptr;

                // Tambahkan node lagu ke linked list lagu dalam playlist
                if (newPlaylist->songs == nullptr) {
                    newPlaylist->songs = newNode;
                } else {
                    Node* temp = newPlaylist->songs;
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = newNode;
                }
            } else {
                cerr << "Invalid line format in " << filename << ": " << lines << endl;
            }
        }

        playlistFile.close();

        // Tambahkan playlist ke linked list playlist
        if (head == nullptr) {
            head = newPlaylist;
        } else {
            Playlist* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newPlaylist;
        }
    }

    file.close();
}
