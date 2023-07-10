#include "addNewWordScreen.h"
#include "Operation.h"

void submitAdding (string word, string def, string typeDictionary, Trie &trie)
{
    ofstream fout("Data/" + typeDictionary + "/document.txt", ios::app);
    fout << word << " " << def << '\n';
    fout.close();

    trie.insertWord(word, def);
}

//-------------------Scene-----------------
void addNewWordScreen(RenderWindow& window, string typeDictionary, Trie& trie)
{
    Clock clickClock;
    string tmp = "";
    int check = 0;

    Object screen = createObject("content/scene.png");

    Object enterWordBar = createObject("content/searchBar.png", 200, 360);
    Object enterWordBarMove = createObject("content/searchBarMove.png", 200, 360);
    Object enterWordBarPressed = createObject("content/searchBarPressed.png", 200, 360);
    int enterWordState = 0;

    Object enterDefBar = createObject("content/searchBar.png", 200, 440);
    Object enterDefBarMove = createObject("content/searchBarMove.png", 200, 440);
    Object enterDefBarPressed = createObject("content/searchBarPressed.png", 200, 440);
    int enterDefState = 0;

    Object submit = createObject("content/submit.png", 200, 700);
    Object submitMove = createObject("content/submitMove.png", 200, 700);
    Object submitPressed = createObject("content/submitPressed.png", 200, 700);
    int submitState = 0;

    Object back = createObject("content/back.png", 200, 780);
    Object backMove = createObject("content/backMove.png", 200, 780);
    Object backPressed = createObject("content/backPressed.png", 200, 780);
    int backState = 0;

    Info wordText = createInfo("arial.ttf", "Enter your word please!", 220, 360, 40);
    Info defText = createInfo("arial.ttf", "Enter your definition please!", 220, 440, 40);

    Event e;

    while (window.isOpen()) {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
            else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape) {
                backState = 2;
                clickClock.restart();
            }
            else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Return) {
                check = 0;
                submitState = 2;
                clickClock.restart();
                if (wordText.text.getString() != "Enter your word please!" && defText.text.getString() != "Enter your definition please!" && !trie.searchWord(wordText.text.getString())) {
                    submitAdding(wordText.text.getString(), defText.text.getString(), typeDictionary, trie);
                }
            }
            else if (e.type == Event::MouseMoved) {
                if (isHere(enterWordBar.bound, mouse)) {
                    enterWordState = 1;
                }
                else {
                    enterWordState = 0;
                }
                if (isHere(enterDefBar.bound, mouse)) {
                    enterDefState = 1;
                }
                else {
                    enterDefState = 0;
                }
                if (isHere(submit.bound, mouse)) {
                    submitState = 1;
                }
                else {
                    submitState = 0;
                }
                if (isHere(back.bound, mouse)) {
                    backState = 1;
                }
                else {
                    backState = 0;
                }
            }
            else if (e.type == Event::MouseButtonPressed) {
                if (isHere(back.bound, mouse)) {
                    backState = 2;
                    clickClock.restart();
                }
                else if (isHere(submit.bound, mouse)) {
                    check = 0;
                    submitState = 2;
                    clickClock.restart();
                    if (wordText.text.getString() != "Enter your word please!" && defText.text.getString() != "Enter your definition please!" && !trie.searchWord(wordText.text.getString())) {
                        submitAdding(wordText.text.getString(), defText.text.getString(), typeDictionary, trie);
                    }
                }
                else if (isHere(enterWordBar.bound, mouse)) {
                    enterWordState = 2;
                    clickClock.restart();
                    if (check != 1) {
                        check = 1;
                        tmp = "";
                        wordText.text.setString(tmp);
                    }
                }
                else if (isHere(enterDefBar.bound, mouse)) {
                    enterDefState = 2;
                    clickClock.restart();
                    if (check != 2) {
                        check = 2;
                        tmp = "";
                        defText.text.setString(tmp);
                    }
                }
            }
            else if (e.type == Event::TextEntered && check == 1) {
                if (e.text.unicode < 128 && e.text.unicode != '\b') {
                    tmp += e.text.unicode;
                    wordText.text.setString(tmp);
                }
                else if (e.text.unicode == '\b' && !wordText.text.getString().isEmpty()) {
                    if (tmp.size() > 0) {
                        tmp.pop_back();
                        wordText.text.setString(tmp);
                    }
                    else {
                        wordText.text.setString("");
                    }
                }
            }
            else if (e.type == Event::TextEntered && check == 2) {
                if (e.text.unicode < 128 && e.text.unicode != '\b') {
                    tmp += e.text.unicode;
                    defText.text.setString(tmp);
                }
                else if (e.text.unicode == '\b' && !defText.text.getString().isEmpty()) {
                    if (tmp.size() > 0) {
                        tmp.pop_back();
                        defText.text.setString(tmp);
                    }
                    else {
                        defText.text.setString("");
                    }
                }
            }
        }
        if (enterWordState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            if (isHere(enterWordBar.bound, mouse)) {
                enterWordState = 1;
            }
            else {
                enterWordState = 0;
            }
        }
        if (enterDefState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            if (isHere(enterDefBar.bound, mouse)) {
                enterDefState = 1;
            }
            else {
                enterDefState = 0;
            }
        }
        if (submitState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            if (isHere(submit.bound, mouse)) {
                submitState = 1;
            }
            else {
                submitState = 0;
            }
        }
        if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            Operation(window, typeDictionary, trie);
        }

        window.clear();

        window.draw(screen.draw);

        if (enterWordState == 0) {
            window.draw(enterWordBar.draw);
        }
        else if (enterWordState == 1) {
            window.draw(enterWordBarMove.draw);
        }
        else {
            window.draw(enterWordBarPressed.draw);
        }

        if (enterDefState == 0) {
            window.draw(enterDefBar.draw);
        }
        else if (enterDefState == 1) {
            window.draw(enterDefBarMove.draw);
        }
        else {
            window.draw(enterDefBarPressed.draw);
        }

        if (submitState == 0) {
            window.draw(submit.draw);
        }
        else if (submitState == 1) {
            window.draw(submitMove.draw);
        }
        else {
            window.draw(submitPressed.draw);
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

        window.draw(wordText.text);
        window.draw(defText.text);

        window.display();
    }
}
