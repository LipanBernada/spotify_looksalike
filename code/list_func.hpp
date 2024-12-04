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
struct Playlist
{
 string title;
 vector<Node> songs;
};


void append(Node*& head, string title, string artist, string album, string duration);
void add_song(const string& song, const string& title);
bool dupliCheck(Node* head, const string& title, const string&  artist);
bool dupliyCheck(string title, vector <Playlist> &ply);
void printList(Node* head);
void print_ply(const vector<Playlist>& ply);


void save(Node* head);
void load(Node*& head);
void clear(Node*& head);
void plyToFile(const Playlist& playlist);



void loadPly(vector<Playlist>& ply);

void addSongToPlaylist(vector <Playlist>& ply, const Node* song, int index);
Node* chooseSong(Node* head, int index);
void printPlaylist(const vector<Playlist>& ply, int index); 
int findIndex(const vector<Playlist>& ply, string title);
bool duplicateCheck(Node* selected, vector<Playlist>& ply, int index);



void sortList(Node*& head, int kriteria);
void deleteSong(Node*& head, Node* toDelete);
vector<Node*> cariLagu(Node* head, const string& kataKunci);



#endif
