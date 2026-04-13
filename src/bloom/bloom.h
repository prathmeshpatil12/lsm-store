#pragma once
#include <vector>
#include <string>

class BloomFilter {
    private:
    std::vector<bool> bitArray;
    int size;

    public:
    BloomFilter(int size);
    void add(std::string key);
    bool mayContain(std::string key);
    bool getBit(int index);
    void setBit(int index, bool value);
};