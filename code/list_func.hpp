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



void append(Node*& head, string title, string artist, string album, string duration);
void add_song(const string& song, const string& title);
bool dupliCheck(Node* head, const string& title, const string&  artist);
bool dupliyCheck(string title, vector <Playlist> &ply);
void printList(Node* head);
void print_ply(Playlist* head);

void save(Node* head);
void load(Node*& head);
void clear(Node*& head);
void plyToFile(Playlist* playlist, const string& title);


void loadPly(Playlist*& head);
    void clearAllPlaylists(Playlist*& head);
    void appendPlaylist(Playlist*& playlistHead, const string& title);

void addSongToPlaylist(Playlist* head, const string& playlistTitle, const Node* song);
Node* chooseSong(vector <Node*> head, int index);
void printPlaylist(Playlist* head, const string& playlistTitle);
Playlist* findPlaylist(Playlist* head, const string& title);
bool duplicateCheck(const Node* selected, const Playlist* playlist);
void printTitle(Playlist* head);


void sortList(Node*& head, int kriteria);
void deleteSong(Node*& head, Node* toDelete);
void deleteSongFromPlaylist(Playlist* playlist, Node* songToDelete);
void deletePlaylistFromFile(const string& playlistTitle);
void rewrite(Playlist* head);
vector<Node*> cariLagu(Node* head, const string& kataKunci);
void dropPly(Playlist** head, const string& playlistTitle);

void displayPlaylistMenu();
void displaySongMenu();
void displayMainMenu();


#endif