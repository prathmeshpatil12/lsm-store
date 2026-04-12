#pragma once
#include <string>
#include <fstream>
#include <functional>

class WAL {
private:
    std::ofstream log_file;

public:
    WAL(const std::string& filename);
    ~WAL();

    void append(const std::string& key, const std::string& value);

    void recover(const std::string& filename, 
                 std::function<void(std::string, std::string)> callback);
};