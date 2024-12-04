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
void print_ply(const vector<Playlist>& ply){
        ofstream file("file/ply_list.txt", ios::trunc);
         if (!file) {
        cerr << "Error: Tidak dapat membuka file untuk ditulis.\n";
        return;
    }
        for (size_t i = 0; i < ply.size(); i++) {
        file << ply[i].title<< endl;
        }
        file.close();
        string filename;
        for(size_t i = 0; i < ply.size(); i++){
            filename = "./file/PlayLists/" + ply[i].title + ".txt";
            if(isFileEmpty(filename)){
                ofstream file (filename);
                // file << ply[i].title << endl;
                file.close();
            }
        }

        


    }  
    
void loadPly(vector<Playlist>& ply) {
    ply.clear(); // Menghapus isi vector sebelum memuat data
    ifstream file("./file/ply_list.txt");
    if (!file) {
        cerr << "Error: Tidak dapat membuka file untuk dibaca.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        Playlist newPly;
        newPly.title = line; // Nama playlist

        string filename = "./file/PlayLists/" + line + ".txt";
        ifstream playlistFile(filename);
        if (!playlistFile) {
            cerr << "Error: Tidak dapat membuka file playlist " << filename << ".\n";
            continue;
        }

        string lines;
        while (getline(playlistFile, lines)) {
            size_t pos1 = lines.find(','); // Posisi koma pertama
            size_t pos2 = lines.find(',', pos1 + 1); // Posisi koma kedua
            size_t pos3 = lines.find(',', pos2 + 1); // Posisi koma ketiga

            if ( pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                Node newNode;
                newNode.title = lines.substr(0, pos1);
                newNode.artist = lines.substr(pos1 + 1, pos2 - pos1 - 1);
                newNode.album = lines.substr(pos2 + 1, pos3 - pos2 - 1);
                newNode.duration = lines.substr(pos3 + 1);
                newNode.next = nullptr; // Tidak digunakan dalam konteks vector

                newPly.songs.push_back(newNode); // Tambahkan lagu ke vector songs
            } else {
                cerr << "Invalid line format in " << filename << ": " << lines << endl;
            }
        }

        ply.push_back(newPly); // Tambahkan playlist ke vector
    }

    file.close();
}