#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>

#include "MainScreen.h"

using namespace std;
using namespace sf;

int main()
{
	Trie trie;
	RenderWindow window(VideoMode(1920, 1080), "CS163-Dictionary", Style::Close);

	mainScreen(window, trie);

	trie.clearAll();
	return 0;
}