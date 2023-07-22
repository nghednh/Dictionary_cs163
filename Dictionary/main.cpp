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
	Trie trie;
	Trie favor_trie;
	RenderWindow window(VideoMode(1920, 1080), "CS163-Dictionary", Style::Default);

	mainScreen(window, trie, favor_trie);

	trie.clearAll();
	favor_trie.clearAll();
	return 0;
}