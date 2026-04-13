#include <iostream>
#include "bloom.h"

using namespace std;

int main() {
    BloomFilter bloomFilter(100);
    bloomFilter.add("apple");
    bloomFilter.add("banana");
    bloomFilter.add("carrot");

    cout << bloomFilter.mayContain("apple") << endl;
    cout << bloomFilter.mayContain("dog") << endl;
    cout << bloomFilter.mayContain("carrot") << endl;
    
}