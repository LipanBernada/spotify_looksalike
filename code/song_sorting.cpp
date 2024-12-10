#include "list_func.hpp"
using namespace std;
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
        Node* current = head;
        Node* prev = nullptr;

        while (current && current->next) {
            Node* next = current->next;
            bool kondisi = false;

            if (kriteria == 1) kondisi = current->title > next->title;
            else if (kriteria == 2) kondisi = current->artist > next->artist;
            else if (kriteria == 3) kondisi = current->album > next->album;
            else if (kriteria == 4) {
                int durasiCurrent = durasiLagu(current->duration);
                int durasiNext = durasiLagu(next->duration);
                kondisi = durasiCurrent > durasiNext;
            }

            if (kondisi) {
                if (!prev) {
                    head = next;
                } else {
                    prev->next = next;
                }
                current->next = next->next;
                next->next = current;

                swapp = true;
                if (!prev) {
                    prev = head;
                } else {
                    prev = next;
                }
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapp);
}