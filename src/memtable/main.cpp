#include<iostream>
#include "memtable.h"

using namespace std;

int main() {
    Memtable memtable("test.log");
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
    
    memtable.put(k1, v1);
    memtable.put(k2, v2);
    memtable.put(k3, v3);
    memtable.put(k4, v4);
    memtable.put(k5, v5);
    
    memtable.getAll();

    cout << memtable.isFull() << endl;
    return 0;
}