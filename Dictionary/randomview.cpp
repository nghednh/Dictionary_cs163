#include "randomview.h"
#include "Operation.h"
#include "changeDictionary.h"
#include "game.h"
#include "search.h"

//-------------------Scene-----------------
void randomView(RenderWindow& window, string typeDictionary, Trie* trie, Trie& favor_trie, Trie& history_trie)
{
    Clock clickClock;
    Object screen = createObject("content/scene.png");
    Object enterWordBar = createObject("content/searchBar.png", 200, 360);
    Object enterWordBar2 = createObject("content/searchBar2.png", 200, 440);
    Object back = createObject("content/back.png", 200, 780);
    Object backMove = createObject("content/backMove.png", 200, 780);
    Object backPressed = createObject("content/backPressed.png", 200, 780);
    Object retry = createObject("content/retry.png", 450, 780);
    Object retryMove = createObject("content/retryMove.png", 450, 780);
    Object retryPressed = createObject("content/retryPressed.png", 450, 780);
    RectangleShape box(Vector2f(1000, 200));
    int retryState = 0;
    TrieNode* tr;
    chooseDef(trie, tr);
    string word = tr->word;
    string meaning = buffer(tr);
    Info wordText = createInfo("arial.ttf", word, 220, 360, 40);
    Info wordText2 = createInfo("arial.ttf", meaning, 220, 450, 40);
    wrapped_text(box, wordText2.text);
    int backState = 0;
    Event e;
    Cursor cursor;
    vector<Sprite> button {back.draw, retry.draw};
    bool handstate = false;
    if (cursor.loadFromSystem(Cursor::Arrow)) {
        window.setMouseCursor(cursor);
    }

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
            else if (e.type == Event::MouseMoved) {
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
            }
            else if (e.type == Event::MouseButtonPressed) {
                
                if (isHere(back.bound, mouse)) {
                    backState = 2;
                    clickClock.restart();
                }
                else if (isHere(retry.bound, mouse)) {
                    retryState = 2;
                    clickClock.restart();
                }
            }
        }
        setCursor(window, button, handstate, mouse, cursor);
        window.clear();
        
        window.draw(screen.draw);
        
        window.draw(enterWordBar.draw);
        window.draw(enterWordBar2.draw);
        window.draw(wordText.text);
        window.draw(wordText2.text);
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
        window.display();
        if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            searchMenu(window, typeDictionary, trie, favor_trie, history_trie);
        }
        if (retryState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            string tmp = tr->word;
            while (tmp == tr->word) {
                chooseDef(trie, tr);
            }
            word = tr->word;
            meaning = buffer(tr);
            wordText.text.setString(word);
            wordText2.text.setString(meaning);
            wrapped_text(box, wordText2.text);
            retryState = 0;
        }
    }
}
void flashcardHideDef(RenderWindow& window, string typeDictionary, Trie* trie, Trie& favor_trie, Trie& history_trie)
{
    Clock clickClock;
    Object screen = createObject("content/scene.png");
    Object enterWordBar = createObject("content/searchBar.png", 200, 360);
    Object enterWordBar2 = createObject("content/searchBar2.png", 200, 440);
    Object back = createObject("content/back.png", 200, 780);
    Object backMove = createObject("content/backMove.png", 200, 780);
    Object backPressed = createObject("content/backPressed.png", 200, 780);
    Object retry = createObject("content/retry.png", 450, 780);
    Object retryMove = createObject("content/retryMove.png", 450, 780);
    Object retryPressed = createObject("content/retryPressed.png", 450, 780);
    Object appe = createObject("content/return.png", 1230, 500);
    Object appe2 = createObject("content/return1.png", 1230, 500);
    int appestate = 0;
    RectangleShape box(Vector2f(1000, 200));
    int retryState = 0;
    TrieNode* tr;
    chooseDef(trie, tr);
    string word = tr->word;
    string meaning = buffer(tr);
    Info wordText = createInfo("arial.ttf", word, 220, 360, 40);
    Info wordText2 = createInfo("arial.ttf", meaning, 220, 450, 40);
    wrapped_text(box, wordText2.text);
    int backState = 0;
    Event e;
    Cursor cursor;
    vector<Sprite> button {appe.draw, back.draw, retry.draw};
    bool handstate = false;
    if (cursor.loadFromSystem(Cursor::Arrow)) {
        window.setMouseCursor(cursor);
    }

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
            else if (e.type == Event::MouseMoved) {
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
            }
            else if (e.type == Event::MouseButtonPressed) {

                if (isHere(back.bound, mouse)) {
                    backState = 2;
                    clickClock.restart();
                }
                else if (isHere(retry.bound, mouse)) {
                    retryState = 2;
                    appestate = 0;
                    clickClock.restart();
                }
                else if (isHere(appe.bound, mouse)) {
                    if (appestate == 0) {
                        appestate = 1;
                    }
                    else appestate = 0;

                    clickClock.restart();
                }
            }
        }
        setCursor(window, button, handstate, mouse, cursor);
        window.clear();

        window.draw(screen.draw);

        window.draw(enterWordBar.draw);
        window.draw(enterWordBar2.draw);
        window.draw(wordText.text);
        if (appestate == 1) window.draw(wordText2.text);
        if (appestate == 0) {
            window.draw(appe.draw);
        }
        else {
            window.draw(appe2.draw);
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
        window.display();
        if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            gameMenu(window, typeDictionary, trie, favor_trie, history_trie);
        }
        if (retryState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            string tmp = tr->word;
            while (tmp == tr->word) {
                chooseDef(trie, tr);
            }
            word = tr->word;
            meaning = buffer(tr);
            wordText.text.setString(word);
            wordText2.text.setString(meaning);
            wrapped_text(box, wordText2.text);
            retryState = 0;
        }
    }
}
void flashcardHideWord(RenderWindow& window, string typeDictionary, Trie* trie, Trie& favor_trie, Trie& history_trie)
{
    Clock clickClock;
    Object screen = createObject("content/scene.png");
    Object enterWordBar = createObject("content/searchBar.png", 200, 360);
    Object enterWordBar2 = createObject("content/searchBar2.png", 200, 440);
    Object back = createObject("content/back.png", 200, 780);
    Object backMove = createObject("content/backMove.png", 200, 780);
    Object backPressed = createObject("content/backPressed.png", 200, 780);
    Object retry = createObject("content/retry.png", 450, 780);
    Object retryMove = createObject("content/retryMove.png", 450, 780);
    Object retryPressed = createObject("content/retryPressed.png", 450, 780);
    Object appe = createObject("content/return.png", 1230, 351);
    Object appe2 = createObject("content/return1.png", 1230, 351);
    int appestate = 0;
    RectangleShape box(Vector2f(1000, 200));
    int retryState = 0;
    TrieNode* tr;
    chooseDef(trie, tr);
    string word = tr->word;
    string meaning = buffer(tr);
    Info wordText = createInfo("arial.ttf", word, 220, 360, 40);
    Info wordText2 = createInfo("arial.ttf", meaning, 220, 450, 40);
    wrapped_text(box, wordText2.text);
    int backState = 0;
    Event e;
    Cursor cursor;
    vector<Sprite> button {appe.draw, back.draw, retry.draw};
    bool handstate = false;
    if (cursor.loadFromSystem(Cursor::Arrow)) {
        window.setMouseCursor(cursor);
    }

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
            else if (e.type == Event::MouseMoved) {
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
            }
            else if (e.type == Event::MouseButtonPressed) {

                if (isHere(back.bound, mouse)) {
                    backState = 2;
                    clickClock.restart();
                }
                else if (isHere(retry.bound, mouse)) {
                    retryState = 2;
                    appestate = 0;
                    clickClock.restart();
                }
                else if (isHere(appe.bound, mouse)) {
                    if (appestate == 0) {
                        appestate = 1;
                    }
                    else appestate = 0;

                    clickClock.restart();
                }
            }
        }
        setCursor(window, button, handstate, mouse, cursor);
        window.clear();

        window.draw(screen.draw);

        window.draw(enterWordBar.draw);
        window.draw(enterWordBar2.draw);
        if (appestate == 1) window.draw(wordText.text);
        window.draw(wordText2.text);
        if (appestate == 0) {
            window.draw(appe.draw);
        }
        else {
            window.draw(appe2.draw);
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
        window.display();
        if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            gameMenu(window, typeDictionary, trie, favor_trie, history_trie);
        }
        if (retryState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            string tmp = tr->word;
            while (tmp == tr->word) {
                chooseDef(trie, tr);
            }
            word = tr->word;
            meaning = buffer(tr);
            wordText.text.setString(word);
            wordText2.text.setString(meaning);
            wrapped_text(box, wordText2.text);
            retryState = 0;
        }
    }
}