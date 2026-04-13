#include <iostream>
#include "db.h"

using namespace std;

int main() {
    // 1. create DB
    string dir = "mydata";
    DB db(dir);

    // 2. insert some keys
    // your code here...
    string k1 = "apple";
    string k2 = "banana";
    string k3 = "carrot";
    string k4 = "papaya";
    string k5 = "dog";
    string v1 = "1";
    string v2 = "2";
    string v3 = "3";
    string v4 = "4";
    string v5 = "5";
    db.put(k1, v1);
    db.put(k2, v2);
    db.put(k3, v3);
    db.put(k4, v4);
    db.put(k5, v5);

    // 3. get them back and print
    // your code here...
    string value1 = db.get(k3);
    cout << "carrot: " << value1 << endl;

    // key that doesn't exist
    string key1 = "mango";
    string value2 = db.get(key1);
    cout << "mango: " << value2 << endl;

    return 0;
}