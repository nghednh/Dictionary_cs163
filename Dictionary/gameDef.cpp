#include "Operation.h"
#include "gameWord.h"
#include "game.h"
extern Trie dictrie[5];
//-------------------Function-----------------
void createGameDef(int& ans, Font& font, Trie* trie, Object ob[], Object obMove[], Object obPressed[], Object obTrue[], Object obFalse[], Text opText[], Text& question, RectangleShape& box)
{
	srand(time(0));
	ans = rand() % 4 + 1;
	TrieNode* tmp = trie->getRandomWordTrue();
	TrieNode* op1 = trie->getRandomWordWrong(tmp, nullptr, nullptr);
	TrieNode* op2 = trie->getRandomWordWrong(tmp, op1, nullptr);
	TrieNode* op3 = trie->getRandomWordWrong(tmp, op1, op2);

	question.setString(tmp->meaning[0]);
	question.setPosition(300, 300);
	question.setFont(font);
	question.setFillColor(Color(136, 136, 136));
	question.setCharacterSize(40);
	wrapped_text(box, question);

	int cnt = 1;
	for (int i = 1; i <= 4; ++i) {
		if (i == ans) {
			opText[i].setString(tmp->word);
		}
		else if (cnt == 1) {
			opText[i].setString(op1->word);
			++cnt;
		}
		else if (cnt == 2) {
			opText[i].setString(op2->word);
			++cnt;
		}
		else {
			opText[i].setString(op3->word);
		}
		opText[i].setCharacterSize(30);
		opText[i].setFont(font);
		opText[i].setFillColor(Color(52, 142, 254));

		ob[i].txt.loadFromFile("content/option.png");
		ob[i].draw.setTexture(ob[i].txt);
		obMove[i].txt.loadFromFile("content/optionMove.png");
		obMove[i].draw.setTexture(obMove[i].txt);
		obPressed[i].txt.loadFromFile("content/optionPressed.png");
		obPressed[i].draw.setTexture(obPressed[i].txt);
		obTrue[i].txt.loadFromFile("content/optionTrue.png");
		obTrue[i].draw.setTexture(obTrue[i].txt);
		obFalse[i].txt.loadFromFile("content/optionFalse.png");
		obFalse[i].draw.setTexture(obFalse[i].txt);

		if (i == 1) {
			opText[i].setPosition(210, 510);
			ob[i].draw.setPosition(200, 500);
			obMove[i].draw.setPosition(200, 500);
			obPressed[i].draw.setPosition(200, 500);
			obTrue[i].draw.setPosition(200, 500);
			obFalse[i].draw.setPosition(200, 500);
		}
		else if (i == 2) {
			opText[i].setPosition(860, 510);
			ob[i].draw.setPosition(850, 500);
			obMove[i].draw.setPosition(850, 500);
			obPressed[i].draw.setPosition(850, 500);
			obTrue[i].draw.setPosition(850, 500);
			obFalse[i].draw.setPosition(850, 500);
		}
		else if (i == 3) {
			opText[i].setPosition(210, 735);
			ob[i].draw.setPosition(200, 725);
			obMove[i].draw.setPosition(200, 725);
			obPressed[i].draw.setPosition(200, 725);
			obTrue[i].draw.setPosition(200, 725);
			obFalse[i].draw.setPosition(200, 725);
		}
		else if (i == 4) {
			opText[i].setPosition(860, 735);
			ob[i].draw.setPosition(850, 725);
			obMove[i].draw.setPosition(850, 725);
			obPressed[i].draw.setPosition(850, 725);
			obTrue[i].draw.setPosition(850, 725);
			obFalse[i].draw.setPosition(850, 725);
		}
	}
}

//-----------------Draw Scene--------------------------
void gameDef(RenderWindow& window, string typeDictionary, Trie* trie, Trie& favor_trie, Trie& history_trie)
{
	Clock clickClock;

	Font font;
	font.loadFromFile("arial.ttf");

	Object screen = createObject("content/scene.png");

	Object title = createObject("content/searchBar.png", 200, 225);
	Info titleText = createInfo("arial.ttf", "Choose the correct definition of the given word!", 220, 225, 40);

	Object back = createObject("content/back.png", 200, 950);
	Object backMove = createObject("content/backMove.png", 200, 950);
	Object backPressed = createObject("content/backPressed.png", 200, 950);
	int backState = 0;

	Object retry = createObject("content/retry.png", 600, 950);
	Object retryMove = createObject("content/retryMove.png", 600, 950);
	Object retryPressed = createObject("content/retryPressed.png", 600, 950);
	int retryState = 0;

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

	RectangleShape box(Vector2f(1140, 400));
	Object ob[5];
	Object obMove[5];
	Object obPressed[5];
	Object obTrue[5];
	Object obFalse[5];
	Text opText[5];
	Text question;
	int ans;
	int state[5] = { 0, 0, 0, 0, 0 };
	bool isAns = false;

	createGameDef(ans, font, trie, ob, obMove, obPressed, obTrue, obFalse, opText, question, box);

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
				if (!isAns) {
					if (ob[1].draw.getGlobalBounds().contains(mouse)) {
						state[1] = 1;
					}
					else {
						state[1] = 0;
					}
					if (ob[2].draw.getGlobalBounds().contains(mouse)) {
						state[2] = 1;
					}
					else {
						state[2] = 0;
					}
					if (ob[3].draw.getGlobalBounds().contains(mouse)) {
						state[3] = 1;
					}
					else {
						state[3] = 0;
					}
					if (ob[4].draw.getGlobalBounds().contains(mouse)) {
						state[4] = 1;
					}
					else {
						state[4] = 0;
					}
				}
				if (isHere(back.bound, mouse)) {
					backState = 1;
				}
				else {
					backState = 0;
				}
				if (isHere(retry.bound, mouse)) {
					retryState = 1;
				}
				else {
					retryState = 0;
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
				else if (ob[1].draw.getGlobalBounds().contains(mouse) && !isAns) {
					isAns = true;
					state[1] = 2;
				}
				else if (ob[2].draw.getGlobalBounds().contains(mouse) && !isAns) {
					isAns = true;
					state[2] = 2;
				}
				else if (ob[3].draw.getGlobalBounds().contains(mouse) && !isAns) {
					isAns = true;
					state[3] = 2;
				}
				else if (ob[4].draw.getGlobalBounds().contains(mouse) && !isAns) {
					isAns = true;
					state[4] = 2;
				}
				else if (isHere(back.bound, mouse)) {
					backState = 2;
					clickClock.restart();
				}
				else if (isHere(retry.bound, mouse)) {
					retryState = 2;
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
		if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			gameMenu(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (retryState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			gameDef(window, typeDictionary, trie, favor_trie, history_trie);
		}
		if (engengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			*trie = dictrie[0];
			Operation(window, "EngEng", trie, favor_trie, history_trie);
		}
		if (engvieState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			*trie = dictrie[1];
			Operation(window, "EngVie", trie, favor_trie, history_trie);
		}
		if (vieengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			*trie = dictrie[2];
			Operation(window, "VieEng", trie, favor_trie, history_trie);
		}
		if (slangState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			*trie = dictrie[3];
			Operation(window, "Slang", trie, favor_trie, history_trie);
		}
		if (emoState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			*trie = dictrie[4];
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
		window.draw(question);

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

		if (backState == 0) {
			window.draw(back.draw);
		}
		else if (backState == 1) {
			window.draw(backMove.draw);
		}
		else {
			window.draw(backPressed.draw);
		}

		if (retryState == 0) {
			window.draw(retry.draw);
		}
		else if (backState == 1) {
			window.draw(retryMove.draw);
		}
		else {
			window.draw(retryPressed.draw);
		}

		for (int i = 1; i <= 4; ++i) {
			if (isAns) {
				if (state[i] != 2 && i != ans) {
					window.draw(obPressed[i].draw);
				}
				else if (state[i] == 2 && i != ans) {
					window.draw(obFalse[i].draw);
				}
				else {
					window.draw(obTrue[i].draw);
				}
			}
			else {
				if (state[i] == 0) {
					window.draw(ob[i].draw);
				}
				else if (state[i] == 1) {
					window.draw(obMove[i].draw);
				}
			}
			window.draw(opText[i]);
		}

		window.display();
	}
}
