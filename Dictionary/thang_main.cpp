//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//#include <cstdlib> 
//#include <ctime> 
//#include <sstream>
//#include "Trie.h"
//#include "History.h"
//using namespace std;
//using namespace sf;
//
//int main()
//{
//
//	Trie trie;
//	trie.readDatasetToTrie("words.txt");
//	int page = 1;
//	int mode = 1;
//	vector<string> historyStack;
//	storeHistory(trie, historyStack, mode);
//	RenderWindow window;
//	Image icon;
//	float scale = 1.5f;
//	window.create(VideoMode(1000.0f * scale, 750.0f * scale), "CS163-Dictionary", Style::Close);
//
//
//	while (page > 0 && window.isOpen())
//	{
//		switch (page)
//		{
//		case 1:
//		{
//			searchScene(window, page, mode, scale);
//			break;
//		}
//		case 2:
//		{
//			historyScene(historyStack, window, page, mode, scale);
//			break;
//		}
//		case 3:
//		{editDefScene(trie, window, page, mode, scale);
//		break;
//		}
//		case 4:
//		{
//
//			break;
//		}
//		case 5:
//		{
//
//			break;
//		}
//		case 6:
//		{
//
//			break;
//		}
//		case 7:
//		{
//
//			break;
//		}
//		case 8:
//		{
//
//			break;
//		}
//		case 9:
//		{
//
//			break;
//		}
//		case 11:
//		{
//
//			break;
//		}
//		case 13:
//		{
//
//			break;
//		}
//		default:
//		{
//			break;
//		}
//		}
//	}
//	storeHistory(trie, historyStack, mode);
//	displayHistory(historyStack, mode);
//	writeHistoryToFile(trie, historyStack, mode);
//	return 0;
//}
