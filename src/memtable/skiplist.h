#pragma once
#include <vector>
#include <string> 

using namespace std;

struct Node {
    string key;
    string value;
    vector<Node*> nextNode;

    Node(string& k, string &v, int levels) {
        this->key = k;
        this->value = v;
        this->nextNode = vector<Node*>(levels, nullptr);
    }
};

class SkipList {
    private:
    static const int MAX_LEVELS = 4;
    int activeLevels;
    Node* head;

    public:
    SkipList();
    ~SkipList();
    void insert(string& key, string& value);
    string get(const string& key);
    void getAll();
    std::vector<std::pair<std::string, std::string>> getEntries();
    void getByLevel(int level) ;
    int getActiveLevels();
};