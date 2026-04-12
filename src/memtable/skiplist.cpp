#include "skiplist.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int randomLevel(int maxLevels) {
    int level = 1;
    while ((rand() % 2 == 0) && level < maxLevels) {
        level++;
    }
    return level;
}

SkipList::SkipList() {
    activeLevels = 1;
    string emptyKey = "";
    string emptyValue = "";
    head = new Node(emptyKey, emptyValue, MAX_LEVELS);
}

SkipList::~SkipList() {
    Node* curr = head->nextNode[0];
    while (curr != nullptr) {
        Node* next = curr->nextNode[0];
        delete curr;
        curr = next;
    }
    delete head;
}

void SkipList::insert(string& key, string& value) {
    vector<Node*> update(MAX_LEVELS, nullptr);
    Node* curr = head;

    for (int i = activeLevels - 1; i >= 0; i--) {
        while (curr->nextNode[i] != nullptr && curr->nextNode[i]->key < key) {
            curr = curr->nextNode[i];
        }
        update[i] = curr;
    }

    Node* candidate = curr->nextNode[0];
    if (candidate != nullptr && candidate->key == key) {
        candidate->value = value;
        return;
    }

    int newLevel = randomLevel(MAX_LEVELS);
    if (newLevel > activeLevels) {
        for (int i = activeLevels; i < newLevel; i++) {
            update[i] = head;
        }
        activeLevels = newLevel;
    }

    Node* newNode = new Node(key, value, newLevel);
    for (int i = 0; i < newLevel; i++) {
        newNode->nextNode[i] = update[i]->nextNode[i];
        update[i]->nextNode[i] = newNode;
    }
}

string SkipList::get(const string& key) {
    Node* curr = head;
    for (int i = activeLevels - 1; i >= 0; i--) {
        while (curr->nextNode[i] != nullptr && curr->nextNode[i]->key < key) {
            curr = curr->nextNode[i];
        }
    }

    curr = curr->nextNode[0];
    if (curr != nullptr && curr->key == key) {
        return curr->value;
    }
    return "";
}

void SkipList::getAll() {
    Node* curr = head;
    while (curr->nextNode[0] != nullptr) {
        curr = curr->nextNode[0];
        cout << curr->key << " " << curr->value << ", ";
    }
    cout << endl;
}

void SkipList::getByLevel(int level) {
    if (level < 0 || level >= activeLevels) {
        cout << endl;
        return;
    }

    Node* curr = head;
    while (curr->nextNode[level] != nullptr) {
        curr = curr->nextNode[level];
        cout << curr->key << " " << curr->value << ", ";
    }
    cout << endl;
}

int SkipList::getActiveLevels() {
    return activeLevels;
}