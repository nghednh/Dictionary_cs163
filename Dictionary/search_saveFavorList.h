#pragma once
#include "Trie.h"

//-----------------Function--------------------------
void wrapped_text(RectangleShape shape, Text& text);
void searchWordsWithPrefix(TrieNode* node, string& prefix, vector<pair<string, string>>& result);
vector<pair<string, string>> searchPrefix(Trie* trie, string input);

//-----------------Draw Scene--------------------------
void search_addfavorite(RenderWindow& window, Trie* trie, string typeDictionary, Trie& favor_trie, Trie& history_trie);
void searchByDef(RenderWindow& window, Trie* trie, string typeDictionary, Trie& favor_trie, Trie& history_trie);
void display(TrieNode* root, string str, ofstream& fout);
void findDef(TrieNode* root, string input, vector<pair<string, string>>& ans);
