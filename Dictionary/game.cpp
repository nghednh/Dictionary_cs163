#include "Operation.h"
#include "game.h"

//-------------------Function-----------------
void createGame(int& ans, Font& font, Trie& trie, Object ob[], Text opText[], Text& question, RectangleShape& box)
{
	srand(time(0));
	ans = rand() % 4 + 1;
	TrieNode* tmp = trie.getRandomWordTrue();
	TrieNode* op1 = trie.getRandomWordWrong(tmp, nullptr, nullptr);
	TrieNode* op2 = trie.getRandomWordWrong(tmp, op1, nullptr);
	TrieNode* op3 = trie.getRandomWordWrong(tmp, op1, op2);

	question.setString(tmp->word);
	question.setPosition(300, 300);
	question.setFont(font);
	question.setFillColor(Color(136, 136, 136));
	question.setCharacterSize(40);

	int cnt = 1;
	for (int i = 1; i <= 4; ++i) {
		if (i == ans) {
			opText[i].setString(tmp->meaning[0]);
		}
		else if (cnt == 1) {
			opText[i].setString(op1->meaning[0]);
			++cnt;
		}
		else if (cnt == 2) {
			opText[i].setString(op2->meaning[0]);
			++cnt;
		}
		else {
			opText[i].setString(op3->meaning[0]);
		}
		opText[i].setCharacterSize(30);
		opText[i].setFont(font);
		opText[i].setFillColor(Color(52, 142, 254));
		ob[i].txt.loadFromFile("content/option.png");
		ob[i].draw.setTexture(ob[i].txt);

		if (i == 1) {
			opText[i].setPosition(210, 510);
			ob[i].draw.setPosition(200, 500);
		}
		else if (i == 2) {
			opText[i].setPosition(860, 510);
			ob[i].draw.setPosition(850, 500);
		}
		else if (i == 3) {
			opText[i].setPosition(210, 735);
			ob[i].draw.setPosition(200, 725);
		}
		else if (i == 4) {
			opText[i].setPosition(860, 735);
			ob[i].draw.setPosition(850, 725);
		}
	}
}

void resultGame(TrieNode*& ans, Text& ansText, Text& op1Text, Text& op2Text, Text& op3Text, int& state1, int& state2, int& state3, int& state4)
{

}

//-------------------Scene-----------------
void gameMenu(RenderWindow& window, string typeDictionary, Trie& trie, Trie& favor_trie)
{
	Clock clickClock;

	Object screen = createObject("content/scene.png");

	Object title = createObject("content/searchBar.png", 200, 360);
	Info titleText = createInfo("arial.ttf", "Choose your mode!", 220, 360, 40);

	Object back = createObject("content/back.png", 200, 820);
	Object backMove = createObject("content/backMove.png", 200, 820);
	Object backPressed = createObject("content/backPressed.png", 200, 820);
	int backState = 0;

	Object word = createObject("content/word.png", 200, 660);
	Object wordMove = createObject("content/wordMove.png", 200, 660);
	Object wordPressed = createObject("content/wordPressed.png", 200, 660);
	int wordState = 0;

	Object def = createObject("content/definition.png", 200, 740);
	Object defMove = createObject("content/definitionMove.png", 200, 740);
	Object defPressed = createObject("content/definitionPressed.png", 200, 740);
	int defState = 0;

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
			gameWord(window, typeDictionary, trie, favor_trie);
		}
		if (defState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			gameDef(window, typeDictionary, trie, favor_trie);
		}
		if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			Operation(window, typeDictionary, trie, favor_trie);
		}
		if (engengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/EngEng/document.txt");
			Operation(window, "EngEng", trie, favor_trie);
		}
		if (engvieState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/EngVie/document.txt");
			Operation(window, "EngVie", trie, favor_trie);
		}
		if (vieengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/VieEng/document.txt");
			Operation(window, "VieEng", trie, favor_trie);
		}
		if (slangState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/Slang/document.txt");
			Operation(window, "Slang", trie, favor_trie);
		}
		if (emoState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/Emoji/document.txt");
			Operation(window, "Emoji", trie, favor_trie);
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

void gameWord(RenderWindow& window, string typeDictionary, Trie& trie, Trie& favor_trie)
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

	RectangleShape box(Vector2f(600, 200));
	Object ob[5];
	Text opText[5];
	Text question;
	int ans;

	createGame(ans, font, trie, ob, opText, question, box);

	Vector2f position = ob[1].draw.getPosition();
	
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
				if (ob[1].draw.getGlobalBounds().contains(mouse)) {
					ob[1].txt.loadFromFile("content/optionMove.png");
					ob[1].draw.setTexture(ob[1].txt);
				}
				else {
					ob[1].txt.loadFromFile("content/option.png");
					ob[1].draw.setTexture(ob[1].txt);
				}
				if (ob[2].draw.getGlobalBounds().contains(mouse)) {
					ob[2].txt.loadFromFile("content/optionMove.png");
					ob[2].draw.setTexture(ob[2].txt);
				}
				else {
					ob[2].txt.loadFromFile("content/option.png");
					ob[2].draw.setTexture(ob[2].txt);
				}
				if (ob[3].draw.getGlobalBounds().contains(mouse)) {
					ob[3].txt.loadFromFile("content/optionMove.png");
					ob[3].draw.setTexture(ob[3].txt);
				}
				else {
					ob[3].txt.loadFromFile("content/option.png");
					ob[3].draw.setTexture(ob[3].txt);
				}
				if (ob[4].draw.getGlobalBounds().contains(mouse)) {
					ob[4].txt.loadFromFile("content/optionMove.png");
					ob[4].draw.setTexture(ob[4].txt);
				}
				else {
					ob[4].txt.loadFromFile("content/option.png");
					ob[4].draw.setTexture(ob[4].txt);
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
				else if (isHere(ob[1].bound, mouse)) {
					
				}
				else if (isHere(ob[2].bound, mouse)) {

				}
				else if (isHere(ob[3].bound, mouse)) {

				}
				else if (isHere(ob[4].bound, mouse)) {

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
		if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			gameMenu(window, typeDictionary, trie, favor_trie);
		}
		if (engengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/EngEng/document.txt");
			Operation(window, "EngEng", trie, favor_trie);
		}
		if (engvieState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/EngVie/document.txt");
			Operation(window, "EngVie", trie, favor_trie);
		}
		if (vieengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/VieEng/document.txt");
			Operation(window, "VieEng", trie, favor_trie);
		}
		if (slangState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/Slang/document.txt");
			Operation(window, "Slang", trie, favor_trie);
		}
		if (emoState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/Emoji/document.txt");
			Operation(window, "Emoji", trie, favor_trie);
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

		for (int i = 1; i <= 4; ++i) {
			window.draw(ob[i].draw);
			window.draw(opText[i]);
		}

		window.display();
	}
}

void gameDef(RenderWindow& window, string typeDictionary, Trie& trie, Trie& favor_trie)
{
	Clock clickClock;

	Object screen = createObject("content/scene.png");

	Object title = createObject("content/searchBar.png", 200, 225);
	Info titleText = createInfo("arial.ttf", "Choose the correct word of the given definition!", 220, 225, 40);

	Object option1 = createObject("content/option1.png", 200, 500);
	Object option1Move = createObject("content/option1Move.png", 200, 500);
	Object option1Pressed = createObject("content/option1Pressed.png", 200, 500);
	int state1 = 0;

	Object option2 = createObject("content/option2.png", 850, 500);
	Object option2Move = createObject("content/option2Move.png", 850, 500);
	Object option2Pressed = createObject("content/option2Pressed.png", 850, 500);
	int state2 = 0;

	Object option3 = createObject("content/option3.png", 200, 725);
	Object option3Move = createObject("content/option3Move.png", 200, 725);
	Object option3Pressed = createObject("content/option3Pressed.png", 200, 725);
	int state3 = 0;

	Object option4 = createObject("content/option4.png", 850, 725);
	Object option4Move = createObject("content/option4Move.png", 850, 725);
	Object option4Pressed = createObject("content/option4Pressed.png", 850, 725);
	int state4 = 0;

	Object back = createObject("content/back.png", 200, 950);
	Object backMove = createObject("content/backMove.png", 200, 950);
	Object backPressed = createObject("content/backPressed.png", 200, 950);
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
				if (isHere(option1.bound, mouse)) {
					state1 = 1;
				}
				else {
					state1 = 0;
				}
				if (isHere(option2.bound, mouse)) {
					state2 = 1;
				}
				else {
					state2 = 0;
				}
				if (isHere(option3.bound, mouse)) {
					state3 = 1;
				}
				else {
					state3 = 0;
				}
				if (isHere(option4.bound, mouse)) {
					state4 = 1;
				}
				else {
					state4 = 0;
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
				else if (isHere(option1.bound, mouse)) {
					state1 = 2;
					clickClock.restart();
				}
				else if (isHere(option2.bound, mouse)) {
					state2 = 2;
					clickClock.restart();
				}
				else if (isHere(option3.bound, mouse)) {
					state3 = 2;
					clickClock.restart();
				}
				else if (isHere(option4.bound, mouse)) {
					state4 = 2;
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
		if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			gameMenu(window, typeDictionary, trie, favor_trie);
		}
		if (engengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/EngEng/document.txt");
			Operation(window, "EngEng", trie, favor_trie);
		}
		if (engvieState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/EngVie/document.txt");
			Operation(window, "EngVie", trie, favor_trie);
		}
		if (vieengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/VieEng/document.txt");
			Operation(window, "VieEng", trie, favor_trie);
		}
		if (slangState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/Slang/document.txt");
			Operation(window, "Slang", trie, favor_trie);
		}
		if (emoState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
			trie.clearAll();
			trie.readDatasetToTrie("Data/Emoji/document.txt");
			Operation(window, "Emoji", trie, favor_trie);
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

		if (state1 == 0) {
			window.draw(option1.draw);
		}
		else if (state1 == 1) {
			window.draw(option1Move.draw);
		}
		else {
			window.draw(option1Pressed.draw);
		}

		if (state2 == 0) {
			window.draw(option2.draw);
		}
		else if (state2 == 1) {
			window.draw(option2Move.draw);
		}
		else {
			window.draw(option2Pressed.draw);
		}

		if (state3 == 0) {
			window.draw(option3.draw);
		}
		else if (state3 == 1) {
			window.draw(option3Move.draw);
		}
		else {
			window.draw(option3Pressed.draw);
		}

		if (state4 == 0) {
			window.draw(option4.draw);
		}
		else if (state4 == 1) {
			window.draw(option4Move.draw);
		}
		else {
			window.draw(option4Pressed.draw);
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