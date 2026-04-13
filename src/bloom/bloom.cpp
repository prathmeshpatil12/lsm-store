#include "bloom.h"
#include <vector>
#include <iostream>

using namespace std;

int hash1(const std::string& key) {
    int hash = 0;
    for (char c : key) {
        hash = hash * 31 + c;
    }
    return abs(hash);
}

int hash2(const std::string& key) {
    int hash = 0;
    for (char c : key) {
        hash = hash * 37 + c;
    }
    return abs(hash);
}

BloomFilter::BloomFilter(int size) {
    this->size = size;
    bitArray = vector<bool> (size, 0);
}

void BloomFilter::add(string key) {
    int h1 = hash1(key) % size;
    int h2 = hash2(key) % size;

    for(int i=0; i<3; i++) {
        int position = (h1 + i * h2) % size;
        bitArray[position] = 1;
    }
}

bool BloomFilter::mayContain(string key) {
    int h1 = hash1(key) % size;
    int h2 = hash2(key) % size;

    for(int i=0; i<3; i++) {
        int position = (h1 + i * h2) % size;
        if(bitArray[position]==0) {
            return false;
        }
    }
    return true;
}