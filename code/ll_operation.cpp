#include <iostream>
#include "list_func.hpp"
using namespace std;

// Implementasi fungsi
void add_song(const string& song, const string& title) {
    cout << "Song: " << song << ", Title: " << title << endl;
}

void append(Node*& head, string title, string artist, string album, string duration) {
    Node* newNode = new Node{title,artist, album, duration, nullptr}; // Membuat node baru
    if (head == nullptr) {
        head = newNode; // Jika linked list kosong, node baru menjadi head
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next; 
    }
    temp->next = newNode; 
}
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << "Title: " << temp->title << " Artist: " << temp->artist << " Album: " << temp->album << " Duration: " << temp->duration << endl;
        temp = temp->next;
    }
}

void clear(Node*& head) { // Gunakan Node*& agar perubahan head berlaku global
    while (head) {
        Node* temp = head;
        head = head->next; // Pindahkan head ke node berikutnya
        delete temp;       // Hapus node saat ini
    }
}
bool dupliCheck(Node* head, const string& title, const string& artist) {
    Node* temp = head;
    while (temp) {
        if (temp->title == title && temp->artist == artist) { // Jika ditemukan duplikasi
            return true;
        }
        temp = temp->next; // Lanjutkan ke node berikutnya
    }
    return false; // Tidak ada duplikasi
}
bool dupliyCheck(string title, vector <Playlist> &ply) {

    for (int i = 0; i < ply.size(); i++) {
        if (title == ply[i].title) {
            return true;
        }
    }
    return false; // Tidak ada duplikat
}
bool duplicateCheck(const Node* selected, const Playlist* playlist) {
    if (playlist == nullptr) return false;
    
    Node* songTemp = playlist->songs;
    while (songTemp != nullptr) {
        if (selected->title == songTemp->title) {
            return true; // Lagu sudah ada
        }
        songTemp = songTemp->next;
    }
    return false; // Tidak ada duplikasi
}
