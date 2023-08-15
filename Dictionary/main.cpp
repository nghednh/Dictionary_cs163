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
using namespace std;
using namespace sf;

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	Trie trie;
	Trie favor_trie;
	Trie history_trie;
	RenderWindow window(VideoMode(1740, 1080), "CS163-Dictionary", Style::Default);
	mainScreen(window, trie, favor_trie, history_trie);



	//luu lai trie sau khi tat chuong trinh

	//if (trie.checkisChanged()) {
	//	cout <<endl<<endl<< 1;
	//	string str = "";
	//	ofstream fout;
	//	fout.open("Data/nghe.txt"); // luu tam thoi
	//	if (fout.is_open()) display(trie.getRoot(), str, fout);
	//	fout.close();
	//}
	trie.clearAll();
	favor_trie.clearAll();
	history_trie.clearAll();
	return 0;
}
