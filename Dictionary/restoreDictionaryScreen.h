#pragma once
#include "Trie.h"
#include "MainScreen.h"

//-----------------Function--------------------------
void restoreDictionary (string typeDictionary);

//-----------------Draw Scene--------------------------
void restoreDictionaryScreen (RenderWindow& window, string typeDictionary, Trie& trie);
