#include "wal.h"
#include <iostream>

using namespace std;

int main() {

    WAL wal("test.log");

    wal.append("apple", "1");
    wal.append("banana", "2");
    wal.append("carrot", "3");

    wal.recover("test.log", [](string key, string value) {
        cout << key << " : " << value << endl;  
    });

    return 0;
}