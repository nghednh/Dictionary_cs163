#pragma once
#include "Trie.h"
#include "MainScreen.h"

//-----------------Function--------------------------
void restoreDictionary(string& typeDictionary, Trie& trie);

//-----------------Draw Scene--------------------------
void restoreDictionaryScreen(RenderWindow& window, string& typeDictionary, Trie& trie, Trie& favor_trie, Trie& history_trie);
