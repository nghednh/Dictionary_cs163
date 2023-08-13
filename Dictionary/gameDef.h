#pragma once
#include "MainScreen.h"

//-------------------Function-----------------
void wrapped_text(RectangleShape shape, Text& text);

//-----------------Draw Scene--------------------------
void gameDef(RenderWindow& window, string typeDictionary, Trie& trie, Trie& favor_trie);