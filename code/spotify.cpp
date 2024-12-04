#include "list_func.hpp"
using namespace std;

int main()

{
    Node *head = nullptr;
    string title, artist, album, duration;
    int choice, sortChoice;
    vector<Playlist> ply;
    do
    {
        loadPly(ply);
        cout << "======= Spotipi =======";
        cout << "\n1. Show Songs List\n";
        cout << "2. Add Song\n";
        cout << "3. Delete Song\n";
        cout << "4. Sort Song\n";
        cout << "5. Add song to playlist\n";
        cout << "6. Create PLaylist\n";
        cout << "7. Exit\n";
        cout << "Masukkan Pilihan (1/2/3/4/5/6/7): ";
        cin >> choice;

        if (choice == 1)
        {
            load(head);
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
                save(head);
            }
            else
            {
                cout << "Lagu Sudah Ada dalam Daftar ^_~\n";
            }
        }
        else if (choice == 3){
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
                    save(head);
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
            loadPly(ply);
            string ttle;
            int songIndex, plyIndex;
            load(head);
            cout << "Masukkan Judul Playlist: ";
            getline(cin, ttle);
            plyIndex = findIndex(ply, ttle);
            if (plyIndex == -1)
            {
                cout << "Playlist Tidak Ditemukan\n";
            }
            else
            {
                printList(head);

                cout << "\nPilih nomor lagu yang ingin ditambahkan ke playlist: ";
                cin >> songIndex;
                Node *selectedSong = chooseSong(head, songIndex);
                bool dupli = duplicateCheck(selectedSong, ply, plyIndex);
                if (selectedSong != nullptr && !dupli)
                {
                    addSongToPlaylist(ply, selectedSong, plyIndex);
                    printPlaylist(ply, plyIndex);
                    plyToFile(ply[plyIndex]);
                }
                else
                {
                    if (dupli)
                    {
                        cout << "Lagu sudah ada dalam playlist\n";
                    }
                    else
                    {
                        cout << "Indeks lagu tidak valid.\n";
                    }
                }

                plyIndex = 0;
            }
        }
        else if (choice == 6)
        {
            loadPly(ply);
            Playlist newply;
            cout << "Masukkan Judul PLaylist: ";
            cin.ignore();
            getline(cin, newply.title);
            if (ply.empty())
            {
                ply.push_back(newply);
                print_ply(ply);
            }
            else
            {
                if (dupliyCheck(newply.title, ply))
                {
                    cout << "Maaf Playlist Sudah ada >_<";
                }
                else
                {
                    ply.push_back(newply);
                    print_ply(ply);
                }
            }
        }
        else if (choice == 7)
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
                    save(head);
                    cout << "Lagu berhasil dihapus.\n";
                }
                else
                {
                    cout << "Penghapusan dibatalkan.\n";
                }
            }
        }
    } while (choice != 7);

    return 0;
}
