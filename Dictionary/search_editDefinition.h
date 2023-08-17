#pragma once
#include "Trie.h"

void wrapped_text(RectangleShape shape, Text& text);

//-----------------Draw Scene--------------------------
void search_editDefinition(RenderWindow& window, Trie* trie, string typeDictionary, Trie& favor_trie, Trie& history_trie, string word, int& state);