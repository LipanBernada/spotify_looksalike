#ifndef LIST_FUNC_H
#define LIST_FUNC_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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
Node* chooseSong(Node* head, int index);
void printPlaylist(Playlist* head, const string& playlistTitle);
Playlist* findPlaylist(Playlist* head, const string& title);
bool duplicateCheck(const Node* selected, const Playlist* playlist);


void sortList(Node*& head, int kriteria);
void deleteSong(Node*& head, Node* toDelete);
vector<Node*> cariLagu(Node* head, const string& kataKunci);



#endif
