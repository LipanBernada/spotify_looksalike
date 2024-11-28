#include "list_func.hpp"
#include <iostream>
using namespace std;


int main() {
    Node* head = nullptr;
    string title, artist;
    int choice;

    do{
    cout << "======= Spotipi =======";
    cout << "\n1. Show Songs List\n";
    cout << "2. Add Song\n";
    cout << "3. Show Playlists\n";
    cout << "4. Add Playlist\n";
    cout << "5. Exit\n";
    cout << "Masukkan Pilihan (1/2/3/4/5): ";
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
        
        if(!dupliCheck(head, title, artist)){
        append(head, title, artist);
        save(head);
        }
        else{
            cout << "Lagu Sudah Ada dalam Daftar ^_~\n";
        }
    }
    }while(choice != 5);
    
    printList(head);
    printList(head);
    
    return 0;
}
