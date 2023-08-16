#include "randomview.h"
#include "Operation.h"
#include "changeDictionary.h"

//-------------------Scene-----------------
void randomView(RenderWindow& window, string typeDictionary, Trie& trie, Trie& favor_trie, Trie& history_trie)
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
    int retryState = 0;
    TrieNode* tr = trie.getRandomWordTrue();
    string word = tr->word;
    string meaning = tr->meaning[0];
    Info wordText = createInfo("arial.ttf", word, 220, 360, 40);
    Info wordText2 = createInfo("arial.ttf", meaning, 220, 450, 40);
    int backState = 0;
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
            Operation(window, typeDictionary, trie, favor_trie, history_trie);
        }
        if (retryState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            tr = trie.getRandomWordWrong(tr,nullptr,nullptr);
            word = tr->word;
            meaning = tr->meaning[0];
            wordText.text.setString(word);
            wordText2.text.setString(meaning);
            retryState = 0;
        }
    }
}
