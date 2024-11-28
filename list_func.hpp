#ifndef LIST_FUNC_H
#define LIST_FUNC_H

#include <string>
using std::string;


struct Node{
    string title;
    string artist;
    struct Node *next;
};

void append(Node*& head, string title, string artist);
void add_song(const string& song, const string& title);
void printList(Node* head);

#endif
