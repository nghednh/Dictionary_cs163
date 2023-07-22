//
//#include "History.h"
//void storeHistory(Trie& trie, vector<string>& historyStack, int mode,string searching) {
//	string  line, tmp = "";
//	ifstream read;
//	for (int i = 0; i < trie.searchWordNode(searching)->meaning.size(); i++) {
//		tmp += trie.searchWordNode(searching)->meaning[i];
//	}
//		switch (mode) {
//		case 1: read.open("EngEng/history.txt"); break;
//		case 2: read.open("EngViet/history.txt"); break;
//		case 3:read.open("VietEng/history.txt"); break;
//		case 4:read.open("Emoji/history.txt"); break;
//		case 5:read.open("Slang/history.txt"); break;
//		default:break;
//		}historyStack.push_back(searching + tmp);
//		while (getline(read, line)) {
//			historyStack.push_back(line);
//		}
//	read.close();
//}
//
//void writeHistoryToFile(Trie& trie, vector<string>& historyStack, int mode) {
//	ofstream write;
//	switch (mode) {
//	case 1: write.open("EngEng/history.txt"); break;
//	case 2: write.open("EngViet/history.txt"); break;
//	case 3:write.open("VietEng/history.txt"); break;
//	case 4:write.open("Emoji/history.txt"); break;
//	case 5:write.open("Slang/history.txt"); break;
//	default:break;
//	}
//	for (int i = 0; i < historyStack.size(); i++) {
//		if (i != historyStack.size() - 1)
//			write << historyStack[i] << endl;
//		else write << historyStack[i];
//	}
//	write.close();
//	historyStack.clear();
//}
//void displayHistory(vector<string>& historyStack, int mode) {
//	for (int i = historyStack.size() - 1; i >= 0; i--) {
//		cout << historyStack[i] << endl;
//	}
//}
//
////-------------------UI-----------------
//Object createObject(string s, float x, float y)
//{
//	Object me;
//	me.txt.loadFromFile(s);
//	me.draw.setTexture(me.txt);
//	me.draw.setPosition(x, y);
//	me.bound = me.draw.getGlobalBounds();
//	return me;
//}
//
//Object* createObjectTest(string s, float x, float y)
//{
//	Object* me = new Object;
//	me->txt.loadFromFile(s);
//	me->draw.setTexture(me->txt);
//	me->draw.setPosition(x, y);
//	me->bound = me->draw.getGlobalBounds();
//	return me;
//}
//
//Object createObject(string s)
//{
//	Object me;
//	me.txt.loadFromFile(s);
//	me.draw.setTexture(me.txt);
//	me.bound = me.draw.getGlobalBounds();
//	return me;
//}
//
//Object* createObjectTest(string s)
//{
//	Object* me = new Object;
//	me->txt.loadFromFile(s);
//	me->draw.setTexture(me->txt);
//	me->bound = me->draw.getGlobalBounds();
//	return me;
//}
//bool isHere(FloatRect& bound, Vector2f& mouse)
//{
//	return bound.contains(mouse);
//}
//
//Info createInfo(string s, float x, float y, float size)
//{
//	Info a;
//	a.font.loadFromFile(s);
//	a.text.setFont(a.font);
//	a.text.setCharacterSize(size);
//	a.text.setPosition(x, y);
//	a.text.setFillColor(Color(46, 68, 112, 255));
//	a.bound = a.text.getGlobalBounds();
//	return a;
//}
//
//Info createInfo(string s, string info, float x, float y, float size)
//{
//	Info a;
//	a.font.loadFromFile(s);
//	a.text.setFont(a.font);
//	a.text.setCharacterSize(size);
//	a.text.setPosition(x, y);
//	a.text.setFillColor(Color(46, 68, 112, 255));
//	a.text.setString(info);
//	a.bound = a.text.getGlobalBounds();
//	return a;
//}
//
//Info* createInfoTest(string s, string info, float x, float y, float size)
//{
//	Info* a = new Info;
//	a->font.loadFromFile(s);
//	a->text.setFont(a->font);
//	a->text.setCharacterSize(size);
//	a->text.setPosition(x, y);
//	a->text.setFillColor(Color(46, 68, 112, 255));
//	a->text.setString(info);
//	a->bound = a->text.getGlobalBounds();
//	return a;
//}
//
//bool drawWhich(RenderWindow& window, Object a, Object b, Vector2f& mouse)
//{
//	if (isHere(a.bound, mouse))
//	{
//		window.draw(a.draw);
//		return true;
//	}
//	window.draw(b.draw);
//	return false;
//}
//
//bool drawWhich(RenderWindow& window, Object* a, Object* b, Vector2f& mouse)
//{
//	if (isHere(a->bound, mouse))
//	{
//		window.draw(a->draw);
//		return true;
//	}
//	window.draw(b->draw);
//	return false;
//}
//
//bool switchPage(FloatRect& bound, Vector2f& mouse, int k, int& page)
//{
//	if (isHere(bound, mouse))
//	{
//		page = k;
//		return true;
//	}
//	return false;
//}
//
//void changePos(Object* a, Object* b, float x, float y)
//{
//	a->draw.setPosition(x, y);
//	a->bound = a->draw.getGlobalBounds();
//	b->draw.setPosition(x, y);
//	b->bound = b->draw.getGlobalBounds();
//}
//
//void changePos(Object* a, float x, float y)
//{
//	a->draw.setPosition(x, y);
//	a->bound = a->draw.getGlobalBounds();
//}
//
//void changePos(Info* a, float x, float y)
//{
//	a->text.setPosition(x, y);
//	a->bound = a->text.getGlobalBounds();
//}
//
//void texting(Info& text, Uint32 unicode, unsigned int limit)
//{
//	if (text.check && (text.s.size() < limit || unicode == 8))
//	{
//		if (unicode == 8)
//		{
//			if (!text.s.empty())
//				text.s.pop_back();
//		}
//		else
//		{
//			text.s += unicode;
//		}
//		text.text.setString(text.s);
//	}
//}
//
//void texting(Info*& text, Uint32 unicode, unsigned int limit)
//{
//	if (text->check && (text->s.size() < limit || unicode == 8))
//	{
//		if (unicode == 8)
//		{
//			if (!text->s.empty())
//				text->s.pop_back();
//		}
//		else
//		{
//			text->s += unicode;
//		}
//		text->text.setString(text->s);
//	}
//}
//
////-------------------Scene-----------------
//void searchScene(RenderWindow& window, int& page, int& mode, const float& scale)
//{
//	bool entered = 0;
//	Object screen = createObject("content/scene.png");
//	Object searchBar = createObject("content/searchBar.png", 110.0f * scale, 240.0f * scale);
//	Object his1 = createObject("content/His1.png", 780.0f * scale, 230.0f * scale);
//	Object his2 = createObject("content/His2.png", 780.0f * scale, 230.0f * scale);
//	Object edit1 = createObject("content/Edit1.png", 760.0f * scale, 310.0f * scale);
//	Object edit2 = createObject("content/Edit2.png", 760.0f * scale, 310.0f * scale);
//	Info search = createInfo("content/Oswald-Light.ttf", "Search", 120.0f * scale, 245.0f * scale, 26.25f * scale);
//	Info word = createInfo("content/Oswald-Light.ttf", " ", 110.0f * scale, 245.0f * scale, 30.25f * scale);
//	Event event;
//
//	while (window.isOpen() && page == 1)
//	{
//		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
//		while (window.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case Event::Closed:
//			{
//				window.close();
//				break;
//			}
//			case Event::MouseButtonReleased:
//			{
//				if (event.mouseButton.button == Mouse::Left)
//				{
//					if (isHere(search.bound, mouse))
//						search.check = true;
//					if (isHere(his1.bound, mouse)) {
//						page = 2;
//						return;
//					}
//					if (isHere(edit1.bound, mouse)) {
//						page = 3;
//						return;
//					}
//				}
//			}
//			break;
//			case Event::TextEntered:
//			{
//				texting(word, event.text.unicode, 15);
//				word.s += event.text.unicode;
//				word.text.setString(word.s);
//				break; }
//			default:
//				break;
//
//			}
//
//			window.clear();
//			window.draw(screen.draw);
//			window.draw(searchBar.draw);
//			drawWhich(window, his1, his2, mouse);
//			drawWhich(window, edit1, edit2, mouse);
//			window.draw(search.text);
//
//			window.display();
//		}
//	}
//}
//void historyScene(vector<string> historyStack, RenderWindow& window, int& page, int& mode, const float& scale) {
//	historyStack.push_back("");
//	//bool entered = 0;
//	Object screen = createObject("content/historyScene.png");
//	Object return1 = createObject("content/return.png", 80.0f * scale, 90.0f * scale);
//	Object return2 = createObject("content/return1.png", 80.0f * scale, 90.0f * scale);
//	Object left = createObject("content/left.png", 632.0f * scale, 644.0f * scale);
//	Object left_point = createObject("content/left_point.png", 632.0f * scale, 644.0f * scale);
//	Object left_valid = createObject("content/left_valid.png", 632.0f * scale, 644.0f * scale);
//	Object right = createObject("content/right.png", 650.0f * scale, 644.0f * scale);
//	Object right_point = createObject("content/right_point.png", 650.0f * scale, 644.0f * scale);
//	Object right_valid = createObject("content/right_valid.png", 650.0f * scale, 644.0f * scale);
//	Event event;
//	int change = 0, count = historyStack.size() + 1;
//	bool trigger_page = true;
//	Info* inf[8];
//	for (int i = 0; i < 8; i++) {
//		inf[i] = createInfoTest("content/Oswald-Light.ttf", "demo_text", 160.0f * scale, (210.0f + 50.f * i) * scale, 25.0f * scale);
//	}
//	while (window.isOpen() && page == 2)
//	{
//		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
//		while (window.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case Event::Closed:
//			{
//				window.close();
//				break;
//			}
//			case Event::MouseButtonReleased:
//			{
//				if (event.mouseButton.button == Mouse::Left)
//				{
//
//					if (isHere(return1.bound, mouse)) {
//						page = 1;
//						return;
//					}
//					if (isHere(right.bound, mouse) && change <= count - 8)
//					{
//						trigger_page = true;
//						change += 8;
//					}
//					if (isHere(left.bound, mouse) && change != 0)
//					{
//						trigger_page = true;
//						change -= 8;
//					}
//				}
//				break;
//			}
//			default: break;
//			}
//			window.clear();
//			window.draw(screen.draw);
//			drawWhich(window, return2, return1, mouse);
//			if (change == 0 && change >= count - 8)
//			{
//				window.draw(right.draw);
//				window.draw(left.draw);
//			}
//			else if (change == 0)
//			{
//				window.draw(left.draw);
//				drawWhich(window, right_point, right_valid, mouse);
//			}
//			else if (change >= count - 8)
//			{
//				window.draw(right.draw);
//				drawWhich(window, left_point, left_valid, mouse);
//			}
//			else
//			{
//				drawWhich(window, right_point, right_valid, mouse);
//				drawWhich(window, left_point, left_valid, mouse);
//			}
//			if (trigger_page)
//			{
//				int index = 0;
//				for (int i = 0; i < change; i++)
//				{
//					index++;
//				}
//				for (int i = 0; i < 8; i++)
//				{
//					if (historyStack[index] != "")
//					{
//						inf[i]->text.setString(historyStack[index]);
//						index++;
//					}
//					else
//					{
//						inf[i]->text.setString("");
//					}
//				}
//				trigger_page = false;
//			}
//			for (int i = 0; i < 8; i++)
//			{
//				if (inf[i]->text.getString() == "")
//					break;
//				window.draw(inf[i]->text);
//			}
//			window.display();
//		}
//
//	}for (int i = 0; i < 8; i++)
//	{
//		delete inf[i];
//	}
//}
//void editDefScene(Trie& trie, RenderWindow& window, int& page, int& mode, const float& scale) {
//	bool entered1 = 0;
//	int ableEdit = 0;
//	Object screen = createObject("content/editScene.png");
//	Object return1 = createObject("content/return.png", 80.0f * scale, 90.0f * scale);
//	Object return2 = createObject("content/return1.png", 80.0f * scale, 90.0f * scale);
//	Object searchBar = createObject("content/searchBar.png", 150.0f * scale, 210.0f * scale);
//	Info search = createInfo("content/Oswald-Light.ttf", "Please Enter The Edit Word", 160.0f * scale, 213.0f * scale, 26.25f * scale);
//	Info enterEdit = createInfo("content/Oswald-Light.ttf", "New Definition", 475.0f * scale, 430.0f * scale, 26.25f * scale);
//	Object canEdit = createObject("content/canEdit.png", 450.0f * scale, 350.0f * scale);
//	Object cannotEdit = createObject("content/cannotEdit.png", 450.0f * scale, 350.0f * scale);
//	Object ok1 = createObject("content/ok2.png", 620.0f * scale, 510.0f * scale);
//	Object ok2 = createObject("content/ok1.png", 620.0f * scale, 510.0f * scale);
//	Object ok3 = createObject("content/ok2.png", 540.0f * scale, 510.0f * scale);
//	Object ok4 = createObject("content/ok1.png", 540.0f * scale, 510.0f * scale);
//	Object return3 = createObject("content/return2.png", 460.0f * scale, 510.0f * scale);
//	Object return4 = createObject("content/return3.png", 460.0f * scale, 510.0f * scale);
//	Event event;
//	while (window.isOpen() && page == 3)
//	{
//		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
//
//		while (window.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case Event::Closed:
//			{
//				window.close();
//				break;
//			}
//			case Event::MouseButtonReleased:
//			{
//				if (event.mouseButton.button == Mouse::Left)
//				{
//
//					if (isHere(return1.bound, mouse)) {
//						page = 1;
//						return;
//					}
//					if (isHere(search.bound, mouse))
//					{
//						search.check = true;
//						enterEdit.check = false;
//					}
//
//					if (ableEdit == 1) {
//						if (isHere(enterEdit.bound, mouse))
//						{
//							enterEdit.check = true;
//							search.check = false;
//						}
//						if (isHere(ok1.bound, mouse)) {
//							if (trie.searchWord(search.s) && ableEdit == 1) {
//								trie.replaceDefinition(" " + enterEdit.s, search.s);
//							};
//							page = 3;
//							return;
//						}
//						if (isHere(return3.bound, mouse)) {
//							page = 3;
//							return;
//						}
//					}
//					if (ableEdit == 2) {
//						if (isHere(ok3.bound, mouse)) {
//							page = 3;
//							return;
//						}
//					}
//				}
//			}break;
//			case Event::TextEntered:
//			{if (!Keyboard::isKeyPressed(Keyboard::Return))
//				texting(search, event.text.unicode, 100);
//			else
//				entered1 = 1;
//			if (ableEdit == 1)
//				texting(enterEdit, event.text.unicode, 100);
//			break;
//			}
//			default: break;
//			}
//
//			window.clear();
//			window.draw(screen.draw);
//			//	modeBar(trie, window, scale, mouse,event);
//			window.draw(searchBar.draw);
//			window.draw(search.text);
//			if (isHere(return1.bound, mouse))
//				window.draw(return2.draw);
//			else
//				window.draw(return1.draw);
//			window.draw(search.text);
//			if (ableEdit == 1) {
//				window.draw(canEdit.draw);
//				window.draw(enterEdit.text);
//				drawWhich(window, ok2, ok1, mouse);
//				drawWhich(window, return4, return3, mouse);
//			}
//			else if (ableEdit == 2) {
//				window.draw(cannotEdit.draw);
//				drawWhich(window, ok4, ok3, mouse);
//			}
//			window.display();
//		}
//		if (trie.searchWord(search.s) && entered1 == 1) {
//			ableEdit = 1;
//		}
//		else if (!trie.searchWord(search.s) && entered1 == 1)
//			ableEdit = 2;
//	}
//}