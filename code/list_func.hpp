#ifndef LIST_FUNC_H
#define LIST_FUNC_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>

// Warna ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

using std::string;
using namespace std;

struct Node{
    string title;
    string artist;
    string album;
    string duration;
    struct Node *next;
};
struct Playlist {
    string title; // Nama playlist
    Node* songs;  // Pointer ke head linked list lagu
    Playlist* next;
};


//File Operation
void save(Node* head);
void load(Node*& head);
void print_ply(Playlist* head);
void loadPly(Playlist*& head);
void clearAllPlaylists(Playlist*& head);


//ll Operation
void append(Node*& head, string title, string artist, string album, string duration);
void printList(Node* head);
void clear(Node*& head);
bool dupliCheck(Node* head, const string& title, const string&  artist);
bool dupliyCheck(string title, vector <Playlist> &ply);
bool duplicateCheck(const Node* selected, const Playlist* playlist);

//Menu Function
void displayPlaylistMenu();
void displaySongMenu();
void displayMainMenu();


//PLaylist Function
void addSongToPlaylist(Playlist* head, const string& playlistTitle, const Node* song);
Playlist* findPlaylist(Playlist* head, const string& title);
Node* chooseSong(vector <Node*> head, int index);
void printTitle(Playlist* head);
void printPlaylist(Playlist* head, const string& playlistTitle);
void plyToFile(Playlist* playlist, const string& title);
void appendPlaylist(Playlist*& playlistHead, const string& title);
void dropPly(Playlist** head, const string& playlistTitle);
void rewrite(Playlist* head);


//Delete Song
void deleteSong(Node*& head, Node* toDelete);
void deleteSongFromPlaylist(Playlist* playlist, Node* songToDelete);
vector<Node*> cariLagu(Node* head, const string& kataKunci);



//Sorting function
void sortList(Node*& head, int kriteria);


#endif