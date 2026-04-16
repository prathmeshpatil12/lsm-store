#pragma once
#include<iostream>
#include "skiplist.h"
#include "../wal/wal.h"

using namespace std;

class Memtable {
    private:
    SkipList* sl;
    WAL wal;
    size_t current_size;
    static const size_t MAX_SIZE = 1024;  // 1KB

    public:
    Memtable(const string& filename);
    ~Memtable();
    void put(string& key, string& value);
    string get(string& key);
    bool isFull();
    void getAll();
    vector<pair<string, string>> getEntries();
    void clear();
};