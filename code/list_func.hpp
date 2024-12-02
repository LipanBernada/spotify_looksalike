#ifndef LIST_FUNC_H
#define LIST_FUNC_H

#include <string>
using std::string;


struct Node{
    string title;
    string artist;
    string album;
    string duration;
    struct Node *next;
};

void append(Node*& head, string title, string artist, string album, string duration);
void add_song(const string& song, const string& title);
bool dupliCheck(Node* head, const string& title, const string&  artist);
void printList(Node* head);

void save(Node* head);
void load(Node*& head);
void clear(Node*& head);

void sortList(Node*& head, int kriteria);
#endif
