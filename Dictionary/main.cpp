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
//    //debug
//    Trie trie;
//    trie.readDatasetToTrie("words.txt");
//   /* cout << trie.searchWord("abaction") << endl;
//    cout << trie.searchWord("abactor") << endl;
//    cout << trie.searchWord("car") << endl;
//    cout << trie.searchWord("cat:))") << endl;
//    cout << trie.searchWord("dog") << endl;
//
//    cout << trie.partSearch("ab") << endl;
//    cout << trie.partSearch("ba") << endl;
//    cout << trie.partSearch("ca") << endl;*/
//	// Test UI history
	Trie trie;
	Trie favor_trie;
	trie.readDatasetToTrie("../Dictionary/EngEng/words.txt");
	int page = 1;
	int mode = 1;
	vector<string> historyStack;
	storeHistory(trie, historyStack, mode);
	RenderWindow window;
	Image icon;
	float scale = 1.5f;
	window.create(VideoMode(1000.0f * scale, 750.0f * scale), "CS163-Dictionary", Style::Close);


	while (page > 0 && window.isOpen())
	{
		switch (page)
		{
		case 1:
		{
			search_addfavorite(window, trie, favor_trie);
			/*searchScene(window, page, mode, scale);*/
			break;
		}
		case 2:
		{
			historyScene(historyStack, window, page, mode, scale);
			break;
		}
		case 3:
		{editDefScene(trie, window, page, mode, scale);
			break;
		}
		case 4:
		{
			
			break;
		}
		case 5:
		{

			break;
		}
		case 6:
		{

			break;
		}
		case 7:
		{

			break;
		}
		case 8:
		{

			break;
		}
		case 9:
		{

			break;
		}
		case 11:
		{

			break;
		}
		case 13:
		{

			break;
		}
		default:
		{
			break;
		}
		}
	}
	storeHistory(trie, historyStack, mode);
	displayHistory(historyStack, mode);
	writeHistoryToFile(trie, historyStack, mode);
	return 0;
}