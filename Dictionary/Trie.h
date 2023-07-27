#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>

using namespace std;
using namespace sf;

const int sizee = 128;

class TrieNode {
public:
    vector<TrieNode*> children;
    vector<string> meaning;
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

public:
    Trie() {
        root = new TrieNode();
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
        cur->isFavorite = false;
        if (def_is_exist(cur->meaning, meaning)) cur->meaning.push_back(meaning);
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
        string line;
        while (getline(file, line, '\n')) {

            int i = 0;
            string word = "", meaning = "";
            while (line[i] != '\0') {
                if (line[i] != '\t') word += line[i];
                else break;
                i++;
            }
            i++;
            while (line[i] != '\0') {
                meaning += line[i];
                i++;
            }
            insertWord(word, meaning);
        }
        file.close();
    }

    void clearAll() {
        clearTrie(root);
        root = new TrieNode();
    }

private:
    bool removeOrigin(TrieNode* node, const string& word, int index) {
        if (index == word.length()) {
            if (!node->isEndOfWord) {
                return false;
            }
            node->isEndOfWord = false;
            node->meaning.clear();
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
