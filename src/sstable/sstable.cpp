#include "sstable.h"
#include "../bloom/bloom.h"
#include <fstream>
#include <iostream>

using namespace std;

void SSTable::flush(string filename, vector<pair<string, string>> entries) {
    ofstream outputFile(filename, std::ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        return;
    }

    BloomFilter bloomFilter = BloomFilter(100);

    for(auto entry: entries) {
        string key = entry.first;
        string value = entry.second;
        bloomFilter.add(key);

        int key_len = key.size();
        outputFile.write(reinterpret_cast<const char*>(&key_len), sizeof(int));
        outputFile.write(key.c_str(), key.size());
        
        int val_len = value.size();
        outputFile.write(reinterpret_cast<const char*>(&val_len), sizeof(int));
        outputFile.write(value.c_str(), value.size());
    }
    
    int bloom_offset = outputFile.tellp();
    int bloom_size = 100;
    outputFile.write(reinterpret_cast<const char*>(&bloom_size), sizeof(int));
    for (int i = 0; i < bloom_size; i++) {
        char bit = bloomFilter.getBit(i);
        outputFile.write(&bit, sizeof(char));
    }
    outputFile.write(reinterpret_cast<const char*> (&bloom_offset), sizeof(int));
}


string SSTable::get(string filename, string key) {
    ifstream inputFile(filename, std::ios::binary);
    if(!inputFile.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        return "";
    }

    inputFile.seekg(-sizeof(int), ios::end);

    int bloom_offset;
    inputFile.read(reinterpret_cast<char*>(&bloom_offset), sizeof(int));

    // seek to bloom_offset
    inputFile.seekg(bloom_offset);

    int bloom_size;
    inputFile.read(reinterpret_cast<char*>(&bloom_size), sizeof(int));

    BloomFilter bloomFilter(bloom_size);
    for (int i = 0; i < bloom_size; i++) {
        char bit;
        inputFile.read(&bit, sizeof(char));
        bloomFilter.setBit(i, bit);
    }

    if (!bloomFilter.mayContain(key)) {
        return "";
    }

    // seek back to start
    inputFile.seekg(0, ios::beg);

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