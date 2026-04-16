#include "compaction.h"
#include "../sstable/sstable.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

string Compaction::compact(vector<string> filenames, string outputFileName) {
    // step 1 - read all entries from all files
    // use map to automatically handle duplicates - newer files overwrite older ones
    map<string, string> merged;

    for (int i = 0; i < filenames.size(); i++) {
        SSTable sst;
        // we need to read ALL entries from a file, not just one key
        // add a readAll() method to SSTable
        vector<pair<string,string>> entries = sst.readAll(filenames[i]);
        for (auto& entry : entries) {
            merged[entry.first] = entry.second;  // newer files overwrite older
        }
    }

    // step 2 - map is already sorted by key
    // convert to vector of pairs
    vector<pair<string,string>> result(merged.begin(), merged.end());

    // step 3 - write to output file
    SSTable sst;
    sst.flush(outputFileName, result);

    cout << "Compacted " << filenames.size() 
         << " files into " << outputFileName << endl;

    return outputFileName;
}