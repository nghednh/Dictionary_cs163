#include "restoreDictionaryScreen.h"
#include "MainScreen.h"

void restoreDictionary()
{
    ifstream fin("Src/Data/backUp.txt");    // Change after create 5 main mode Vie-Eng, Eng-Vie, Eng-Eng, Slang, Emo
    ofstream fout("Src/Data/mainDocument.txt");     // Change after create 5 main mode Vie-Eng, Eng-Vie, Eng-Eng, Slang, Emo

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


void restoreDictionaryScreen (RenderWindow &app, Trie &trie)
{
    // Tracking
    int state = 0;

    // Clock
    Clock clickClock;

    // Font
    Font font;
    font.loadFromFile("Src/Font/arial_narrow_7.ttf");

    // Button Shape
    RectangleShape askToRestoreButton (Vector2f (900, 50));
    askToRestoreButton.setFillColor (Color::White);
    askToRestoreButton.setPosition (400, 450);
    askToRestoreButton.setOutlineThickness (2);
    askToRestoreButton.setOutlineColor (Color (204, 204, 204));

    RectangleShape submitButton (Vector2f (220, 50));
    submitButton.setFillColor (Color::White);
    submitButton.setPosition (400, 600);
    submitButton.setOutlineThickness (2);
    submitButton.setOutlineColor (Color (157, 209, 255));

    RectangleShape exitButton (Vector2f (220, 50));
    exitButton.setFillColor (Color::White);
    exitButton.setPosition (400, 750);
    exitButton.setOutlineThickness (2);
    exitButton.setOutlineColor (Color (157, 209, 255));

    // Button Text
    Text askToRestoreText ("Do you want to restore your dictionary?", font, 50);
    askToRestoreText.setPosition (410, 445);
    askToRestoreText.setFillColor (Color (136, 136, 136));

    Text submitText ("Submit", font, 50);
    submitText.setPosition (410, 595);
    submitText.setFillColor (Color (52, 142, 254));

    Text exitText ("Exit", font, 50);
    exitText.setPosition (410, 745);
    exitText.setFillColor (Color (52, 142, 254));

    // Screen
    while (app.isOpen()) {
        Event e;

        while (app.pollEvent (e)) {
            if (e.type == Event::Closed) {
                trie.clearAll();
                app.close ();
            }
            else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape) {
                exitButton.setFillColor (Color (202, 216, 229));
                state = 1;
                clickClock.restart();
            }
            else if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter) {
                submitButton.setFillColor(Color (202, 216, 229));
                state = 2;
                clickClock.restart();
            }
            else if (e.type == Event::MouseMoved) {
                Vector2f mousePos = app.mapPixelToCoords (Mouse::getPosition(app));
                if (submitButton.getGlobalBounds ().contains (mousePos))
                {
                    submitButton.setFillColor (Color (225, 241, 255));
                }
                else
                {
                    submitButton.setFillColor (Color::White);
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
                else if (submitButton.getGlobalBounds ().contains (mousePos)) {
                    submitButton.setFillColor(Color (202, 216, 229));
                    state = 2;
                    clickClock.restart();
                }
            }
        }

        if (state == 1 && clickClock.getElapsedTime().asMilliseconds() >= 250) {
            state = 0;
            MainScreen(app, trie);
        }
        else if (state == 2 && clickClock.getElapsedTime().asMilliseconds() >= 250) {
            state = 0;
            restoreDictionary();
            submitButton.setFillColor(Color (225, 241, 255));
        }

        app.clear (Color (96, 169, 255));

        app.draw(askToRestoreButton);
        app.draw(askToRestoreText);

        app.draw(submitButton);
        app.draw(submitText);

        app.draw(exitButton);
        app.draw(exitText);

        app.display ();
    }
}
