#include "db.h"

using namespace std;

DB::DB(string& directoryName) : memtable(directoryName + "/wal.log"), sst_counter(0), directoryName(directoryName) {
    filesystem::create_directories(directoryName);
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

string DB::get(string& key) {
    string val = memtable.get(key);
    if (val != "") 
        return val;
    
    for (int i = filenames.size() - 1; i >= 0; i--) {
        string val = sstable.get(filenames[i], key);
        if (val != "") return val;
    }
    return "";
}