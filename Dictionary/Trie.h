#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>
#include "Trie.h"
using namespace std;
using namespace sf;

const int sizee = 128;

class TrieNode {
public:
    vector<TrieNode*> children;
    bool isEndOfWord;
    string meaning;

    TrieNode() {
        children = vector<TrieNode*>(sizee, nullptr);
        isEndOfWord = false;
        meaning = "";
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insertWord(const string& word, const string& meaning) {
        TrieNode* cur = root;

        for (char c : word) {
            int index = c - 'a';
            if (cur->children[index] == nullptr) {
                cur->children[index] = new TrieNode();
            }
            cur = cur->children[index];
        }

        cur->isEndOfWord = true;
        cur->meaning = meaning;
    }

    bool searchWord(const string& word) {
        TrieNode* cur = root;

        for (char c : word) {
            int index = c - 'a';
            if (cur->children[index] == nullptr) {
                return false;
            }
            cur = cur->children[index];
        }

        return cur->isEndOfWord;
    }

    bool partSearch(const string& prefix) {
        TrieNode* cur = root;

        for (char c : prefix) {
            int index = c - 'a';
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

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string word, meaning;

            if (iss >> word) {
                getline(iss, meaning);
                insertWord(word, meaning);
            }
        }

        file.close();
    }

    void clearAll() {
        clearTrie(root);
    }

private:
    // this function not return if the word is delete or not. it just use backtracking to remove the word
    bool removeOrigin(TrieNode* node, const string& word, int index) {
        if (index == word.length()) {
            if (!node->isEndOfWord) {
                return false;
            }
            node->isEndOfWord = false;
            node->meaning = "";
            return isEmpty(node);
        }

        int charIndex = word[index] - 'a';
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
