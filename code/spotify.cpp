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
                }
                else if (command == "/delete")
                {
                    string keyword;
                    cout << "Masukkan judul lagu yang ingin dihapus: ";
                    cin.ignore();
                    getline(cin, keyword);

                    vector<Node *> songList = cariLagu(head, keyword);
                    if (songList.empty())
                    {
                        cout << RED << "Tidak ada lagu yang cocok dengan \"" << keyword << "\".\n"
                             << RESET;
                    }
                    else
                    {
                        cout << "Lagu yang ditemukan:\n";
                        for (size_t i = 0; i < songList.size(); ++i)
                        {
                            cout << i + 1 << ". " << songList[i]->title << " oleh " << songList[i]->artist << endl;
                        }
                        cout << songList.size() + 1 << ". Batal\n";

                        cout << "Pilih nomor lagu yang ingin dihapus: ";
                        int opsiDelete;
                        cin >> opsiDelete;

                        if (opsiDelete > 0 && opsiDelete <= songList.size())
                        {
                            deleteSong(head, songList[opsiDelete - 1]);
                            save(head);
                            cout << GREEN << "Lagu berhasil dihapus." << RESET << endl;
                        }
                        else
                        {
                            cout << YELLOW << "Penghapusan dibatalkan.\n"
                                 << RESET;
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
