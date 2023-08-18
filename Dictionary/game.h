#pragma once
#include "MainScreen.h"
#include "gameDef.h"
#include "gameWord.h"

//-------------------Function-----------------
void wrapped_text(RectangleShape shape, Text& text);
string buffer(TrieNode*& tmp);

//-----------------Draw Scene--------------------------
void gameMenu(RenderWindow& window, string typeDictionary, Trie* trie, Trie& favor_trie, Trie& history_trie);
