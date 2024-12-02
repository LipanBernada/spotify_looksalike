#include "list_func.hpp"
#include <iostream>
using namespace std;


int main() {
    Node* head = nullptr;
    string title, artist, album, duration;
    int choice, sortChoice;

    do{
    cout << "======= Spotipi =======";
    cout << "\n1. Show Songs List\n";
    cout << "2. Add Song\n";
    cout << "3. Sort Songs\n";
    cout << "4. Show Playlists\n";
    cout << "5. Add Playlist\n";
    cout << "6. Exit\n";
    cout << "Masukkan Pilihan (1/2/3/4/5/6): ";
    cin >> choice;

    if (choice == 1){
        load(head);
        if(head != nullptr){
        printList(head);
        }
        else{
            cout << "Maaf belum ada lagu di daftar lagu >_<\n";
        }
    }
    else if(choice == 2){
        cout << "Masukkan Judul Lagu: ";
        cin.ignore();
        getline(cin, title);
        cout << "Masukkan Nama Artis: ";
        getline(cin,artist);
        cout << "Masukkan Album: ";
        getline(cin, album);
        cout << "Masukkan Durasi Lagu: ";
        getline(cin, duration);
        
        if(!dupliCheck(head, title, artist)){
        append(head, title, artist, album, duration);
        save(head);
        }
        else{
            cout << "Lagu Sudah Ada dalam Daftar ^_~\n";
        }
    } else if (choice == 3) {
        cout << "Pilih metode pengurutan:\n";
        cout << "1. Berdasarkan Judul\n";
        cout << "2. Berdasarkan Artis\n";
        cout << "3. Berdasarkan Album\n";
        cout << "4. Berdasarkan Durasi\n";
        cout << "Masukkan Pilihan (1/2/3/4): ";
        cin >> sortChoice;
        
        if (sortChoice >= 1 && sortChoice <= 4) {
                sortList(head, sortChoice);
                cout << "List Lagu Telah diurutkan.\n";
            } else {
                cout << "Pilihan tidak valid.\n";
            }
    }
    }while(choice != 6);
    
    printList(head);
    printList(head);
    
    return 0;
}
