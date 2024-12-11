#include "list_func.hpp"
using namespace std;

void addSongToPlaylist(Playlist* head, const string& playlistTitle, const Node* song) {
    Playlist* temp = head;

    // Cari playlist berdasarkan nama
    while (temp->next != nullptr && temp->title != playlistTitle) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Playlist \"" << playlistTitle << "\" tidak ditemukan!" << endl;
        return;
    }

    // Tambahkan lagu ke linked list dalam playlist
    Node* newSong = new Node;
    *newSong = *song; // Salin data lagu
    newSong->next = nullptr;

    if (temp->songs == nullptr) {
        temp->songs = newSong;
    } else {
        Node* songTemp = temp->songs;
        while (songTemp->next != nullptr) {
            songTemp = songTemp->next;
        }
        songTemp->next = newSong;
    }

    // Konfirmasi penambahan
    cout << "Lagu \"" << song->title << "\" telah ditambahkan ke playlist \"" << playlistTitle << "\"." << endl;
}

Playlist* findPlaylist(Playlist* head, const string& title) {
    Playlist* temp = head;
    // Cari playlist berdasarkan nama
    while (temp != nullptr) {
        if (temp->title == title) {
            return temp;
        }
        temp = temp->next;
    }

    return nullptr; // Jika tidak ditemukan
}


Node* chooseSong(vector <Node*> head, int index) {
    int current = 0; // Penomoran dimulai dari 0
    while (head[current]!= nullptr) {
        if (current == index) {
            return head[current]; // Mengembalikan pointer ke lagu yang dipilih
        }
        current++;
    }
    return nullptr; // Jika indeks tidak valid
}

void printTitle(Playlist* head){
    int curr = 1;
    if(head == nullptr){
        return;
    }
    cout << "---------------------------------" << endl;
    cout << "| No  | Judul                   |" << endl;
    cout << "---------------------------------" << endl;

    // Menampilkan data playlist
    while (head != nullptr){
        cout << "| " << setw(3) << curr << " | " 
             << setw(23) << left << head->title << " |" << endl;
        head = head->next;
        curr++;
    }
    
    cout << "---------------------------------" << endl;
}




void printPlaylist(Playlist* head, const string& playlistTitle) {
    Playlist* temp = head;

    // Cari playlist berdasarkan nama
    while (temp != nullptr && temp->title != playlistTitle) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Playlist \"" << playlistTitle << "\" tidak ditemukan!" << endl;
        return;
    }

    Node* song = temp->songs;
    if (song == nullptr) {
        cout << "Playlist \"" << temp->title << "\" kosong!" << endl;
        return;
    }
    system("cls");
    // Header tabel
    cout << "                                       "<< RED<<temp->title  << RESET<< endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "| No | Judul                    | Artis               | Album           | Durasi |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    // Isi tabel
    int index = 1;
    while (song != nullptr) {
        cout << "| " << setw(2) << index << " | "
             << setw(25) << left << song->title << "| "
             << setw(20) << left << song->artist << "| "
             << setw(16) << left << song->album << "| "
             << setw(6) << right << song->duration << " |" << endl;
        song = song->next;
        index++;
    }

    cout << "----------------------------------------------------------------------------------" << endl;
}

void plyToFile(Playlist* playlist, const string& title) {
    if (!playlist) {
        cerr << "Error: Playlist tidak valid." << endl;
        return;
    }
    Playlist* temp = playlist;
    while(temp->title != title && temp->next != nullptr){
        temp = temp->next;
    }
   cout << "Masuk Gan";
    string filename = "./file/PlayLists/" + temp->title + ".txt";
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Tidak dapat membuka file untuk menulis." << endl;
        return;
    }

    Node* song = temp->songs;
   
    while (song != nullptr) {
        file << song->title << "," << song->artist << "," 
             << song->album << "," << song->duration << endl;
        song = song->next;
    }
    file.close();
}

void appendPlaylist(Playlist*& playlistHead, const string& title) {
    // Buat node playlist baru
    Playlist* newPlaylist = new Playlist;
    newPlaylist->title = title;
    newPlaylist->songs = nullptr; // Inisialisasi linked list lagu dalam playlist
    newPlaylist->next = nullptr;

    // Jika linked list kosong, jadikan playlist baru sebagai head
    if (playlistHead == nullptr) {
        playlistHead = newPlaylist;
    } else {
        // Traversal ke akhir linked list
        Playlist* temp = playlistHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPlaylist; // Tambahkan playlist baru di akhir
    }

    cout << "Playlist \"" << title << "\" berhasil ditambahkan.\n";
}

void dropPly(Playlist** head, const string& playlistTitle) {
    Playlist* temp = *head;
    Playlist* prev = nullptr;
    string filen = "./file/PlayLists/" + playlistTitle + ".txt";
    // Jika playlist yang ingin dihapus adalah head
    if (temp != nullptr && temp->title == playlistTitle) {
        *head = temp->next;
        delete temp;
        return;
    }

    // Cari playlist yang akan dihapus
    while (temp != nullptr && temp->title != playlistTitle) {
        prev = temp;
        temp = temp->next;
    }

    // Jika playlist tidak ditemukan
    if (temp == nullptr) return;

    // Hapus playlist
    prev->next = temp->next;
    delete temp;
    remove(filen.c_str());
}



void rewrite(Playlist* head){
    Playlist* temp = head;
    ofstream file("./file/ply_list.txt",ios::trunc);
    while (temp != nullptr){
        file << temp->title << endl;
        temp = temp->next;
    }
}