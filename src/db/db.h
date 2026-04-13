#pragma once
#include "../memtable/memtable.h"
#include "../sstable/sstable.h"
#include <vector>

class DB {
    private:
    Memtable memtable;
    std::vector<std::string> filenames;
    std::string directoryName;
    int sst_counter;
    SSTable sstable;

    public:
    DB(std::string& directoryName);
    std::string get(std::string& key);
    void put(std::string &key, std::string &value);
};