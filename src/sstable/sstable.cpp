#include "sstable.h"
#include <fstream>
#include <iostream>

using namespace std;

void SSTable::flush(string filename, vector<pair<string, string>> entries) {
    ofstream outputFile(filename, std::ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        return;
    }


    for(auto entry: entries) {
        string key = entry.first;
        string value = entry.second;

        int key_len = key.size();
        outputFile.write(reinterpret_cast<const char*>(&key_len), sizeof(int));
        outputFile.write(key.c_str(), key.size());
        
        int val_len = value.size();
        outputFile.write(reinterpret_cast<const char*>(&val_len), sizeof(int));
        outputFile.write(value.c_str(), value.size());
    }
}


string SSTable::get(string filename, string key) {
    ifstream inputFile(filename, std::ios::binary);
    if(!inputFile.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        return "";
    }

    while(inputFile.peek() != EOF) {
        int key_len;
        inputFile.read(reinterpret_cast<char*>(&key_len), sizeof(int));
        
        string current_key(key_len, '\0');
        inputFile.read(&current_key[0], key_len);


        int val_len;
        inputFile.read(reinterpret_cast<char*>(&val_len), sizeof(int));

        string current_value(val_len, '\0');
        inputFile.read(&current_value[0], val_len);

        // cout << key_len << " " << current_key << " " << val_len << " " << current_value << endl;

        if(current_key == key) {
            return current_value;
        }
    }
    return "";
}