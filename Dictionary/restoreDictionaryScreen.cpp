#include "restoreDictionaryScreen.h"
#include "Operation.h"

void restoreDictionary(string typeDictionary)
{
    ifstream fin("Data/" + typeDictionary + "/backup.txt");
    ofstream fout("Data/" + typeDictionary + "/document.txt");

    if (fin && fout) {
        string line;
        while (getline(fin, line)) {
            fout << line << '\n';
        }
    }
    else {
        cout << "Error opening files." << endl;
    }

    fin.close();
    fout.close();
}

void restoreDictionaryScreen(RenderWindow& window, string typeDictionary, Trie& trie)
{
    Clock clickClock;

    Object screen = createObject("content/scene.png");
    Object askToReset = createObject("content/searchBar.png", 200, 360);
    Info resetText = createInfo("arial.ttf", "Do you want to reset your " + typeDictionary + " Dictionary?", 220, 360, 40);

    Object submit = createObject("content/submit.png", 200, 700);
    Object submitMove = createObject("content/submitMove.png", 200, 700);
    Object submitPressed = createObject("content/submitPressed.png", 200, 700);
    int submitState = 0;

    Object back = createObject("content/back.png", 200, 780);
    Object backMove = createObject("content/backMove.png", 200, 780);
    Object backPressed = createObject("content/backPressed.png", 200, 780);
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
            else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Return) {
                restoreDictionary(typeDictionary);
                submitState = 2;
                clickClock.restart();
            }
            else if (e.type == Event::MouseMoved) {
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
                    restoreDictionary(typeDictionary);
                    submitState = 2;
                    clickClock.restart();
                }
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
        window.draw(askToReset.draw);
        window.draw(resetText.text);

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

        window.display();
    }
}

