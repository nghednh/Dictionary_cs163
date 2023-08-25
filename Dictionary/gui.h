#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>

using namespace std;
using namespace sf;

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
Object createButton(int x, int y);
Object createObject(string s, int x, int y);
Object* createObjectTest(string s, int x, int y);
Object createObject(string s);
Object* createObjectTest(string s);
Info createInfo(string s, int x, int y, int size);
Info createInfo(string s, string info, int x, int y, int size);
Info* createInfoTest(string s, string info, int x, int y, int size);

//-----------------Other features--------------------------

bool isHere(FloatRect& bound, Vector2f& mouse);
bool drawWhich(RenderWindow& window, Object a, Object b, Vector2f& mouse);
bool drawWhich(RenderWindow& window, Object* a, Object* b, Vector2f& mouse);
bool switchPage(FloatRect& bound, Vector2f& mouse, int k, int& page);
void changePos(Object* a, Object* b, int x, int y);
void changePos(Object* a, int x, int y);
void changePos(Info* a, int x, int y);
void texting(Info& text, Uint32 unicode, unsigned int limit);
void texting(Info*& text, Uint32 unicode, unsigned int limit);
void setCursor(RenderWindow& window, vector<Sprite> button, bool& state, Vector2f& mouse, Cursor& cursor);