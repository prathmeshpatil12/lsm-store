#include "memtable.h"

using namespace std;

Memtable::Memtable(const string& filename) : wal(filename) {
    current_size = 0;
}

string Memtable::get(string& key) {
    return sl.get(key);
}

void Memtable::put(string& key, string& value) {
    wal.append(key, value);
    sl.insert(key, value);
    current_size += key.size() + value.size();
}

void Memtable::getAll() {
    sl.getAll();
}

bool Memtable::isFull() {
    if(current_size>=MAX_SIZE) {
        return true;
    } else {
        return false;
    }
}

vector<pair<string, string>> Memtable::getEntries() {
    return sl.getEntries();
}

void Memtable::clear() {
    this->current_size = 0;
    sl = SkipList();
    wal.clear();
}