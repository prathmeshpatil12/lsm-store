#pragma once
#include "../memtable/memtable.h"
#include "../sstable/sstable.h"
#include "../compaction/compaction.h"
#include <vector>

class DB {
    private:
    static const int L0_COMPACTION_TRIGGER = 4;
    static const int L1_COMPACTION_TRIGGER = 4;
    Memtable memtable;
    std::vector<std::string> l0_files;
    std::vector<std::string> l1_files;
    std::string directoryName;
    int sst_counter;
    int compaction_counter;
    SSTable sstable;
    Compaction compactor;

    void runCompaction();
    void runL1Compaction();

    public:
    DB(std::string& directoryName);
    std::string get(std::string& key);
    void put(std::string &key, std::string &value);
    
};