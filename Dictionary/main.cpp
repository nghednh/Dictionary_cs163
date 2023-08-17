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
#include "search_saveFavorList.h"
#include "randomview.h"
using namespace std;
using namespace sf;

Trie dictrie[5];

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	dictrie[0].readDatasetToTrie("Data/EngVie/document.txt");
	dictrie[1].readDatasetToTrie("Data/EngVie/document.txt");
	dictrie[2].readDatasetToTrie("Data/VieEng/document.txt");
	dictrie[3].readDatasetToTrie("Data/Slang/document.txt");
	dictrie[4].readDatasetToTrie("Data/Emoji/document.txt");

	Trie trie;
	Trie favor_trie;
	Trie history_trie;
	RenderWindow window(VideoMode(1740, 1080), "CS163-Dictionary", Style::Default);
	mainScreen(window, trie, favor_trie, history_trie);

	for (auto tr : dictrie) {
		if (trie.checkisChanged()) {
			cout << endl << endl << 1;
			string str = "";
			ofstream fout;
			fout.open("Data/nghe.txt"); // luu tam thoi
			if (fout.is_open()) display(trie.getRoot(), str, fout);
			fout.close();
		}
	}
	trie.clearAll();
	favor_trie.clearAll();
	history_trie.clearAll();
	return 0;
}
