#pragma once
#include "Trie.h"

//-----------------Function--------------------------
void submitAdding(string word, string def, string typeDictionary, Trie& trie);

//-----------------Draw Scene--------------------------
void addNewWordScreen(RenderWindow& window, string typeDictionary, Trie& trie, Trie& favor_trie);