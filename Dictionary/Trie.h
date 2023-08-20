#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>
#include "random.h"
#include "HashTable.h"

using namespace std;
using namespace sf;

const int sizee = 128;


class TrieNode {
public:
    vector<TrieNode*> children;
    vector<string> meaning;
    vector<HashTable> hashTable;

    string word;
    bool isEndOfWord;
    bool isFavorite;

    TrieNode() {
        children = vector<TrieNode*>(sizee, nullptr);
        isEndOfWord = false;
        isFavorite = false;
    }   
};

class Trie {
private:
    TrieNode* root;
    bool isChanged;

public:
    Trie() {
        root = new TrieNode();
        isChanged = false;
    }
    bool checkisChanged() {
        return isChanged;
    }
    TrieNode* getRoot() {
        return root;
    }
    bool def_is_exist(vector<string> meaning, string s) {
        for (int i = 0; i < meaning.size(); i++) {
            if (meaning[i] == s) return false;
        }
        return true;
    }
    void insertWord(const string& word, const string& meaning) {
        TrieNode* cur = root;
        
        for (char c : word) {
            int index = c - ' ';
            if (cur->children[index] == nullptr) {
                cur->children[index] = new TrieNode();
            }
            cur = cur->children[index];
        }

        cur->isEndOfWord = true;
        cur->word = word;
        cur->isFavorite = false;
        if (def_is_exist(cur->meaning, meaning)) {
            cur->meaning.push_back(meaning);
            //Hash definition
            istringstream iss(meaning);
            string s;
            if (cur->hashTable.size() <= 5) {
                HashTable tmp;
                while (iss >> s) {
                    int t = (int)(s.size() - 1);
                    if ('a' > s[t] || s[t] > 'z') s.pop_back();
                    tmp.insert(s);
                }
                cur->hashTable.push_back(tmp);
            }
        }
    }

    bool searchWord(const string& word) {
        TrieNode* cur = root;

        for (char c : word) {
            int index = c - ' ';
            if (cur->children[index] == nullptr) {
                return false;
            }
            cur = cur->children[index];
        }

        return cur->isEndOfWord;
    }

    TrieNode* searchWordNode(const string& word) {
        TrieNode* cur = root;

        for (char c : word) {
            int index = c - ' ';
            if (cur->children[index] == nullptr) {
                return NULL;
            }
            cur = cur->children[index];
        }
        if (cur->isEndOfWord)
            return cur;
        else return NULL;
    }
    void replaceDefinition(string newDef, string word) {
        string tmpstr = "";
        TrieNode* tmp = searchWordNode(word);
        tmp->meaning.clear();
        for (int i = 0; i < newDef.length(); i++)
        {
            if (newDef[i] != ',') {
                tmpstr += newDef[i];
            }
            else tmpstr += newDef[i];
            tmp->meaning.push_back(tmpstr);
            tmpstr = "";
        }
    }
    bool partSearch(const string& prefix) {
        TrieNode* cur = root;

        for (char c : prefix) {
            int index = c - ' ';
            if (cur->children[index] == nullptr) {
                return false;
            }
            cur = cur->children[index];
        }

        return true;
    }

    bool removeWord(const string& word) {
        return removeOrigin(root, word, 0);
    }

    bool isEmpty(TrieNode* node) {
        for (TrieNode* child : node->children) {
            if (child != nullptr) {
                return false;
            }
        }
        return true;
    }

    void readDatasetToTrie(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Failed to open the file: " << filename << endl;
            return;
        }
        while (!file.eof()) {
            string word = "";
            string meaning = "";
            getline(file, word, '\t');
            getline(file, meaning, '\n');
            insertWord(word, meaning);
        }
        file.close();
    }

    void clearAll() {
        clearTrie(root);
        root = new TrieNode();
    }
    bool compareRan();
    TrieNode *getRandomWordTrue() {
        TrieNode* cur = root;
        TrieNode* pre = nullptr;
        int n = randominrange2(150,200);
        for (int i = 0; i < n; i++) {
            int m = 0;
            if (compareRan()) m = randominrange2(65, 90);
            else m = randominrange2(1, 90);
            if (cur->children[m])
            {
                cur = cur->children[m];
                if (cur->isEndOfWord) pre = cur;
            }
        }
        if (pre != nullptr) {
            return pre;
        }
        else {
            return getRandomWordTrue();
        }
    }
    TrieNode* getRandomWordWrong(TrieNode* x, TrieNode* y, TrieNode*z) {
        TrieNode* cur = root;
        TrieNode* pre = nullptr;
        int n = randominrange2(150,200);
        for (int i = 0; i < n; i++) {
            int m = 0;
            if (compareRan()) m = randominrange2(65, 90);
            else m = randominrange2(1, 90);
            if (cur->children[m])
            {
                cur = cur->children[m];
                if (cur->isEndOfWord) pre = cur;
            }
        }
        if (pre != nullptr && pre != x && pre != y && pre != z) {
            return pre;
        }
        else {
            return getRandomWordWrong(x,y,z);
        }
    }
private:
    bool removeOrigin(TrieNode* node, const string& word, int index) {
        if (index == word.length()) {
            if (!node->isEndOfWord) {
                return false;
            }
            node->isEndOfWord = false;
            node->word.clear();
            node->meaning.clear();
            node->hashTable.clear();
            isChanged = true;
            return isEmpty(node);
        }

        int charIndex = word[index] - ' ';
        if (node->children[charIndex] == nullptr) {
            return false;
        }

        bool shouldDelete = removeOrigin(node->children[charIndex], word, index + 1);

        if (shouldDelete) {
            delete node->children[charIndex];
            node->children[charIndex] = nullptr;
            return isEmpty(node);
        }

        return false;
    }

    void clearTrie(TrieNode* node) {
        if (!node) {
            return;
        }

        for (TrieNode* child : node->children) {
            clearTrie(child);
        }

        delete node;
    }
};
