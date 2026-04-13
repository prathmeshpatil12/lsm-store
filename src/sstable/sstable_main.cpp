#include <iostream>
#include "sstable.h"
#include "../memtable/skiplist.h"

using namespace std;

int main() {
    // 1. create a skiplist and insert some keys
    SkipList sl;
    // insert 3 keys here...
    string k1 = "apple";
    string k2 = "banana";
    string k3 = "carrot";
    string k4 = "papaya";
    string k5 = "dog";
    string v1 = "1";
    string v2 = "2";
    string v3 = "3";
    string v4 = "4";
    string v5 = "5";
    sl.insert(k1, v1);
    sl.insert(k2, v2);
    sl.insert(k3, v3);
    sl.insert(k4, v4);
    sl.insert(k5, v5);

    // 2. get sorted entries
    auto entries = sl.getEntries();

    // 3. flush to disk
    SSTable sst;
    sst.flush("test.bin", entries);

    string value1 = sst.get("test.bin", "carrot");
    cout << "carrot: " << value1 << endl;

    // key that doesn't exist
    string value2 = sst.get("test.bin", "mango");
    cout << "mango: " << value2 << endl;

    return 0;
}