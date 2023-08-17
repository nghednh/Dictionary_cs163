#include "addNewWordScreen.h"
#include "Operation.h"
#include "changeDictionary.h"
extern Trie dictrie[5];
void submitAdding(string word, string def, string typeDictionary, Trie& trie)
{
    ofstream fout("Data/" + typeDictionary + "/document.txt", ios::app);
    fout << word << "\t" << def << '\n';
    fout.close();

    trie.insertWord(word, def);
}

//-------------------Scene-----------------
void addNewWordScreen(RenderWindow& window, string typeDictionary, Trie& trie, Trie& favor_trie, Trie& history_trie)
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
    Info warning = createInfo("arial.ttf", "", 220, 520, 15);
    warning.text.setFillColor(Color(200, 40, 40));
    int warningState = 0;

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
                warningState = 1;
                submitState = 2;
                clickClock.restart();
                cout << trie.searchWord(wordText.text.getString()) << endl;
                if (wordText.text.getString() != "Enter your word please!" && defText.text.getString() != "Enter your definition please!" && !trie.searchWord(wordText.text.getString())) {
                    submitAdding(wordText.text.getString(), defText.text.getString(), typeDictionary, trie);
                    warning.text.setString("Add successfully!");
                }
                else {
                    warning.text.setString("Please check your word again!");
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
                else if (isHere(back.bound, mouse)) {
                    backState = 2;
                    clickClock.restart();
                }
                else if (isHere(submit.bound, mouse)) {
                    check = 0;
                    warningState = 1;
                    submitState = 2;
                    clickClock.restart();
                    if (wordText.text.getString() != "Enter your word please!" && defText.text.getString() != "Enter your definition please!" && !trie.searchWord(wordText.text.getString())) {
                        submitAdding(wordText.text.getString(), defText.text.getString(), typeDictionary, trie);
                        warning.text.setString("Add successfully!");
                    }
                    else {
                        warning.text.setString("Please check your word again!");
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
        if (warningState == 1 && clickClock.getElapsedTime().asMilliseconds() >= 2000) {
            warning.text.setString("");
        }
        if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            changeMenu(window, typeDictionary, trie, favor_trie, history_trie);
        }
        if (engengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            trie = dictrie[0];
            Operation(window, "EngEng", trie, favor_trie, history_trie);
        }
        if (engvieState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            trie = dictrie[1];
            Operation(window, "EngVie", trie, favor_trie, history_trie);
        }
        if (vieengState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            trie = dictrie[2];
            Operation(window, "VieEng", trie, favor_trie, history_trie);
        }
        if (slangState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            trie = dictrie[3];
            Operation(window, "Slang", trie, favor_trie, history_trie);
        }
        if (emoState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            trie = dictrie[4];
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
        window.draw(warning.text);

        window.display();
    }
}

