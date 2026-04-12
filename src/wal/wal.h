#pragma once
#include <string>
#include <fstream>

using namespace std;

class WAL {
private:
    ofstream log_file;

public:
    WAL(const string& filename);
    ~WAL();

    void append(const string& key, const string& value);

    void recover(const string& filename, function<void(string, string)> callback);
};