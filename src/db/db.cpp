#include "db.h"

using namespace std;

DB::DB(string& directoryName) : memtable(directoryName + "/wal.log"), sst_counter(0), directoryName(directoryName) {

};

void DB::put(string &key, string &value) {
    memtable.put(key, value);
    if(memtable.isFull()) {
        string SSFilename = this->directoryName + "/sst_" + to_string(sst_counter) + ".bin";
        vector<pair<string, string>> entries = memtable.getEntries();
        sstable.flush(SSFilename, entries);
        this->filenames.push_back(SSFilename);
        sst_counter+=1;
        memtable.clear();
    }
}