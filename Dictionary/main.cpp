#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>
#include "Trie.h"
#include "History.h"
#include "MainScreen.h";
using namespace std;
using namespace sf;

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	Trie trie;
	Trie favor_trie;
	RenderWindow window(VideoMode(1740, 1080), "CS163-Dictionary", Style::Default);
	mainScreen(window, trie, favor_trie);

	cout << trie.getRandomWordTrue()->word <<" " << trie.getRandomWordTrue()->meaning[0];
	TrieNode* x = trie.getRandomWordWrong(nullptr, nullptr, nullptr);
	cout << endl << endl <<x->word << x->meaning[0];

	trie.clearAll();
	favor_trie.clearAll();
	return 0;
}