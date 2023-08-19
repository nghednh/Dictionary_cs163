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
    int hashString(const string& s) {
        if (s[0] < 101) return s[0];
        return s[0] % TABLE_SIZE;
    }
    void insert(const string& key) {
        int hashValue = hashString(key);

        table[hashValue].push_back(key);
    }
    bool get(const string& key) {
        int hashValue = hashString(key);
        for (auto entry : table[hashValue]){
            if (entry == key) return true;
        }
        return false;
    }
};