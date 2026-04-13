#include "wal.h"
#include <iostream>

using namespace std;

// opens the log file in append mode
WAL::WAL(const string& filename) {
    this->fileName = filename;
    log_file.open(filename, ios::app);
    if (!log_file.is_open()) {
        cerr << "Error: could not open WAL file" << endl;
    }
}

// closes the log file
WAL::~WAL() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

// writes one entry to the log file
void WAL::append(const string& key, const string& value) {
    log_file << key << "=" << value << "\n";
    log_file.flush();
}


// Recovers the logs
void WAL::recover(const string& filename, function<void(string, string)> callback) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No WAL file found, starting fresh" << endl;
        return;
    }

    string line = "";
    int count = 0;
    while (getline(file, line)) {
        size_t sep = line.find('=');

        if(sep == string::npos) {
            continue;
        }

        string key = line.substr(0, sep);
        string value = line.substr(sep+1);

        callback(key, value);
        count += 1;
    }
    cout << "Recovered " << count << " entries from WAL" << endl;
}

void WAL::clear() {
    if (log_file.is_open()) {
        log_file.close();
    }
    log_file.open(this->fileName, std::ios::trunc);
}
