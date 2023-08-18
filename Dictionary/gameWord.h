#pragma once
#include "MainScreen.h"

//-------------------Function-----------------
void wrapped_text(RectangleShape shape, Text& text);
void chooseWord(Trie*& trie, TrieNode*& tmp, TrieNode*& op1, TrieNode*& op2, TrieNode*& op3);

//-----------------Draw Scene--------------------------
void gameWord(RenderWindow& window, string typeDictionary, Trie* trie, Trie& favor_trie, Trie& history_trie);
