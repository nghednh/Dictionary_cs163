#include "addNewWordScreen.h"
#include "MainScreen.h"

void submitAdding (string word, string def, Trie &trie)
{
    ofstream fout("Src/Data/mainDocument.txt", ios::app);    // Change after create 5 main mode Vie-Eng, Eng-Vie, Eng-Eng, Slang, Emo
    fout << word << " " << def << '\n';
    fout.close();

    trie.insertWord(word, def);
}

void addNewWordScreen(RenderWindow &app, Trie &trie)
{
    // Tracking
    string tmp;
    int state = 0;      // change button color
    int check = 0;      // change text box input

    // Clock
    Clock clickClock;

    // Font
    Font font;
    font.loadFromFile("Src/Font/arial_narrow_7.ttf");

    // Button
    RectangleShape requireToEnter (Vector2f (700, 75));
    requireToEnter.setFillColor (Color::White);
    requireToEnter.setPosition (400, 300);
    requireToEnter.setOutlineThickness (2);
    requireToEnter.setOutlineColor (Color (204, 204, 204));

    RectangleShape enterWordButton (Vector2f (500, 30));
    enterWordButton.setFillColor (Color::White);
    enterWordButton.setPosition (400, 450);
    enterWordButton.setOutlineThickness (2);
    enterWordButton.setOutlineColor (Color (157, 209, 255));

    RectangleShape defButton (Vector2f (500, 30));
    defButton.setFillColor (Color::White);
    defButton.setPosition (400, 550);
    defButton.setOutlineThickness (2);
    defButton.setOutlineColor (Color (157, 209, 255));

    RectangleShape submitButton (Vector2f (200, 30));
    submitButton.setFillColor (Color::White);
    submitButton.setPosition (400, 850);
    submitButton.setOutlineThickness (2);
    submitButton.setOutlineColor (Color (157, 209, 255));

    RectangleShape exitButton (Vector2f (200, 30));
    exitButton.setFillColor (Color::White);
    exitButton.setPosition (400, 1000);
    exitButton.setOutlineThickness (2);
    exitButton.setOutlineColor(Color (157, 209, 255));

    // Text
    Text requireToEnterText ("Please enter your word and def", font, 50);
    requireToEnterText.setPosition (410, 305);
    requireToEnterText.setFillColor (Color (136, 136, 136));

    Text enterWordText ("Enter your word!", font, 25);
    enterWordText.setPosition (410, 450);
    enterWordText.setFillColor (Color (52, 142, 254));

    Text defText ("Definition of the word!", font, 25);
    defText.setPosition (410, 550);
    defText.setFillColor (Color (52, 142, 254));

    Text submitText ("Submit!", font, 25);
    submitText.setPosition (410, 850);
    submitText.setFillColor (Color (52, 142, 254));

    Text exitText ("Return", font, 25);
    exitText.setPosition (410, 1000);
    exitText.setFillColor (Color (52, 142, 254));

    Text warning ("", font, 15);
    warning.setPosition (410, 885);
    warning.setFillColor (Color (198, 40, 40));

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
                check = 0;
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
                if (enterWordButton.getGlobalBounds ().contains (mousePos))
                {
                    enterWordButton.setFillColor (Color (225, 241, 255));
                }
                else
                {
                    enterWordButton.setFillColor (Color::White);
                }
                if (defButton.getGlobalBounds ().contains (mousePos))
                {
                    defButton.setFillColor (Color (225, 241, 255));
                }
                else
                {
                    defButton.setFillColor (Color::White);
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
                    check = 0;
                    clickClock.restart();
                }
                else if (enterWordButton.getGlobalBounds ().contains (mousePos)) {
                    enterWordButton.setFillColor(Color (202, 216, 229));
                    state = 3;
                    if (check != 1) {
                        check = 1;
                        tmp = "";
                        enterWordText.setString(tmp);
                    }
                    clickClock.restart();
                }
                else if (defButton.getGlobalBounds ().contains (mousePos)) {
                    defButton.setFillColor(Color (202, 216, 229));
                    state = 4;
                    if (check != 2) {
                        check = 2;
                        tmp = "";
                        defText.setString(tmp);
                    }
                    clickClock.restart();
                }
            }
            else if (e.type == Event::TextEntered && check == 1)
            {
                if (e.text.unicode < 128 && e.text.unicode != '\b') {
                    tmp += e.text.unicode;
                    enterWordText.setString (tmp);
                }
                else if (e.text.unicode == '\b' && !enterWordText.getString().isEmpty()) {
                    if (tmp.size() > 0) {
                        tmp.pop_back ();
                        enterWordText.setString (tmp);
                    }
                    else {
                        enterWordText.setString ("");
                    }
                }
            }
            else if (e.type == Event::TextEntered && check == 2)
            {
                if (e.text.unicode < 128 && e.text.unicode != '\b') {
                    tmp += e.text.unicode;
                    defText.setString (tmp);
                }
                else if (e.text.unicode == '\b' && !defText.getString().isEmpty()) {
                    if (tmp.size() > 0) {
                        tmp.pop_back ();
                        defText.setString (tmp);
                    }
                    else {
                        defText.setString ("");
                    }
                }
            }
        }

        if (state == 1 && clickClock.getElapsedTime().asMilliseconds() >= 250) {
            state = 0;
            MainScreen(app, trie);
        }
        else if (state == 2 && clickClock.getElapsedTime().asMilliseconds() >= 250) {
            state = 0;
            if (enterWordText.getString() != "Enter your word!" && defText.getString() != "Definition of the word!" && !trie.searchWord(enterWordText.getString())) {
                submitAdding(enterWordText.getString(), defText.getString(), trie);
            }
            submitButton.setFillColor(Color (225, 241, 255));
        }
        else if (state == 3 && clickClock.getElapsedTime().asMilliseconds() >= 250) {
            state = 0;

            enterWordButton.setFillColor(Color (225, 241, 255));
        }
        else if (state == 4 && clickClock.getElapsedTime().asMilliseconds() >= 250) {
            state = 0;

            defButton.setFillColor(Color (225, 241, 255));
        }

        app.clear (Color (96, 169, 255));

        app.draw(requireToEnter);
        app.draw(requireToEnterText);

        app.draw(submitButton);
        app.draw(submitText);

        app.draw(exitButton);
        app.draw(exitText);

        app.draw(enterWordButton);
        app.draw(enterWordText);

        app.draw(defButton);
        app.draw(defText);

        app.display ();
    }
}
