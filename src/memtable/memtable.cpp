#include "memtable.h"

using namespace std;

Memtable::Memtable(const string& filename) : wal(filename) {
    sl = new SkipList();
    current_size = 0;
}

string Memtable::get(string& key) {
    return sl->get(key);
}

void Memtable::put(string& key, string& value) {
    wal.append(key, value);
    sl->insert(key, value);
    current_size += key.size() + value.size();
}

void Memtable::getAll() {
    sl->getAll();
}

bool Memtable::isFull() {
    if(current_size>=MAX_SIZE) {
        return true;
    } else {
        return false;
    }
}

vector<pair<string, string>> Memtable::getEntries() {
    return sl->getEntries();
}

void Memtable::clear() {
    delete sl;
    this->current_size = 0;
    sl = new SkipList();
    wal.clear();
}

Memtable::~Memtable() {
    delete sl;
}