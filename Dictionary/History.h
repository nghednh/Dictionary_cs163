#pragma once
#include "Trie.h"
void storeHistory(Trie& trie, vector<string>& historyStack, int mode);
void writeHistoryToFile(Trie& trie, vector<string>& historyStack, int mode);
void displayHistory(vector<string>& historyStack, int mode);

//-------------------UI-----------------
struct Object
{
	Sprite draw;
	Texture txt;
	FloatRect bound;
};

struct Info
{
	Font font;
	Text text;
	FloatRect bound;
	bool check = false;
	string s = "";
};

//-------------------Objects/Text to draw-----------------

Object createObject(string s, float x, float y);
Object* createObjectTest(string s, float x, float y);
Object createObject(string s);
Object* createObjectTest(string s);
Info createInfo(string s, float x, float y, float size);
Info createInfo(string s, string info, float x, float y, float size);
Info* createInfoTest(string s, string info, float x, float y, float size);

//-----------------Other features--------------------------

bool isHere(FloatRect& bound, Vector2f& mouse);
bool drawWhich(RenderWindow& window, Object a, Object b, Vector2f& mouse);
bool drawWhich(RenderWindow& window, Object* a, Object* b, Vector2f& mouse);
bool switchPage(FloatRect& bound, Vector2f& mouse, int k, int& page);
void changePos(Object* a, Object* b, float x, float y);
void changePos(Object* a, float x, float y);
void changePos(Info* a, float x, float y);
void texting(Info& text, Uint32 unicode, unsigned int limit);
void texting(Info*& text, Uint32 unicode, unsigned int limit);

//-----------------Draw Scene--------------------------
void searchScene(RenderWindow& window, int& page, int& mode, const float& scale);
void historyScene(vector<string>& historyStack, RenderWindow& window, int& page, int& mode, const float& scale);
void editDefScene(Trie& trie, RenderWindow& window, int& page, int& mode, const float& scale);