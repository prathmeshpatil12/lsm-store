#include <iostream>
#include "db.h"

using namespace std;

int main() {
    string dir = "mydata";
    DB db(dir);

    // insert enough to trigger multiple flushes and compaction
    for (int i = 0; i < 10000; i++) {
        string k = "key" + to_string(i);
        string v = "value" + to_string(i);
        db.put(k, v);
    }

    cout << "Inserted 10000 keys" << endl;

    // test reads
    string k1 = "key5";
    cout << "key5: " << db.get(k1) << endl;

    string k2 = "key50";
    cout << "key50: " << db.get(k2) << endl;

    string k3 = "mango";
    cout << "mango: " << db.get(k3) << endl;

    return 0;
}