#include "Operation.h"
#include "addNewWordScreen.h"
#include "restoreDictionaryScreen.h"

//-------------------Scene-----------------
void Operation(RenderWindow& window, string typeDictionary, Trie& trie)
{
	Clock clickClock;

	Object screen = createObject("content/scene.png");

	Object addWord = createObject("content/addWord.png", 200, 500);
	Object addWordMove = createObject("content/addWordMove.png", 200, 500);
	Object addWordPressed = createObject("content/addWordPressed.png", 200, 500);
	int addState = 0;

	Object resetDicitonary = createObject("content/reset.png", 200, 580);
	Object resetDicitonaryMove = createObject("content/resetMove.png", 200, 580);
	Object resetDicitonaryPressed = createObject("content/resetPressed.png", 200, 580);
	int resetState = 0;

	Object back = createObject("content/back.png", 200, 780);
	Object backMove = createObject("content/backMove.png", 200, 780);
	Object backPressed = createObject("content/backPressed.png", 200, 780);
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

	trie.clearAll();
	trie.readDatasetToTrie("Data/" + typeDictionary + "/document.txt");

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
				if (isHere(addWord.bound, mouse)) {
					addState = 1;
				}
				else {
					addState = 0;
				}
				if (isHere(resetDicitonary.bound, mouse)) {
					resetState = 1;
				}
				else {
					resetState = 0;
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
				else if (isHere(addWord.bound, mouse)) {
					addState = 2;
					clickClock.restart();
				}
				else if (isHere(resetDicitonary.bound, mouse)) {
					resetState = 2;
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
		if (addState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			addNewWordScreen(window, typeDictionary, trie);
		}
		if (resetState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			restoreDictionaryScreen(window, typeDictionary, trie);
		}
		if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			mainScreen(window, trie);
		}
		if (engengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			cout << 1 << endl;
			Operation(window, "EngEng", trie);
		}
		if (engvieState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			Operation(window, "EngVie", trie);
		}
		if (vieengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			Operation(window, "VieEng", trie);
		}
		if (slangState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			Operation(window, "Slang", trie);
		}
		if (emoState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			Operation(window, "Emoji", trie);
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

		cout << menuState << endl;
		if (menuState == 0) {
			window.draw(menu.draw);
		}
		else if (menuState == 1) {
			window.draw(menuMove.draw);
		}
		else {
			window.draw(menuPressed.draw);
		}

		if (addState == 0) {
			window.draw(addWord.draw);
		}
		else if (addState == 1) {
			window.draw(addWordMove.draw);
		}
		else {
			window.draw(addWordPressed.draw);
		}

		if (resetState == 0) {
			window.draw(resetDicitonary.draw);
		}
		else if (resetState == 1) {
			window.draw(resetDicitonaryMove.draw);
		}
		else {
			window.draw(resetDicitonaryPressed.draw);
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