#include "History.h"
void storeHistory(Trie& trie, vector<string>& historyStack, int mode) {
	string searching, line;
	ifstream read;
	cout << " Please enter the word you want to search:";
	cin >> searching;
	if (trie.searchWord(searching)) {
		switch (mode) {
		case 1: read.open("History/EngEng.txt"); break;
		case 2: read.open("History/EngViet.txt"); break;
		case 3:read.open("History/Emoji.txt"); break;
		default:break;
		}historyStack.push_back(searching + trie.searchMeaning(searching)->meaning);
		while (getline(read, line)) {
			historyStack.push_back(line);
		}
	}
	read.close();
}

void writeHistoryToFile(Trie& trie, vector<string>& historyStack, int mode) {
	ofstream write;
	switch (mode) {
	case 1: write.open("History/EngEng.txt"); break;
	case 2: write.open("History/EngViet.txt"); break;
	case 3:write.open("History/Emoji.txt"); break;
	default:break;
	}
	for (int i = 0; i < historyStack.size(); i++) {
		if (i != historyStack.size() - 1)
			write << historyStack[i] << endl;
		else write << historyStack[i];
	}
	write.close();
	historyStack.clear();
}
void displayHistory(vector<string>& historyStack, int mode) {
	for (int i = historyStack.size() - 1; i >= 0; i--) {
		cout << historyStack[i] << endl;
	}
}

//-------------------UI-----------------
Object createObject(string s, float x, float y)
{
	Object me;
	me.txt.loadFromFile(s);
	me.draw.setTexture(me.txt);
	me.draw.setPosition(x, y);
	me.bound = me.draw.getGlobalBounds();
	return me;
}

Object* createObjectTest(string s, float x, float y)
{
	Object* me = new Object;
	me->txt.loadFromFile(s);
	me->draw.setTexture(me->txt);
	me->draw.setPosition(x, y);
	me->bound = me->draw.getGlobalBounds();
	return me;
}

Object createObject(string s)
{
	Object me;
	me.txt.loadFromFile(s);
	me.draw.setTexture(me.txt);
	me.bound = me.draw.getGlobalBounds();
	return me;
}

Object* createObjectTest(string s)
{
	Object* me = new Object;
	me->txt.loadFromFile(s);
	me->draw.setTexture(me->txt);
	me->bound = me->draw.getGlobalBounds();
	return me;
}
bool isHere(FloatRect& bound, Vector2f& mouse)
{
	return bound.contains(mouse);
}

Info createInfo(string s, float x, float y, float size)
{
	Info a;
	a.font.loadFromFile(s);
	a.text.setFont(a.font);
	a.text.setCharacterSize(size);
	a.text.setPosition(x, y);
	a.text.setFillColor(Color(46, 68, 112, 255));
	a.bound = a.text.getGlobalBounds();
	return a;
}

Info createInfo(string s, string info, float x, float y, float size)
{
	Info a;
	a.font.loadFromFile(s);
	a.text.setFont(a.font);
	a.text.setCharacterSize(size);
	a.text.setPosition(x, y);
	a.text.setFillColor(Color(46, 68, 112, 255));
	a.text.setString(info);
	a.bound = a.text.getGlobalBounds();
	return a;
}

Info* createInfoTest(string s, string info, float x, float y, float size)
{
	Info* a = new Info;
	a->font.loadFromFile(s);
	a->text.setFont(a->font);
	a->text.setCharacterSize(size);
	a->text.setPosition(x, y);
	a->text.setFillColor(Color(46, 68, 112, 255));
	a->text.setString(info);
	a->bound = a->text.getGlobalBounds();
	return a;
}

bool drawWhich(RenderWindow& window, Object a, Object b, Vector2f& mouse)
{
	if (isHere(a.bound, mouse))
	{
		window.draw(a.draw);
		return true;
	}
	window.draw(b.draw);
	return false;
}

bool drawWhich(RenderWindow& window, Object* a, Object* b, Vector2f& mouse)
{
	if (isHere(a->bound, mouse))
	{
		window.draw(a->draw);
		return true;
	}
	window.draw(b->draw);
	return false;
}

bool switchPage(FloatRect& bound, Vector2f& mouse, int k, int& page)
{
	if (isHere(bound, mouse))
	{
		page = k;
		return true;
	}
	return false;
}

void changePos(Object* a, Object* b, float x, float y)
{
	a->draw.setPosition(x, y);
	a->bound = a->draw.getGlobalBounds();
	b->draw.setPosition(x, y);
	b->bound = b->draw.getGlobalBounds();
}

void changePos(Object* a, float x, float y)
{
	a->draw.setPosition(x, y);
	a->bound = a->draw.getGlobalBounds();
}

void changePos(Info* a, float x, float y)
{
	a->text.setPosition(x, y);
	a->bound = a->text.getGlobalBounds();
}

void texting(Info& text, Uint32 unicode, unsigned int limit)
{
	if (text.check && (text.s.size() < limit || unicode == 8))
	{
		if (unicode == 8)
		{
			if (!text.s.empty())
				text.s.pop_back();
		}
		else
		{
			text.s += unicode;
		}
		text.text.setString(text.s);
	}
}

void texting(Info*& text, Uint32 unicode, unsigned int limit)
{
	if (text->check && (text->s.size() < limit || unicode == 8))
	{
		if (unicode == 8)
		{
			if (!text->s.empty())
				text->s.pop_back();
		}
		else
		{
			text->s += unicode;
		}
		text->text.setString(text->s);
	}
}

//-------------------Scene-----------------
void searchScene(RenderWindow& window, int& page, int& mode, const float& scale)
{
	bool entered = 0;
	Object screen = createObject("content/scene.png");
	Object searchBar = createObject("content/searchBar.png", 110.0f * scale, 240.0f * scale);
	Object his1 = createObject("content/His1.png", 780.0f * scale, 230.0f * scale);
	Object his2 = createObject("content/His2.png", 780.0f * scale, 230.0f * scale);
	Object edit1 = createObject("content/Edit1.png", 760.0f * scale, 310.0f * scale);
	Object edit2 = createObject("content/Edit2.png", 760.0f * scale, 310.0f * scale);
	Info search = createInfo("content/Oswald-Light.ttf", "Search", 120.0f * scale, 245.0f * scale, 26.25f * scale);
	Info word = createInfo("content/Oswald-Light.ttf", " ", 110.0f * scale, 245.0f * scale, 30.25f * scale);
	Event event;

	while (window.isOpen() && page == 1)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (isHere(search.bound, mouse))
						search.check = true;
					if (isHere(his1.bound, mouse)) {
						page = 2;
						return;
					}
					if (isHere(edit1.bound, mouse)) {
						page = 3;
						return;
					}
				}
			}
			break;
			case Event::TextEntered:
			{
				texting(word, event.text.unicode, 15);
				word.s += event.text.unicode;
				word.text.setString(word.s);
				break; }
			default:
				break;

			}

			window.clear();
			window.draw(screen.draw);
			window.draw(searchBar.draw);
			if (isHere(his2.bound, mouse) || entered)
				window.draw(his1.draw);
			else
				window.draw(his2.draw);
			if (isHere(edit2.bound, mouse) || entered)
				window.draw(edit1.draw);
			else
				window.draw(edit2.draw);
			window.draw(search.text);

			window.display();
		}
	}
}
void historyScene(vector<string>& historyStack, RenderWindow& window, int& page, int& mode, const float& scale) {
	bool entered = 0,trigger_page = 1;
	Object screen = createObject("content/historyScene.png");
	Object return1 = createObject("content/return.png", 80.0f * scale, 90.0f * scale);
	Object return2 = createObject("content/return1.png", 80.0f * scale, 90.0f * scale);
	Event event;
	vector<Info> history;
	/*for (int i = 0; i < historyStack.size(); i++) {
		history.push_back(createInfo("content/Oswald-Light.ttf", historyStack[i], 120.0f * scale, (245.0f + 50.0f * i) * scale, (26.25f + 4.75f * i) * scale));
	}*/
	while (window.isOpen() && page == 2)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					
					if (isHere(return1.bound, mouse)) {
						page = 1;
						return;
					}
				}
			}
			default: break;
			}
			window.clear();
			window.draw(screen.draw);
			/*for (int i = 0; i < history.size(); i++) {
				window.draw(history[i].text);
			}*/
			/*window.draw(history[0].text);
			window.draw(history[1].text);*/
			if (isHere(return1.bound, mouse) || entered)
				window.draw(return2.draw);
			else
				window.draw(return1.draw);
			window.display();

		}
	}
}
void editDefScene(Trie&trie, RenderWindow& window, int& page, int& mode, const float& scale) {
	bool entered = 0;
	Object screen = createObject("content/editScene.png");
	Object return1 = createObject("content/return.png", 80.0f * scale, 90.0f * scale);
	Object return2 = createObject("content/return1.png", 80.0f * scale, 90.0f * scale);
	Object searchBar = createObject("content/searchBar.png", 110.0f * scale, 240.0f * scale);
	Info search = createInfo("content/Oswald-Light.ttf", "Please Enter The Edit Word", 120.0f * scale, 245.0f * scale, 26.25f * scale);
	Event event;
	while (window.isOpen() && page == 3)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{

					if (isHere(return1.bound, mouse)) {
						page = 1;
						return;
					}
					if (isHere(search.bound, mouse))
						search.check = true;
				}
			}break;
			case Event::TextEntered:
			{
				texting(search, event.text.unicode, 10);
				break;
			}
			default: break;
			}
			window.clear();
			window.draw(screen.draw);
			window.draw(searchBar.draw);
			window.draw(search.text);
			if (isHere(return1.bound, mouse) || entered)
				window.draw(return2.draw);
			else
				window.draw(return1.draw);
			window.draw(search.text);
			window.display();
			
		}
	}
	cout << search.s;
}