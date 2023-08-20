#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>
#include "MainScreen.h";
#include "search_saveFavorList.h"

using namespace std;
using namespace sf;

Trie dictrie[5];

int main()
{// TEST PUSH LÊN GIT
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	dictrie[0].readDatasetToTrie("Data/EngEng/document.txt");
	dictrie[1].readDatasetToTrie("Data/EngVie/document.txt");
	dictrie[2].readDatasetToTrie("Data/VieEng/document.txt");
	dictrie[3].readDatasetToTrie("Data/Slang/document.txt");
	dictrie[4].readDatasetToTrie("Data/Emoji/document.txt");
	// 0:engeng 1:engvvie 2:vieeng 3:slang 4:emoji
	Trie test;
	Trie *trie= new Trie();
	Trie favor_trie;
	Trie history_trie;
	RenderWindow window(VideoMode(1740, 1080), "CS163-Dictionary", Style::Default);
	mainScreen(window, trie, favor_trie, history_trie);
	int i = 0;
	for (auto tr : dictrie) {
		if (tr.checkisChanged()) {
			string str = "";
			ofstream fout;
			if (i == 0) fout.open("Data/EngEng/document.txt");
			else if (i == 1) fout.open("Data/EngVie/Document.txt");
			else if (i == 2) fout.open("Data/VieEng/Document.txt");
			else if (i == 3) fout.open("Data/Slang/Document.txt");
			else if (i == 4) fout.open("Data/Emoji/Document.txt");
			if (fout.is_open()) display(tr.getRoot(), str, fout);
			fout.close();
		}
		dictrie[i].clearAll();
		i++;
	}
	favor_trie.clearAll();
	history_trie.clearAll();
	return 0;
}
