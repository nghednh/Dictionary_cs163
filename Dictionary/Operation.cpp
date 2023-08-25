#include "Operation.h"
#include "search.h"
#include "addNewWordScreen.h"
#include "removeWordScreen.h"
#include "restoreDictionaryScreen.h"
#include "changeDictionary.h"
#include "viewListFavor.h"
#include "game.h"
#include "Scramble.h"
#include "History.h"
extern Trie dictrie[5];
//-------------------Scene-----------------
void Operation(RenderWindow& window, string typeDictionary, Trie* trie, Trie& favor_trie, Trie& history_trie)
{
	Clock clickClock;

	Object screen = createObject("content/background/dictionaryMenu_scene.png");

	Object searchWord = createObject("content/searchWord.png", 200, 500);
	Object searchWordMove = createObject("content/searchWordMove.png", 200, 500);
	Object searchWordPressed = createObject("content/searchWordPressed.png", 200, 500);
	int searchWordState = 0;

	Object setting = createObject("content/setting.png", 200, 580);
	Object settingMove = createObject("content/settingMove.png", 200, 580);
	Object settingPressed = createObject("content/settingPressed.png", 200, 580);
	int settingState = 0;

	Object favor = createObject("content/favor.png", 200, 660);
	Object favorMove = createObject("content/favorMove.png", 200, 660);
	Object favorPressed = createObject("content/favorPressed.png", 200, 660);
	int favorState = 0;

	Object history = createObject("content/history.png", 200, 740);
	Object historyMove = createObject("content/historyMove.png", 200, 740);
	Object historyPressed = createObject("content/historyPressed.png", 200, 740);
	int historyState = 0;

	Object game = createObject("content/game.png", 200, 820);
	Object gameMove = createObject("content/gameMove.png", 200, 820);
	Object gamePressed = createObject("content/gamePressed.png", 200, 820);
	int gameState = 0;

	Object back = createObject("content/back.png", 200, 900);
	Object backMove = createObject("content/backMove.png", 200, 900);
	Object backPressed = createObject("content/backPressed.png", 200, 900);
	int backState = 0;

	Object engeng = createObject("content/engengMenu.png", 120, 30);
	Object engengMove = createObject("content/engengMenuMove.png", 120, 30);
	Object engengPressed = createObject("content/engengMenuPressed.png", 120, 30);
	int engengState = 3;

	Object engvie = createObject("content/engvieMenu.png", 220, 30);
	Object engvieMove = createObject("content/engvieMenuMove.png", 220, 30);
	Object engviePressed = createObject("content/engvieMenuPressed.png", 220, 30);
	int engvieState = 3;

	Object vieeng = createObject("content/vieengMenu.png", 320, 30);
	Object vieengMove = createObject("content/vieengMenuMove.png", 320, 30);
	Object vieengPressed = createObject("content/vieengMenuPressed.png", 320, 30);
	int vieengState = 3;

	Object slang = createObject("content/slangMenu.png", 420, 30);
	Object slangMove = createObject("content/slangMenuMove.png", 420, 30);
	Object slangPressed = createObject("content/slangMenuPressed.png", 420, 30);
	int slangState = 3;

	Object emo = createObject("content/emojiMenu.png", 520, 30);
	Object emoMove = createObject("content/emojiMenuMove.png", 520, 30);
	Object emoPressed = createObject("content/emojiMenuPressed.png", 520, 30);
	int emoState = 3;

	Object menu = createObject("content/menu.png", 0, 20);
	Object menuMove = createObject("content/menuMove.png", 0, 20);
	Object menuPressed = createObject("content/menuPressed.png", 0, 20);
	int menuState = 0;

	RectangleShape rect(Vector2f(750, 100));
	rect.setFillColor(Color::White);
	rect.setPosition(0, 20);
	rect.setOrigin(700, 0);
	float xVelocity = 0;

	Event e;
	Cursor cursor;
	vector<Sprite> button {menu.draw, setting.draw, history.draw, searchWord.draw, emo.draw, engeng.draw, engvie.draw,
							favor.draw, game.draw, back.draw, slang.draw, menu.draw};
	bool handstate = false;
	if (cursor.loadFromSystem(Cursor::Arrow)) {
		window.setMouseCursor(cursor);
	}
	favor_trie.readDatasetToTrie("Data/" + typeDictionary + "/favorite.txt");

	while (window.isOpen())
	{	
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) {
				window.close();
			}
			else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape) {
				backState = 2;
				clickClock.restart();
			}
			else if (e.type == Event::MouseMoved) {
				if (isHere(searchWord.bound, mouse)) {
					searchWordState = 1;
				}
				else {
					searchWordState = 0;
				}
				if (isHere(setting.bound, mouse)) {
					settingState = 1;
				}
				else {
					settingState = 0;
				}
				if (isHere(favor.bound, mouse)) {
					favorState = 1;
				}
				else {
					favorState = 0;
				}
				if (isHere(history.bound, mouse)) {
					historyState = 1;
				}
				else { historyState = 0; }
				if (isHere(game.bound, mouse)) {
					gameState = 1;
				}
				else {
					gameState = 0;
				}
				if (isHere(back.bound, mouse)) {
					backState = 1;
				}
				else {
					backState = 0;
				}
				if (isHere(engeng.bound, mouse) && rect.getPosition().x >= 700) {
					engengState = 1;
				}
				else if (rect.getPosition().x >= 700) {
					engengState = 0;
				}
				if (isHere(engvie.bound, mouse) && rect.getPosition().x >= 700) {
					engvieState = 1;
				}
				else if (rect.getPosition().x >= 700) {
					engvieState = 0;
				}
				if (isHere(vieeng.bound, mouse) && rect.getPosition().x >= 700) {
					vieengState = 1;
				}
				else if (rect.getPosition().x >= 700) {
					vieengState = 0;
				}
				if (isHere(slang.bound, mouse) && rect.getPosition().x >= 700) {
					slangState = 1;
				}
				else if (rect.getPosition().x >= 700) {
					slangState = 0;
				}
				if (isHere(emo.bound, mouse) && rect.getPosition().x >= 700) {
					emoState = 1;
				}
				else if (rect.getPosition().x >= 700) {
					emoState = 0;
				}
				if (menu.draw.getGlobalBounds().contains(mouse)) {
					menuState = 1;
				}
				else {
					menuState = 0;
				}
			}
			else if (e.type == Event::MouseButtonPressed) {
				if (menu.draw.getGlobalBounds().contains(mouse)) {
					menuState = 2;
					clickClock.restart();
					if (menu.draw.getPosition().x <= 0 || xVelocity == -5) {
						xVelocity = 5;
					}
					else if (menu.draw.getPosition().x >= 600 || xVelocity == 5) {
						xVelocity = -5;
					}
				}
				else if (isHere(setting.bound, mouse)) {
					settingState = 2;
					clickClock.restart();
				}
				else if (isHere(favor.bound, mouse)) {
					favorState = 2;
					clickClock.restart();
				}
				else if (isHere(history.bound, mouse)) {
					historyState = 2;
					clickClock.restart();
				}
				else if (isHere(searchWord.bound, mouse)) {
					searchWordState = 2;
					clickClock.restart();
				}
				else if (isHere(game.bound, mouse)) {
					gameState = 2;
					clickClock.restart();
				}
				else if (isHere(back.bound, mouse)) {
					backState = 2;
					clickClock.restart();
				}
				else if (isHere(engeng.bound, mouse) && rect.getPosition().x >= 700) {
					engengState = 2;
					clickClock.restart();
				}
				else if (isHere(engvie.bound, mouse) && rect.getPosition().x >= 700) {
					engvieState = 2;
					clickClock.restart();
				}
				else if (isHere(vieeng.bound, mouse) && rect.getPosition().x >= 700) {
					vieengState = 2;
					clickClock.restart();
				}
				else if (isHere(slang.bound, mouse) && rect.getPosition().x >= 700) {
					slangState = 2;
					clickClock.restart();
				}
				else if (isHere(emo.bound, mouse) && rect.getPosition().x >= 700) {
					emoState = 2;
					clickClock.restart();
				}
			}
		}
		if (settingState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			changeMenu(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (favorState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			viewlistFavor(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (historyState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			historyScene(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (searchWordState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			searchMenu(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (gameState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			gameMenu(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			mainScreen(window, trie, favor_trie, history_trie);
		}
		if (engengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie = &dictrie[0];
			Operation(window, "EngEng", trie, favor_trie, history_trie);
		}
		if (engvieState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie = &dictrie[1];
			Operation(window, "EngVie", trie, favor_trie, history_trie);
		}
		if (vieengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie = &dictrie[2];
			Operation(window, "VieEng", trie, favor_trie, history_trie);
		}
		if (slangState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie = &dictrie[3];
			Operation(window, "Slang", trie, favor_trie, history_trie);
		}
		if (emoState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie = &dictrie[4];
			Operation(window, "Emoji", trie, favor_trie, history_trie);
		}
		if (menuState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			if (menu.draw.getGlobalBounds().contains(mouse)) {
				menuState = 1;
			}
			else {
				menuState = 0;
			}
		}
		//Set cursor
		/*if (menu.draw.getGlobalBounds().contains(mouse)) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(setting.bound, mouse)) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(favor.bound, mouse)) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(history.bound, mouse)) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(searchWord.bound, mouse)) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(game.bound, mouse)) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(back.bound, mouse)) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(engeng.bound, mouse) && rect.getPosition().x >= 700) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(engvie.bound, mouse) && rect.getPosition().x >= 700) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(vieeng.bound, mouse) && rect.getPosition().x >= 700) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(slang.bound, mouse) && rect.getPosition().x >= 700) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else if (isHere(emo.bound, mouse) && rect.getPosition().x >= 700) {
			if (handstate == false && cursor.loadFromSystem(Cursor::Hand)) {
				window.setMouseCursor(cursor);
			}
			handstate = true;
		}
		else {
			if (handstate == true && cursor.loadFromSystem(Cursor::Arrow)) {
				window.setMouseCursor(cursor);
			}
			handstate = false;
		}*/
		setCursor(window, button, handstate, mouse, cursor);
		window.clear();

		window.draw(screen.draw);

		rect.move(xVelocity, 0);
		menu.draw.move(xVelocity, 0);
		menuMove.draw.move(xVelocity, 0);
		menuPressed.draw.move(xVelocity, 0);
		window.draw(rect);
		if (rect.getPosition().x == 700) {
			if (xVelocity == 5) {
				xVelocity = 0;
			}

			if (engengState == 3) {
				engengState = 0;
			}
			if (engengState == 0) {
				window.draw(engeng.draw);
			}
			else if (engengState == 1) {
				window.draw(engengMove.draw);
			}
			else if (engengState == 2) {
				window.draw(engengPressed.draw);
			}

			if (engvieState == 3) {
				engvieState = 0;
			}
			if (engvieState == 0) {
				window.draw(engvie.draw);
			}
			else if (engvieState == 1) {
				window.draw(engvieMove.draw);
			}
			else if (engvieState == 2) {
				window.draw(engviePressed.draw);
			}

			if (vieengState == 3) {
				vieengState = 0;
			}
			if (vieengState == 0) {
				window.draw(vieeng.draw);
			}
			else if (vieengState == 1) {
				window.draw(vieengMove.draw);
			}
			else if (vieengState == 2) {
				window.draw(vieengPressed.draw);
			}

			if (slangState == 3) {
				slangState = 0;
			}
			if (slangState == 0) {
				window.draw(slang.draw);
			}
			else if (slangState == 1) {
				window.draw(slangMove.draw);
			}
			else if (slangState == 2) {
				window.draw(slangPressed.draw);
			}

			if (emoState == 3) {
				emoState = 0;
			}
			if (emoState == 0) {
				window.draw(emo.draw);
			}
			else if (emoState == 1) {
				window.draw(emoMove.draw);
			}
			else if (emoState == 2) {
				window.draw(emoPressed.draw);
			}
		}
		if (rect.getPosition().x == 0 && xVelocity == -5) {
			xVelocity = 0;
			engengState = 3;
			engvieState = 3;
			vieengState = 3;
			slangState = 3;
			emoState = 3;
		}

		if (menuState == 0) {
			window.draw(menu.draw);
		}
		else if (menuState == 1) {
			window.draw(menuMove.draw);
		}
		else {
			window.draw(menuPressed.draw);
		}

		if (settingState == 0) {
			window.draw(setting.draw);
		}
		else if (settingState == 1) {
			window.draw(settingMove.draw);
		}
		else {
			window.draw(settingPressed.draw);
		}

		if (favorState == 0) {
			window.draw(favor.draw);
		}
		else if (favorState == 1) {
			window.draw(favorMove.draw);
		}
		else {
			window.draw(favorPressed.draw);
		}
		if (historyState == 0) {
			window.draw(history.draw);
		}
		else if (historyState == 1) {
			window.draw(historyMove.draw);
		}
		else {
			window.draw(historyPressed.draw);
		}

		if (searchWordState == 0) {
			window.draw(searchWord.draw);
		}
		else if (searchWordState == 1) {
			window.draw(searchWordMove.draw);
		}
		else {
			window.draw(searchWordPressed.draw);
		}

		if (gameState == 0) {
			window.draw(game.draw);
		}
		else if (gameState == 1) {
			window.draw(gameMove.draw);
		}
		else {
			window.draw(gamePressed.draw);
		}

		if (backState == 0) {
			window.draw(back.draw);
		}
		else if (backState == 1) {
			window.draw(backMove.draw);
		}
		else {
			window.draw(backPressed.draw);
		}

		window.display();
	}
}
