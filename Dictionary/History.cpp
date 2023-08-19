#include "viewListFavor.h"
#include "search_saveFavorList.h"
#include "History.h"
#include "gui.h"
#include "Operation.h"
//-------------------Scene-----------------
void historyScene(RenderWindow& window, string typedictionary, Trie * trie, Trie favor_trie, Trie history_trie) {
	vector<string> his_word;
	vector<string> his_def;
	ifstream fin;
	fin.open("Data/" + typedictionary + "/history.txt");
	while (!fin.eof()) {
		string word = "";
		string meaning = "";
		getline(fin, word, '\t');
		getline(fin, meaning, '\n');
		if (word != "") {
			his_word.push_back(word);
			his_def.push_back(meaning);
		}
	}
	fin.close();
	his_word.push_back("");
	his_def.push_back("");
	sf::RectangleShape rec_dis;
	rec_dis.setSize(sf::Vector2f(588, 450));
	rec_dis.setPosition(789, 375);
	Object book_dis = createObject("content/book_image.png", 798, 375);
	Object screen = createObject("content/historyScene.png");
	Object return1 = createObject("content/return.png", 150, 83);
	Object return2 = createObject("content/return1.png", 150, 83);
	Object left = createObject("content/left.png", 798, 966);
	Object left_point = createObject("content/left_point.png", 798, 966);
	Object left_valid = createObject("content/left_valid.png", 798, 966);
	Object right = createObject("content/right.png", 825, 966);
	Object right_point = createObject("content/right_point.png", 825, 966);
	Object right_valid = createObject("content/right_valid.png", 825, 966);
	Event event;
	int change = 0, count = his_word.size();
	bool trigger_page = true;
	Info* inf[8], * def[8];
	Object* bar_blue[8];
	Object* bar_red[8];
	for (int i = 0; i < 8; i++) {
		inf[i] = createInfoTest("content/Oswald-Light.ttf", "demo_text", 210, (323 + 75 * i), 38);
		bar_blue[i] = createObjectTest("content/bar1.png", 203, (315 + 75 * i));
		bar_red[i] = createObjectTest("content/bar2.png", 203, (315 + 75 * i));
		def[i] = createInfoTest("content/Oswald-Light.ttf", "demo_text", 814, 420, 25);
	}
	while (window.isOpen())
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
						for (int i = 0; i < 8; i++)
						{
							delete inf[i];
							delete bar_blue[i];
							delete bar_red[i];
							delete def[i];
						}
						his_def.clear();
						his_word.clear();
						Operation(window, typedictionary, trie, favor_trie, history_trie);
					}
					if (isHere(right.bound, mouse) && change <= count - 8)
					{
						trigger_page = true;
						change += 8;
					}
					if (isHere(left.bound, mouse) && change != 0)
					{
						trigger_page = true;
						change -= 8;
					}
				}
				break;
			}
			default: break;
			}
			window.clear();
			window.draw(screen.draw);
			drawWhich(window, return2, return1, mouse);
			if (change == 0 && change >= count - 8)
			{
				window.draw(right.draw);
				window.draw(left.draw);
			}
			else if (change == 0)
			{
				window.draw(left.draw);
				drawWhich(window, right_point, right_valid, mouse);
			}
			else if (change >= count - 8)
			{
				window.draw(right.draw);
				drawWhich(window, left_point, left_valid, mouse);
			}
			else
			{
				drawWhich(window, right_point, right_valid, mouse);
				drawWhich(window, left_point, left_valid, mouse);
			}
			if (trigger_page)
			{
				int index = 0;
				for (int i = 0; i < change; i++)
				{
					index++;
				}
				for (int i = 0; i < 8; i++)
				{
					if (his_word[index] != "" && his_def[index] != "")
					{
						inf[i]->text.setString(his_word[index]);
						def[i]->text.setString(his_def[index]);
						wrapped_text(rec_dis, def[i]->text);
						index++;
					}
					else
					{
						inf[i]->text.setString("");
						def[i]->text.setString("");
					}
				}
				trigger_page = false;
			}
			for (int i = 0; i < 8; i++)
			{
				if (inf[i]->text.getString() == "")
					break;
				drawWhich(window, bar_red[i], bar_blue[i], mouse);
				window.draw(inf[i]->text);

			}

			for (int i = 0; i < 8; i++)
			{
				if (isHere(bar_blue[i]->bound, mouse) && inf[i]->text.getString() != "") {
					window.draw(book_dis.draw);
					window.draw(def[i]->text);
				}
			}
			window.display();
		}

	}for (int i = 0; i < 8; i++)
	{
		delete inf[i];
		delete bar_blue[i];
		delete bar_red[i];
		delete def[i];
	}
	his_def.clear();
	his_word.clear();
}
