#include "search_editDefinition.h"
#include "search_saveFavorList.h"
#include "viewListFavor.h"
#include "search_saveFavorList.h"
#include "Operation.h"
void search_editDefinition(RenderWindow& window, Trie* trie, string typeDictionary, Trie& favor_trie, Trie& history_trie, string word, int& state) {
	favor_trie.readDatasetToTrie("Data/" + typeDictionary + "/favorite.txt");
	history_trie.readDatasetToTrie("Data/" + typeDictionary + "/history.txt");
	string editWord;
	vector<string> def;
	def = trie->searchWordNode(word)->meaning;
	def.push_back("");
	float scale = 1.5f;
	bool entered1 = 0;
	int ableEdit = 0, ableAdd = 0, ableDelete = 0;
	int change = 0, count = def.size();
	bool trigger_page = true;
	vector<Sprite> button;
	Info* abs[8], * full[8];
	Object* bar_blue[8];
	Object* bar_red[8];
	for (int i = 0; i < 8; i++) {
		abs[i] = createInfoTest("content/Oswald-Light.ttf", "demo_text", 210, (323 + 75 * i), 38);
		bar_blue[i] = createObjectTest("content/bar1.png", 203, (315 + 75 * i));
		bar_red[i] = createObjectTest("content/bar2.png", 203, (315 + 75 * i));
		full[i] = createInfoTest("content/Oswald-Light.ttf", "demo_text", 616, 420, 24);
		button.push_back(bar_blue[i]->draw);
	}
	Object del_blue = createObject("content/del_blue.png", 1325, 315);
	button.push_back(del_blue.draw);
	Object del_red = createObject("content/del_red.png", 1325, 315);
	Object add_blue = createObject("content/add_blue.png", 1325, 390);
	button.push_back(add_blue.draw);
	Object add_red = createObject("content/add_red.png", 1325, 390);
	Object edit_blue = createObject("content/edit_blue.png", 1325, 465);
	button.push_back(edit_blue.draw);
	Object edit_red = createObject("content/edit_red.png", 1325, 465);
	Object check_delete = createObject("content/del_pop.png", 728, 60);
	Object screen = createObject("content/editDefScene.png");
	Info enterEdit = createInfo("content/Oswald-Light.ttf", "New Definition", 765,180, 39);
	Object canEdit = createObject("content/canEdit.png" , 728, 60);
	Object ok1 = createObject("content/ok2.png", 983, 248);
	button.push_back(ok1.draw);
	Object ok2 = createObject("content/ok1.png", 983, 248);
	Object ok3 = createObject("content/ok2.png", 983, 248);
	Object ok4 = createObject("content/ok1.png", 983, 248);
	Object return3 = createObject("content/return2.png", 743, 248);
	Object return4 = createObject("content/return3.png", 743, 248);
	Object return1 = createObject("content/return.png", 146, 83);
	button.push_back(return1.draw);
	Object return2 = createObject("content/return1.png", 146, 83);
	Object left = createObject("content/left.png", 798, 966);
	button.push_back(left.draw);
	Object left_point = createObject("content/left_point.png", 798, 966);

	Object left_valid = createObject("content/left_valid.png", 798, 966);
	Object right = createObject("content/right.png", 825, 966);
	button.push_back(right.draw);
	Object right_point = createObject("content/right_point.png", 825, 966);
	Object right_valid = createObject("content/right_valid.png", 825, 966);
	sf::RectangleShape rec_dis;
	rec_dis.setSize(sf::Vector2f(588, 450));
	rec_dis.setPosition(589, 375);
	Object book_dis = createObject("content/book_image.png", 600, 375);
	Event event;
	//Cursor
	Cursor cursor;
	bool handstate = false;
	if (cursor.loadFromSystem(Cursor::Arrow)) {
		window.setMouseCursor(cursor);
	}
	state = false;
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
						def.pop_back();
						string str = "";
						ofstream fout;
						if (favor_trie.searchWord(word)) {
							favor_trie.searchWordNode(word)->meaning.swap(def);
							str = "";
							fout.open("Data/" + typeDictionary + "/favorite.txt");
							if (fout.is_open()) display(favor_trie.getRoot(), str, fout);
							fout.close();
						}
						if (history_trie.searchWord(word)) {
							history_trie.searchWordNode(word)->meaning.swap(def);
							str = "";
							fout.open("Data/" + typeDictionary + "/history.txt");
							if (fout.is_open()) display(history_trie.getRoot(), str, fout);
							fout.close();
						}state = 1;
						for (int i = 0; i < 8; i++) {
							delete abs[i];
							delete bar_blue[i];
							delete bar_red[i];
							delete full[i];
						}
						def.clear();
						search_addfavorite(window, trie, typeDictionary, favor_trie, history_trie);
						//Operation(window, typeDictionary, trie, favor_trie, history_trie);
					}
					if (isHere(enterEdit.bound, mouse))
					{
						enterEdit.check = true;
						enterEdit.text.setString("|");
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
					if (isHere(return3.bound, mouse)) {
						state = 0;
						window.clear();
						return;
					}
					if (isHere(del_blue.bound, mouse))
					{
						if (ableDelete == 0)
							ableDelete = 1;
						else ableDelete = 0;
						ableAdd = 0;
						ableEdit = 0;
					}
					if (isHere(add_blue.bound, mouse))
					{
						if (ableAdd == 0)
							ableAdd = 1;
						else ableAdd = 0;
						ableEdit = 0;
						ableDelete = 0;
					}
					if (isHere(edit_blue.bound, mouse))
					{
						if (ableEdit == 0)
							ableEdit = 1;
						else ableEdit = 0;
						ableDelete = 0;
						ableAdd = 0;
					}
					int index = 0;
					for (int i = 0; i < change; i++)
					{
						index++;
					}
					for (int i = 0; i < 8; i++) {
						if (def[index] != "") {
							if (isHere(bar_blue[i]->bound, mouse)) {
								editWord = def[index];
								if (ableEdit == 1)
									ableEdit = 2;
								if (ableDelete == 1)
									ableDelete = 2;
							}
							index++;
						}
					}
					if (ableEdit == 2) {
						if (isHere(ok1.bound, mouse)) {
							int count = 0;
							for (auto i = 0; i < def.size(); i++) {
								if (def[i] != editWord)
								{
									count++;
								}
								else break;
							}
							def.at(count) = enterEdit.text.getString();
							def.pop_back();
							trie->searchWordNode(word)->meaning.swap(def);
							string str = "";
							ofstream fout;
							fout.open("Data/" + typeDictionary + "/document.txt");
							if (fout.is_open()) display(trie->getRoot(), str, fout);
							fout.close();
							if (favor_trie.searchWord(word)) {
								favor_trie.searchWordNode(word)->meaning.swap(def);
								str = "";
								fout.open("Data/" + typeDictionary + "/favorite.txt");
								if (fout.is_open()) display(favor_trie.getRoot(), str, fout);
								fout.close();
							}
							if (history_trie.searchWord(word)) {
								history_trie.searchWordNode(word)->meaning.swap(def);
								str = "";
								fout.open("Data/" + typeDictionary + "/history.txt");
								if (fout.is_open()) display(history_trie.getRoot(), str, fout);
								fout.close();
							}
							state = 0;
							for (int i = 0; i < 8; i++) {
								delete abs[i];
								delete bar_blue[i];
								delete bar_red[i];
								delete full[i];
							}
							def.clear();
							return;
						}
					}
					if (ableAdd == 1) {
						if (isHere(ok1.bound, mouse)) {
							def.pop_back();
							def.push_back(enterEdit.text.getString());
							trie->searchWordNode(word)->meaning.swap(def);
							string str = "";
							ofstream fout;
							fout.open("Data/" + typeDictionary + "/document.txt");
							if (fout.is_open()) display(trie->getRoot(), str, fout);
							fout.close();
							
							if (favor_trie.searchWord(word)) {
								favor_trie.searchWordNode(word)->meaning.swap(def);
								str = "";
								fout.open("Data/" + typeDictionary + "/favorite.txt");
								if (fout.is_open()) display(favor_trie.getRoot(), str, fout);
								fout.close();
							}
							if (history_trie.searchWord(word)) {
								history_trie.searchWordNode(word)->meaning.swap(def);
								str = "";
								fout.open("Data/" + typeDictionary + "/history.txt");
								if (fout.is_open()) display(history_trie.getRoot(), str, fout);
								fout.close();
							}
							state = 0;
							for (int i = 0; i < 8; i++) {
								delete abs[i];
								delete bar_blue[i];
								delete bar_red[i];
								delete full[i];
							}
							def.clear();
							return;
						}
					}
					if (ableDelete == 2) {
						if (isHere(ok1.bound, mouse)) {
							int count = 0;
							for (auto i = 0; i < def.size(); i++) {
								if (def[i] != editWord)
								{
									count++;
								}
								else break;
							}
							def.pop_back();
							def.erase(def.begin() + count);
							trie->searchWordNode(word)->meaning.swap(def);
							string str = "";
							ofstream fout;
							fout.open("Data/" + typeDictionary + "/document.txt");
							if (fout.is_open()) display(trie->getRoot(), str, fout);
							fout.close();
							str = "";
							if (favor_trie.searchWord(word)) {
								favor_trie.searchWordNode(word)->meaning.swap(def);
								str = "";
								fout.open("Data/" + typeDictionary + "/favorite.txt");
								if (fout.is_open()) display(favor_trie.getRoot(), str, fout);
								fout.close();
							}
							if (history_trie.searchWord(word)) {
								history_trie.searchWordNode(word)->meaning.swap(def);
								str = "";
								fout.open("Data/" + typeDictionary + "/history.txt");
								if (fout.is_open()) display(history_trie.getRoot(), str, fout);
								fout.close();
							}
							state = 0;
							for (int i = 0; i < 8; i++) {
								delete abs[i];
								delete bar_blue[i];
								delete bar_red[i];
								delete full[i];
							}
							def.clear();
							return;
						}
					}
				}
			}
			break;
			case Event::TextEntered:
			{if (ableEdit == 2 || ableAdd == 1)
				texting(enterEdit, event.text.unicode, 100);
			}
			break;
			default: break;
			}

			//Set cursor
			setCursor(window, button, handstate, mouse, cursor);
			window.clear();
			window.draw(screen.draw);
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
					string tmp = "";
					if (def[index] != "")
					{
						if (def[index].length() > 10) {
							for (int j = 0; j < 10; j++) {
								tmp += def[index][j];
							}
							tmp += "...";
						}
						else tmp = def[index];
						abs[i]->text.setString(tmp);
						full[i]->text.setString(def[index]);
						wrapped_text(rec_dis, full[i]->text);
						index++;
					}
					else
					{
						abs[i]->text.setString("");
						full[i]->text.setString("");
					}
				}
				trigger_page = false;
			}
			if (isHere(return1.bound, mouse))
				window.draw(return2.draw);
			else
				window.draw(return1.draw);
			for (int i = 0; i < 8; i++)
			{
				if (abs[i]->text.getString() == "")
					break;
				drawWhich(window, bar_red[i], bar_blue[i], mouse);
				window.draw(abs[i]->text);

			}

			for (int i = 0; i < 8; i++)
			{
				if (isHere(bar_blue[i]->bound, mouse) && abs[i]->text.getString() != "") {
					window.draw(book_dis.draw);
					window.draw(full[i]->text);
				}
			}
			if (ableEdit == 0) {
				drawWhich(window, edit_red, edit_blue, mouse);
			}
			if (ableEdit == 1 || ableEdit == 2) {
				drawWhich(window, edit_blue, edit_red, mouse);

			}
			if (ableEdit == 2) {
				window.draw(canEdit.draw);
				window.draw(enterEdit.text);
				drawWhich(window, ok2, ok1, mouse);
				drawWhich(window, return4, return3, mouse);


			}
			if (ableDelete == 0) {
				drawWhich(window, del_red, del_blue, mouse);
			}
			if (ableDelete == 1 || ableDelete == 2) {
				drawWhich(window, del_blue, del_red, mouse);

			}
			if (ableDelete == 2) {
				window.draw(check_delete.draw);
				drawWhich(window, ok2, ok1, mouse);
				drawWhich(window, return4, return3, mouse);
			}
			if (ableAdd == 0) {
				drawWhich(window, add_red, add_blue, mouse);
			}
			if (ableAdd == 1) {
				drawWhich(window, add_blue, add_red, mouse);
				window.draw(canEdit.draw);
				window.draw(enterEdit.text);
				drawWhich(window, ok2, ok1, mouse);
				drawWhich(window, return4, return3, mouse);
			}


			window.display();
		}
	}
	for (int i = 0; i < 8; i++) {
		delete abs[i];
		delete bar_blue[i];
		delete bar_red[i];
		delete full[i];
	}
	def.clear();
}
