#pragma once
#include "MainScreen.h"

//-------------------Function-----------------
void wrapped_text(RectangleShape shape, Text& text);
void chooseDef(Trie*& trie, TrieNode*& tmp);

//-----------------Draw Scene--------------------------
void gameDef(RenderWindow& window, string typeDictionary, Trie* trie, Trie& favor_trie, Trie& history_trie);
