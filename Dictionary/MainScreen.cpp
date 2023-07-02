#include "MainScreen.h"
#include "addNewWordScreen.h"
#include "restoreDictionaryScreen.h"

void MainScreen (RenderWindow &app, Trie &trie)
{
    // Ttracking
    int state = 0;

    // Clock
    Clock clickClock;

    // Font
    Font font;
    font.loadFromFile("Src/Font/arial_narrow_7.ttf");

    // Button Shape
    RectangleShape addNewWordButton (Vector2f (220, 50));
    addNewWordButton.setFillColor (Color::White);
    addNewWordButton.setPosition (400, 450);
    addNewWordButton.setOutlineThickness (2);
    addNewWordButton.setOutlineColor (Color (157, 209, 255));

    RectangleShape restoreButton (Vector2f (220, 50));
    restoreButton.setFillColor (Color::White);
    restoreButton.setPosition (400, 600);
    restoreButton.setOutlineThickness (2);
    restoreButton.setOutlineColor (Color (157, 209, 255));

    RectangleShape exitButton (Vector2f (220, 50));
    exitButton.setFillColor (Color::White);
    exitButton.setPosition (400, 750);
    exitButton.setOutlineThickness (2);
    exitButton.setOutlineColor (Color (157, 209, 255));

    // Button Text
    Text addNewWordText ("Add word", font, 50);
    addNewWordText.setPosition (410, 445);
    addNewWordText.setFillColor (Color (52, 142, 254));

    Text restoreText ("Restore", font, 50);
    restoreText.setPosition (410, 595);
    restoreText.setFillColor (Color (52, 142, 254));

    Text exitText ("Exit", font, 50);
    exitText.setPosition (410, 745);
    exitText.setFillColor (Color (52, 142, 254));

    // Generate Trie
    trie.readDatasetToTrie("Src/Data/mainDocument.txt");    // Change after create 5 main mode Vie-Eng, Eng-Vie, Eng-Eng, Slang, Emo

    // Screen
    while (app.isOpen()) {
        Event e;

        while (app.pollEvent (e)) {
            if (e.type == Event::Closed) {
                trie.clearAll();
                app.close ();
            }
            else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape) {
                trie.clearAll();
                app.close ();
            }
            else if (e.type == Event::MouseMoved) {
                Vector2f mousePos = app.mapPixelToCoords (Mouse::getPosition(app));
                if (addNewWordButton.getGlobalBounds ().contains (mousePos))
                {
                    addNewWordButton.setFillColor (Color (225, 241, 255));
                }
                else
                {
                    addNewWordButton.setFillColor (Color::White);
                }
                if (restoreButton.getGlobalBounds ().contains (mousePos))
                {
                    restoreButton.setFillColor (Color (225, 241, 255));
                }
                else
                {
                    restoreButton.setFillColor (Color::White);
                }
                if (exitButton.getGlobalBounds ().contains (mousePos))
                {
                    exitButton.setFillColor (Color (225, 241, 255));
                }
                else
                {
                    exitButton.setFillColor (Color::White);
                }
            }
            else if (e.type == Event::MouseButtonPressed) {
                Vector2f mousePos = app.mapPixelToCoords (Mouse::getPosition(app));
                if (exitButton.getGlobalBounds ().contains (mousePos))
                {
                    exitButton.setFillColor (Color (202, 216, 229));
                    state = 1;
                    clickClock.restart();
                }
                else if (addNewWordButton.getGlobalBounds ().contains (mousePos)) {
                    addNewWordButton.setFillColor (Color (202, 216, 229));
                    state = 2;
                    clickClock.restart();
                }
                else if (restoreButton.getGlobalBounds ().contains (mousePos)) {
                    restoreButton.setFillColor (Color (202, 216, 229));
                    state = 3;
                    clickClock.restart();
                }
            }
        }

        if (state == 1 && clickClock.getElapsedTime().asMilliseconds() >= 250) {
            state = 0;
            trie.clearAll();
            app.close();
        }
        else if (state == 2 && clickClock.getElapsedTime().asMilliseconds() >= 250) {
            state = 0;
            addNewWordScreen (app, trie);
        }
        else if (state == 3 && clickClock.getElapsedTime().asMilliseconds() >= 250) {
            state = 0;
            restoreDictionaryScreen (app, trie);
        }

        app.clear (Color (96, 169, 255));

        app.draw(addNewWordButton);
        app.draw(addNewWordText);

        app.draw(restoreButton);
        app.draw(restoreText);

        app.draw(exitButton);
        app.draw(exitText);

        app.display ();
    }
}
