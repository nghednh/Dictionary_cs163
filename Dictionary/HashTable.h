#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>
using namespace std;
const int TABLE_SIZE = 101;
const int BASE = 31;

// Hash table class
class HashTable {
private:
    vector<vector<string>> table;

public:
    HashTable() : table(TABLE_SIZE) {}
    vector<vector<string>> getTable() {
        return table;
    }
    unsigned long long hashString(const string& s) {
        if (s[0] < 101) return s[0];
        return s[0] % TABLE_SIZE;
    }
    void insert(const string& key) {
        unsigned long long hashValue = hashString(key);

        table[hashValue].push_back(key);
    }
    bool get(const string& key) {
        unsigned long long hashValue = hashString(key);
        /*int index = hashValue % TABLE_SIZE;*/

        for (auto entry : table[hashValue]){
            if (entry == key) return true;
        }
        return false;
    }
    // void remove(const string& key) {
    //     unsigned long long hashValue = hashString(key);
    //     int index = hashValue % TABLE_SIZE;

    //     for (auto it : table[index]) {
    //         if (it == key) {
    //             table[index].erase(it);
    //             break;
    //         }
    //     }
    // }
};