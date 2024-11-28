#include <iostream>
#include <fstream>
#include "list_func.hpp"

using namespace std;

void save(Node* head) {
    ofstream file("../file/song_list.txt", ios::trunc);
    if (!file) {
        cerr << "Error: Tidak dapat membuka file untuk ditulis.\n";
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        file << temp->title << "," << temp->artist << "\n";
        temp = temp->next;
    }
    file.close();
}


void load(Node*& head) { // Gunakan Node*&
    clear(head); // Kosongkan linked list terlebih dahulu

    ifstream file("../file/song_list.txt");
    if (!file) {
        cerr << "Error: Tidak dapat membuka file.\n";
        return;
    }

    string line, title, artist;
    while (getline(file, line)) {
        size_t delimiterPos = line.find(','); // Pisahkan berdasarkan koma
        if (delimiterPos != string::npos) {
            title = line.substr(0, delimiterPos);
            artist = line.substr(delimiterPos + 1);
            append(head, title, artist); // Tambahkan elemen baru
        }
    }
    file.close();
}
