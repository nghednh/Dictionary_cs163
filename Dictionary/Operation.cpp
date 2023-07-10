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

	Event e;

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
			}
			else if (e.type == Event::MouseButtonPressed) {	
				if (isHere(addWord.bound, mouse)) {
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

		window.clear();

		window.draw(screen.draw);

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