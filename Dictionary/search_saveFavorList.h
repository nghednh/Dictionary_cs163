#pragma once
#include "Trie.h"

//-----------------Function--------------------------
void wrapped_text(RectangleShape shape, Text& text);

//-----------------Draw Scene--------------------------
void search_addfavorite(RenderWindow& window, Trie &trie, string typeDictionary, Trie &favor_trie);
void searchByDef(RenderWindow& window, Trie &trie, string typeDictionary, Trie &favor_trie);
void display(TrieNode* root, string str, ofstream& fout);
void findDef(TrieNode* root, string input, vector<pair<string, string>>& ans);
