#include "db.h"

using namespace std;

DB::DB(string& directoryName) : memtable(directoryName + "/wal.log"), sst_counter(0), directoryName(directoryName), compaction_counter(0) {
    filesystem::create_directories(directoryName);
};

void DB::put(string &key, string &value) {
    memtable.put(key, value);
    // cout << "isFull: " << memtable.isFull() << endl;
    if(memtable.isFull()) {
        // cout << "Flushing to SSTable..." << endl;
        string SSFilename = this->directoryName + "/sst_" + to_string(sst_counter) + ".bin";
        // cout << "Getting entries..." << endl;
        vector<pair<string, string>> entries = memtable.getEntries();
        // cout << "Got " << entries.size() << " entries" << endl;
        // cout << "Flushing to: " << SSFilename << endl;
        sstable.flush(SSFilename, entries);
        // cout << "Flush done" << endl;
        this->l0_files.push_back(SSFilename);
        sst_counter+=1;
        memtable.clear();

        if (l0_files.size() >= L0_COMPACTION_TRIGGER) {
            runCompaction();
        }
    }
    // cout << "Put done" << endl;
}

string DB::get(string& key) {
    // cout << "Calling get" << endl;
    // cout << "Calling memtable.get" << endl;
    string val = memtable.get(key);
    // cout << "val : " << val << endl;
    if (val != "") 
        return val;
    
    // cout << "Searching in sstable" << endl;
    for (int i = l0_files.size() - 1; i >= 0; i--) {
        string val = sstable.get(l0_files[i], key);
        // cout << "val : " << val << endl;
        if (val != "") return val;
    }

    for (int i = l1_files.size() - 1; i >= 0; i--) {
        string val = sstable.get(l1_files[i], key);
        if (val != "") return val;
    }
    return "";
}

void DB::runCompaction() {
    if (l0_files.size() < 2) {
        return;
    }

    // generate output filename for compacted file
    string output = directoryName + "/l1_" + 
                   to_string(compaction_counter++) + ".bin";

    // merge all l0 files into one l1 file
    string compacted = compactor.compact(l0_files, output);

    // delete old l0 files
    for (auto& f : l0_files) {
        filesystem::remove(f);
    }

    // clear l0, add new file to l1
    l0_files.clear();
    l1_files.push_back(compacted);

    cout << "Compaction done. L1 now has " 
         << l1_files.size() << " files" << endl;

    if (l1_files.size() >= L1_COMPACTION_TRIGGER) {
        runL1Compaction();
    }
}

void DB::runL1Compaction() {
    if (l1_files.size() < 2) {
        return;
    }

    string output = directoryName + "/l1_" +
                   to_string(compaction_counter++) + ".bin";

    string compacted = compactor.compact(l1_files, output);

    for (auto& f : l1_files) {
        filesystem::remove(f);
    }

    l1_files.clear();
    l1_files.push_back(compacted);

    cout << "L1 major compaction done. L1 now has "
         << l1_files.size() << " file" << endl;
}