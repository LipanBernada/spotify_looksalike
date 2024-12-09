#include "list_func.hpp"
using namespace std;

vector<Node*> cariLagu(Node* head, const string& kataKunci) {
    vector<Node*> res;
    Node* current = head;
    while (current != nullptr) {
        if (current->title.find(kataKunci) != string::npos) {
            res.push_back(current);
        }
        current = current->next;
    }
    return res;
}

void deleteSong(Node*& head, Node* toDelete) {
    if (head == nullptr || toDelete == nullptr) return;

    if (head == toDelete) {
        head = head->next;
        delete toDelete;
        return;
    }

    Node* prev = head;
    while (prev->next != nullptr && prev->next != toDelete) {
        prev = prev->next;
    }

    if (prev->next == toDelete) {
        prev->next = toDelete->next;
        delete toDelete;
    }
}