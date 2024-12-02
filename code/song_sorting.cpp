#include <iostream>
#include <fstream>
#include "list_func.hpp"

int durasiLagu(const string& durasi) {
    int minutes = 0, seconds = 0;
    char tandaBagi;
    stringstream ss(durasi);
    ss >> minutes >> tandaBagi >> seconds;
    return minutes * 60 + seconds;
}

void sortList(Node*& head, int kriteria) {

    if (!head || !head->next) return;
    bool swapp;

    do {
        swapp = false;
        Node* lagu = head;
        Node* prev = nullptr;

        while (lagu && lagu->next) {
            Node* next = lagu->next;
            bool kondisi = false;
            if (kriteria == 1) kondisi = lagu->title > next->title;
            else if (kriteria == 2) kondisi = lagu->artist > next->artist;
            else if (kriteria == 3) kondisi = lagu->album > next->album;
            else if (kriteria == 4) {
                int durasiLagu = durasiLagu(current->durasi);
                int durasiNext = durasiLagu(next->durasi);
                kondisi = durasiLagu > durasiNext;
            }

            if (kondisi) {
                if (!prev) {
                    head = next;
                } else {
                    prev->next = next;
                }
                lagu->next = next->next;
                next->next = lagu;
                swapp = true;
            }

            prev = swapp ? prev : lagu;
            lagu = lagu->next;
        }
    } while (swapp);
}
