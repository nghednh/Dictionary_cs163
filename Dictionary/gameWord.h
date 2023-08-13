#pragma once
#include "MainScreen.h"

//-------------------Function-----------------
void wrapped_text(RectangleShape shape, Text& text);

//-----------------Draw Scene--------------------------
void gameWord(RenderWindow& window, string typeDictionary, Trie& trie, Trie& favor_trie);