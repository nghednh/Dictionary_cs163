#include "Operation.h"
#include "game.h"
#include "gameWord.h"
#include "gameDef.h"
#include "randomview.h"
#include "Scramble.h"

extern Trie dictrie[5];

//-------------------Function-----------------
string buffer(TrieNode*& tmp)
{
	int i = 0;
	while (tmp->meaning[i].size() > 90 && i < tmp->meaning.size()) {
		++i;
	}
	if (i < tmp->meaning.size()) {
		return tmp->meaning[i];
	}
	else {
		return "";
	}
}

//-------------------Scene-----------------
void gameMenu(RenderWindow& window, string typeDictionary, Trie* trie, Trie& favor_trie, Trie& history_trie)
{
	Clock clickClock;

	Object screen = createObject("content/background/game_scene.png");

	Object title = createObject("content/searchBar.png", 200, 360);
	Info titleText = createInfo("arial.ttf", "Choose your mode!", 220, 360, 40);

	Object back = createObject("content/back.png", 200, 820);
	Object backMove = createObject("content/backMove.png", 200, 820);
	Object backPressed = createObject("content/backPressed.png", 200, 820);
	int backState = 0;

	Object word = createObject("content/word.png", 200, 580);
	Object wordMove = createObject("content/wordMove.png", 200, 580);
	Object wordPressed = createObject("content/wordPressed.png", 200, 580);
	int wordState = 0;

	Object def = createObject("content/definition.png", 200, 660);
	Object defMove = createObject("content/definitionMove.png", 200, 660);
	Object defPressed = createObject("content/definitionPressed.png", 200, 660);
	int defState = 0;

	Object fcword = createObject("content/fcword.png", 1000, 580);
	Object fcwordMove = createObject("content/fcwordMove.png", 1000, 580);
	Object fcwordPressed = createObject("content/fcwordPressed.png", 1000, 580);
	int fcwordState = 0;


	Object fcdef = createObject("content/fcdef.png", 1000, 660);
	Object fcdefMove = createObject("content/fcdefMove.png", 1000, 660);
	Object fcdefPressed = createObject("content/fcdefPressed.png", 1000, 660);
	int fcdefState = 0;

	Object scramble = createObject("content/scramble.png", 200, 740);
	Object scrambleMove = createObject("content/scrambleMove.png", 200, 740);
	Object scramblePressed = createObject("content/scramblePressed.png", 200, 740);
	int scrambleState = 0;

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
				if (isHere(word.bound, mouse)) {
					wordState = 1;
				}
				else {
					wordState = 0;
				}
				if (isHere(def.bound, mouse)) {
					defState = 1;
				}
				else {
					defState = 0;
				}
				if (isHere(fcdef.bound, mouse)) {
					fcdefState = 1;
				}
				else {
					fcdefState = 0;
				}
				if (isHere(fcword.bound, mouse)) {
					fcwordState = 1;
				}
				else {
					fcwordState = 0;
				}
				if (isHere(scramble.bound, mouse)) {
					scrambleState = 1;
				}
				else {
					scrambleState = 0;
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
				else if (isHere(word.bound, mouse)) {
					wordState = 2;
					clickClock.restart();
				}
				else if (isHere(def.bound, mouse)) {
					defState = 2;
					clickClock.restart();
				}
				else if (isHere(fcword.bound, mouse)) {
					fcwordState = 2;
					clickClock.restart();
				}
				else if (isHere(fcdef.bound, mouse)) {
					fcdefState = 2;
					clickClock.restart();
				}
				else if (isHere(scramble.bound, mouse)) {
					scrambleState = 2;
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
		if (wordState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			gameWord(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (defState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			gameDef(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (fcwordState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			flashcardHideDef(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (fcdefState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			flashcardHideWord(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (scrambleState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			TrieNode* scrambleWord = trie->getRandomWordTrue();
			gameScrumble(window, scrambleWord->word, buffer(scrambleWord), typeDictionary, trie, favor_trie, history_trie);
		}
		if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			Operation(window, typeDictionary, trie, favor_trie, history_trie);
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

		window.clear();

		window.draw(screen.draw);
		window.draw(title.draw);
		window.draw(titleText.text);

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

		if (wordState == 0) {
			window.draw(word.draw);
		}
		else if (wordState == 1) {
			window.draw(wordMove.draw);
		}
		else {
			window.draw(wordPressed.draw);
		}

		if (defState == 0) {
			window.draw(def.draw);
		}
		else if (defState == 1) {
			window.draw(defMove.draw);
		}
		else {
			window.draw(defPressed.draw);
		}

		if (fcwordState == 0) {
			window.draw(fcword.draw);
		}
		else if (fcwordState == 1) {
			window.draw(fcwordMove.draw);
		}
		else {
			window.draw(fcwordPressed.draw);
		}

		if (fcdefState == 0) {
			window.draw(fcdef.draw);
		}
		else if (fcdefState == 1) {
			window.draw(fcdefMove.draw);
		}
		else {
			window.draw(fcdefPressed.draw);
		}

		if (scrambleState == 0) {
			window.draw(scramble.draw);
		}
		else if (scrambleState == 1) {
			window.draw(scrambleMove.draw);
		}
		else {
			window.draw(scramblePressed.draw);
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
