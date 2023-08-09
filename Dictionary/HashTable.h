#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>
using namespace std;
const int TABLE_SIZE = 1001;
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
        unsigned long long hashValue = 0;
        unsigned long long power = 1;
        for (char ch : s) {
            hashValue = (hashValue + (ch - 'a' + 1) * power) % TABLE_SIZE;
            power = (power * BASE) % TABLE_SIZE;
        }
        return hashValue;
    }
    void insert(const string& key) {
        unsigned long long hashValue = hashString(key);
        int index = hashValue % TABLE_SIZE;

        table[index].push_back(key);
    }
    bool get(const string& key) {
        unsigned long long hashValue = hashString(key);
        int index = hashValue % TABLE_SIZE;

        for (auto entry : table[index]) {
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