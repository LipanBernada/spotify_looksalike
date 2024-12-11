#include "list_func.hpp"
using namespace std;

string matchChoice(const string &input, const vector<string> &userChoice)
{
    vector<string> ifMatches;
    for (const string &cmd : userChoice)
    {
        if (cmd.find(input) != string::npos)
        {
            ifMatches.push_back(cmd);
        }
    }

    if (ifMatches.size() == 1)
    {
        return ifMatches[0];
    }
    else if (ifMatches.empty())
    {
        return "";
    }
    else
    {
        cout << "Input ambigu, cocok dengan beberapa perintah: ";
        for (const string &match : ifMatches)
        {
            cout << match << " ";
        }
        cout << endl;
        return "";
    }
}

int main()
{
    Node *head = nullptr;             // Pointer ke linked list lagu
    Playlist *playlistHead = nullptr; // Pointer ke linked list playlist
    string command;

    vector<string> mainChoice = {"/songmenu", "/playlistmenu", "/exit"};
    vector<string> songDisplayChoice = {"/show", "/add", "/delete", "/sort", "/back"};
    vector<string> plyListChoice = {"/create", "/add", "/show", "/delete", "/sort", "/back", "/drop"};

    do
    {
        load(head);
        loadPly(playlistHead);
        system("cls");

        displayMainMenu();
        cout << CYAN << "Masukkan Command: " << RESET;
        cin >> command;
        command = matchChoice(command, mainChoice);

        if (command == "/songmenu")
        {
            do
            {
                load(head);
                loadPly(playlistHead);
                displaySongMenu();
                cout << CYAN << "Masukkan Command: " << RESET;
                cin >> command;
                command = matchChoice(command, songDisplayChoice);

                if (command == "/show")
                {
                    load(head);
                    if (head != nullptr)
                    {
                        printList(head);
                        system("pause");
                    }
                    else
                    {
                        cout << RED << "Maaf, belum ada lagu di daftar lagu >_<\n"
                             << RESET;
                    }
                }
                else if (command == "/add")
                {
                    string title, artist, album, duration;
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
                        cout << GREEN << "Lagu berhasil ditambahkan!" << RESET << endl;
                    }
                    else
                    {
                        cout << RED << "Lagu sudah ada dalam daftar ^_~\n"
                             << RESET;
                    }
                    system("pause");
                }
                else if (command == "/delete")
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
                            while (playlistHead != nullptr)
                            {
                                Playlist *selectedPly = findPlaylist(playlistHead, playlistHead->title);
                                deleteSongFromPlaylist(selectedPly, songList[opsiDelete - 1]);
                                plyToFile(playlistHead, selectedPly->title);
                                playlistHead = playlistHead->next;
                            }
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
                else if (command == "/sort")
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
                        load(head);
                        sortList(head, sortChoice);
                        cout << GREEN << "List Lagu Telah diurutkan.\n"
                             << RESET;
                        printList(head);
                        save(head);
                    }
                    else
                    {
                        cout << RED << "Pilihan tidak valid.\n"
                             << RESET;
                    }
                    system("pause");
                }
                else if (command == "/back")
                {
                    break;
                }
                else
                {
                    cout << RED << "Command tidak dikenali. Silakan coba lagi.\n"
                         << RESET;
                }
            } while (command != "/back");
        }
        else if (command == "/playlistmenu")
        {
            do
            {
                load(head);
                loadPly(playlistHead);
                displayPlaylistMenu();
                cout << CYAN << "Masukkan Command: " << RESET;
                cin >> command;
                command = matchChoice(command, plyListChoice);

                if (command == "/create")
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
                    system("pause");
                }
                else if (command == "/add")
                {
                    cin.ignore();
                    loadPly(playlistHead); // Muat playlist dari file
                    load(head);
                    string playlistTitle;
                    string songIndex;
                    printTitle(playlistHead);
                    cout << "Masukkan Judul Playlist: ";
                    getline(cin, playlistTitle);
                    Playlist *selectedPlaylist = findPlaylist(playlistHead, playlistTitle);
                    if (selectedPlaylist == nullptr)
                    {
                        cout << "Playlist Tidak Ditemukan\n";
                        system("pause");
                        continue;
                    }
                    printList(head);
                    cout << "Masukkan judul lagu: ";
                    cin >> songIndex;
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

                            // error
                            if (selectedSong == nullptr)
                            {
                                cout << "Indeks lagu tidak valid.\n";
                            }
                            cout << selectedSong->title << "ini \n";
                            if (duplicateCheck(selectedSong, selectedPlaylist))
                            {
                                cout << "Lagu sudah ada dalam playlist.\n";
                            }
                            else
                            {
                                addSongToPlaylist(playlistHead, playlistTitle, selectedSong);
                                plyToFile(playlistHead, playlistTitle);
                            }
                        }
                        else
                        {
                            cout << "Penghapusan dibatalkan.\n";
                        }
                    }
                    system("pause");
                }
                else if (command == "/show")
                {
                    if (playlistHead != nullptr)
                    {
                        string x;
                        printTitle(playlistHead);
                        cout << "Masukkan Judul Playlist yang kamu ingin buka: ";
                        cin.ignore();
                        getline(cin, x);
                        printPlaylist(playlistHead, x);
                        system("pause");
                    }
                    else
                    {
                        cout << "Tidak ada playlist yang tersedia.\n";
                    }
                }
                else if (command == "/delete")
                {
                    string name;
                    cout << "Masukkan Judul Playlist: ";
                    cin.ignore();
                    getline(cin, name);
                    Playlist *selectedPly = findPlaylist(playlistHead, name);
                    if (selectedPly == nullptr)
                    {
                        cout << "Playlist tidak ditemukan\n";
                    }
                    else
                    {
                        cout << "Masukkan judul lagu yang ingin dihapus: ";
                        string kataKunci;
                        getline(cin, kataKunci);
                        Node *selectedSong = selectedPly->songs;
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
                else if (command == "/sort")
                {
                               string plylistToSort;
            cin.ignore();
            cout << "Pilih judul playlist yang ingin di sort: ";
            getline(cin, plylistToSort);
            Playlist *selectedPlaylist = findPlaylist(playlistHead, plylistToSort);
            int plySortchoice;
            cout << "Pilih metode pengurutan:\n";
            cout << "1. Berdasarkan Judul\n";
            cout << "2. Berdasarkan Artis\n";
            cout << "3. Berdasarkan Album\n";
            cout << "4. Berdasarkan Durasi\n";
            cout << "Masukkan Pilihan (1/2/3/4): ";
            cin >> plySortchoice;
            if(plySortchoice >= 1 && plySortchoice <= 4){
                Node* sortPly = selectedPlaylist->songs;
                sortList(sortPly, plySortchoice);
                selectedPlaylist->songs = sortPly;
                cout << "List Lagu dalam Playlist Telah diurutkan.\n";
                printList(sortPly);
                plyToFile(selectedPlaylist, selectedPlaylist->title);
            }
                }
                else if (command == "/back")
                {
                    break;
                }
                else if (command == "/drop")
                {
                    string name;
                    printTitle(playlistHead);
                    cout << "Masukkan Judul Playlist yang Ingin di Hapus: ";
                    cin.ignore();
                    getline(cin, name);
                    dropPly(&playlistHead, name);
                    rewrite(playlistHead);
                }
                else
                {
                    cout << RED << "Command tidak dikenali. Silakan coba lagi.\n"
                         << RESET;
                }
            } while (command != "/back");
        }
        else if (command == "/exit")
        {
            cout << GREEN << "Keluar dari aplikasi. Terima kasih telah menggunakan Spotipi!\n"
                 << RESET;
        }
        else
        {
            cout << RED << "Command tidak dikenali. Silakan coba lagi.\n"
                 << RESET;
        }
    } while (command != "/exit");

    clear(head);
    clearAllPlaylists(playlistHead);

    return 0;
}
