# pragma once
#include<vector>

class SSTable {
    public:
    void flush(std::string filename, std::vector<std::pair<std::string, std::string>> entries);
    std::string get(std::string filename, std::string key);
    std::vector<std::pair<std::string, std::string>> readAll(std::string fileName);
};