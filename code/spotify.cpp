#include "list_func.hpp"
using namespace std;

void printt(Node *head){
    Node* temp = head;
    while(temp != nullptr){
        cout << temp->title << " " << temp->artist << endl;
        temp = temp->next;
    }
}
void printts(Playlist *head){
    int c = 1;
    Playlist* temp = head;
    while(temp != nullptr){
        cout << c << ". " << temp->title << endl;
        c++;
        temp = temp->next;
    }
}
int main()
{
    Node *head = nullptr;             // Pointer ke linked list lagu
    Playlist *playlistHead = nullptr; // Pointer ke linked list playlist
    string title, artist, album, duration;
    int choice;

    do
    {
        loadPly(playlistHead); // Muat playlist dari file
        load(head);
        cout << "======= Spotipi =======";
        cout << "\n1. Show Songs List\n";
        cout << "2. Add Song\n";
        cout << "3. Delete Song\n";
        cout << "4. Sort Song\n";
        cout << "5. Add song to playlist\n";
        cout << "6. Create Playlist\n";
        cout << "7. Show Playlists\n";
        cout << "8. Exit\n";
        cout << "Masukkan Pilihan (1/2/3/4/5/6/7/8): ";
        cin >> choice;

        if (choice == 1)
        {
            load(head); // Muat lagu dari file
            if (head != nullptr)
            {
                printList(head);
            }
            else
            {
                cout << "Maaf belum ada lagu di daftar lagu >_<\n";
            }
        }
        else if (choice == 2)
        {
            cout << "Masukkan Judul Lagu: ";
            cin.ignore();
            getline(cin, title);
            cout << "Masukkan Nama Artis: ";
            getline(cin, artist);
            cout << "Masukkan Album: ";
            getline(cin, album);
            cout << "Masukkan Durasi Lagu: ";
            getline(cin, duration);

            if (!dupliCheck(head, title, artist))
            {
                append(head, title, artist, album, duration);
                save(head); // Simpan lagu ke file
            }
            else
            {
                cout << "Lagu Sudah Ada dalam Daftar ^_~\n";
            }
        }
        else if (choice == 3)
        {
            cout << "Masukkan judul lagu yang ingin dihapus: ";
            cin.ignore();
            string kataKunci;
            getline(cin, kataKunci);
        
            vector<Node *> songList = cariLagu(head, kataKunci);
            if (songList.empty())
            {
                cout << "Tidak ada lagu yang cocok dengan pencarian \"" << kataKunci << "\".\n";
            }
            else
            {
                cout << "Lagu yang ditemukan:\n";
                for (size_t i = 0; i < songList.size(); ++i)
                {
                    cout << i + 1 << ". " << "Judul: " << songList[i]->title << " Oleh: " << songList[i]->artist << endl;
                }
                cout << songList.size() + 1 << ". Batal\n";

                cout << "Pilih nomor lagu yang ingin dihapus: ";
                int opsiDelete;
                cin >> opsiDelete;

                if (opsiDelete > 0 && opsiDelete <= songList.size())
                {
                    deleteSong(head, songList[opsiDelete - 1]);
                    save(head); // Simpan perubahan ke file
                    
                    cout << "Lagu berhasil dihapus.\n";
                }
                else
                {
                    cout << "Penghapusan dibatalkan.\n";
                }
            }
        }
        else if (choice == 4)
        {
            int sortChoice;
            cout << "Pilih metode pengurutan:\n";
            cout << "1. Berdasarkan Judul\n";
            cout << "2. Berdasarkan Artis\n";
            cout << "3. Berdasarkan Album\n";
            cout << "4. Berdasarkan Durasi\n";
            cout << "Masukkan Pilihan (1/2/3/4): ";
            cin >> sortChoice;

            if (sortChoice >= 1 && sortChoice <= 4)
            {
                sortList(head, sortChoice);
                cout << "List Lagu Telah diurutkan.\n";
                printList(head);
            }
            else
            {
                cout << "Pilihan tidak valid.\n";
            }
        }
        else if (choice == 5)
        {
            
            cin.ignore();
            loadPly(playlistHead); // Muat playlist dari file
            load(head);
            string playlistTitle;
            string songIndex;
            load(head); // Muat lagu dari file
            cout << "Masukkan Judul Playlist: ";
            getline(cin, playlistTitle);
            cout << "Masukkan judul lagu: ";
            cin >> songIndex;
            Playlist *selectedPlaylist = findPlaylist(playlistHead, playlistTitle);
            if (selectedPlaylist == nullptr)
            {
                cout << "Playlist Tidak Ditemukan\n";
            }
            vector<Node *> songList = cariLagu(head, songIndex);
            if (songList.empty())
            {
                cout << "Tidak ada lagu yang cocok dengan pencarian \"" << songIndex << "\".\n";
            }
            else
            {
                cout << "Lagu yang ditemukan:\n";
                for (size_t i = 0; i < songList.size(); ++i)
                {
                    cout << i + 1 << ". " << "Judul: " << songList[i]->title << " Oleh: " << songList[i]->artist << endl;
                }
                cout << songList.size() + 1 << ". Batal\n";

                cout << "Pilih nomor lagu yang ingin ditambah ke playlist: ";
                int opsiAdd;
                cin >> opsiAdd;

                if (opsiAdd > 0 && opsiAdd <= songList.size())
                {       
                    Node *selectedSong = chooseSong(songList, opsiAdd - 1);
                    
                    //error
                    if (selectedSong == nullptr)
                    {
                        cout << "Indeks lagu tidak valid.\n";
                    }
                    cout << selectedSong->title << "ini \n";
                    if (duplicateCheck(selectedSong, selectedPlaylist))
                    {
                        cout << "Lagu sudah ada dalam playlist.\n";
                    }
                    else{
                    addSongToPlaylist(playlistHead, playlistTitle, selectedSong);
                    plyToFile(playlistHead, playlistTitle);
                    }
                }
                else
                {
                    cout << "Penghapusan dibatalkan.\n";
                }
            }

        }
        else if (choice == 6)
        {
            string playlistTitle;
            cin.ignore();
            cout << "Masukkan Judul Playlist: ";
            getline(cin, playlistTitle);

            if (findPlaylist(playlistHead, playlistTitle) == nullptr)
            {
                appendPlaylist(playlistHead, playlistTitle);
                print_ply(playlistHead); // Simpan playlist baru ke file
                cout << "Playlist berhasil dibuat.\n";
            }
            else
            {
                cout << "Playlist sudah ada.\n";
            }
        }
        else if (choice == 7)
        {
            // loadPly(playlistHead); // Muat playlist dari file
            
            if (playlistHead != nullptr)
            {   
                string x;
                cout << "Masukkan Judul Playlist yang kamu ingin buka: ";
                cin.ignore();
                getline(cin, x);
                printPlaylist(playlistHead,x);
            }
            else
            {
                cout << "Tidak ada playlist yang tersedia.\n";
            }
        }
        else if (choice == 8)
        {
            cout << "Keluar dari aplikasi. Terima kasih telah menggunakan Spotipi!\n";
        }
        else if (choice == 9){
            string name;
            printts(playlistHead);
            cout << "Masukkan Judul Playlist: ";
            cin.ignore();
            getline(cin, name);
            Playlist* selectedPly = findPlaylist(playlistHead, name);
            if(selectedPly == nullptr){
                cout << "Playlist tidak ditemukan\n";
            }
            else{
                cout << "Masukkan judul lagu yang ingin dihapus: ";
            string kataKunci;
            getline(cin, kataKunci);
            Node* selectedSong = selectedPly->songs;
            vector<Node *> songList = cariLagu(selectedSong, kataKunci);
            if (songList.empty())
            {
                cout << "Tidak ada lagu yang cocok dengan pencarian \"" << kataKunci << "\".\n";
            }
            else
            {
                cout << "Lagu yang ditemukan:\n";
                for (size_t i = 0; i < songList.size(); ++i)
                {
                    cout << i + 1 << ". " << "Judul: " << songList[i]->title << " Oleh: " << songList[i]->artist << endl;
                }
                cout << songList.size() + 1 << ". Batal\n";

                cout << "Pilih nomor lagu yang ingin dihapus: ";
                int opsiDelete;
                cin >> opsiDelete;

                if (opsiDelete > 0 && opsiDelete <= songList.size())
                {
                    deleteSongFromPlaylist(selectedPly, songList[opsiDelete - 1]);
                    plyToFile(playlistHead, name);
                    cout << "Lagu berhasil dihapus.\n";
                }
                else
                {
                    cout << "Penghapusan dibatalkan.\n";
                }
            }
            }

            

        }
        else
        {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != 8);

    // Bersihkan semua data
    clear(head);                     // Bersihkan list lagu
    clearAllPlaylists(playlistHead); // Bersihkan list playlist

    return 0;
}