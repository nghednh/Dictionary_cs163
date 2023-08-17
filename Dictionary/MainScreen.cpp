#include "MainScreen.h"#include "MainScreen.h"
#include "Operation.h"
extern Trie dictrie[5];
//-------------------Scene-----------------
void mainScreen(RenderWindow& window, Trie* trie, Trie& favor_trie, Trie& history_trie)
{
	Clock clickClock;
	string tmp;

	Object screen = createObject("content/scene.png");

	Object engEng = createObject("content/engeng.png", 200, 400);
	Object engEngMove = createObject("content/engengMove.png", 200, 400);
	Object engEngPressed = createObject("content/engengPressed.png", 200, 400);
	int engengState = 0;

	Object engVie = createObject("content/engvie.png", 200, 480);
	Object engVieMove = createObject("content/engvieMove.png", 200, 480);
	Object engViePressed = createObject("content/engviePressed.png", 200, 480);
	int engvieState = 0;

	Object vieEng = createObject("content/vieeng.png", 200, 560);
	Object vieEngMove = createObject("content/vieengMove.png", 200, 560);
	Object vieEngPressed = createObject("content/vieengPressed.png", 200, 560);
	int vieengState = 0;

	Object slang = createObject("content/slang.png", 200, 640);
	Object slangMove = createObject("content/slangMove.png", 200, 640);
	Object slangPressed = createObject("content/slangPressed.png", 200, 640);
	int slangState = 0;

	Object emo = createObject("content/emoji.png", 200, 720);
	Object emoMove = createObject("content/emojiMove.png", 200, 720);
	Object emoPressed = createObject("content/emojiPressed.png", 200, 720);
	int emoState = 0;

	Object exit = createObject("content/exit.png", 200, 800);
	Object exitMove = createObject("content/exitMove.png", 200, 800);
	Object exitPressed = createObject("content/exitPressed.png", 200, 800);
	int exitState = 0;

	Event e;

	while (window.isOpen())
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) {
				window.close();
			}
			else if (e.type == Event::MouseMoved) {
				if (isHere(engEng.bound, mouse)) {
					engengState = 1;
				}
				else {
					engengState = 0;
				}
				if (isHere(engVie.bound, mouse)) {
					engvieState = 1;
				}
				else {
					engvieState = 0;
				}
				if (isHere(vieEng.bound, mouse)) {
					vieengState = 1;
				}
				else {
					vieengState = 0;
				}
				if (isHere(slang.bound, mouse)) {
					slangState = 1;
				}
				else {
					slangState = 0;
				}
				if (isHere(emo.bound, mouse)) {
					emoState = 1;
				}
				else {
					emoState = 0;
				}
				if (isHere(exit.bound, mouse)) {
					exitState = 1;
				}
				else {
					exitState = 0;
				}
			}
			else if (e.type == Event::MouseButtonPressed)
			{
				if (isHere(engEng.bound, mouse)) {
					tmp = "EngEng";
					engengState = 2;
					clickClock.restart();
				}
				else if (isHere(engVie.bound, mouse)) {
					tmp = "EngVie";
					engvieState = 2;
					clickClock.restart();
				}
				else if (isHere(vieEng.bound, mouse)) {
					tmp = "VieEng";
					vieengState = 2;
					clickClock.restart();
				}
				else if (isHere(slang.bound, mouse)) {
					tmp = "Slang";
					slangState = 2;
					clickClock.restart();
				}
				else if (isHere(emo.bound, mouse)) {
					tmp = "Emoji";
					emoState = 2;
					clickClock.restart();
				}
				else if (isHere(exit.bound, mouse)) {
					exitState = 2;
					clickClock.restart();
				}
			}
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
		if (exitState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			window.close();
		}

		window.clear();

		window.draw(screen.draw);

		if (engengState == 0) {
			window.draw(engEng.draw);
		}
		else if (engengState == 1) {
			window.draw(engEngMove.draw);
		}
		else {
			window.draw(engEngPressed.draw);
		}

		if (engvieState == 0) {
			window.draw(engVie.draw);
		}
		else if (engvieState == 1) {
			window.draw(engVieMove.draw);
		}
		else {
			window.draw(engViePressed.draw);
		}

		if (vieengState == 0) {
			window.draw(vieEng.draw);
		}
		else if (vieengState == 1) {
			window.draw(vieEngMove.draw);
		}
		else {
			window.draw(vieEngPressed.draw);
		}

		if (slangState == 0) {
			window.draw(slang.draw);
		}
		else if (slangState == 1) {
			window.draw(slangMove.draw);
		}
		else {
			window.draw(slangPressed.draw);
		}

		if (emoState == 0) {
			window.draw(emo.draw);
		}
		else if (emoState == 1) {
			window.draw(emoMove.draw);
		}
		else {
			window.draw(emoPressed.draw);
		}

		if (exitState == 0) {
			window.draw(exit.draw);
		}
		else if (exitState == 1) {
			window.draw(exitMove.draw);
		}
		else {
			window.draw(exitPressed.draw);
		}

		window.display();
	}
}
