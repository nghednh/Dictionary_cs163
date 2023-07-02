#include "MainScreen.h"

void search_addfavorite(RenderWindow& window, Trie trie, Trie& favor_trie) {

    sf::RectangleShape rec;
    rec.setSize(sf::Vector2f(200, 70));
    rec.setPosition(100, 50);

    sf::RectangleShape rec_enter;
    rec_enter.setSize(sf::Vector2f(1500, 70));
    rec_enter.setPosition(300, 50);
    rec_enter.setFillColor(sf::Color(20, 108, 148));

    sf::RectangleShape rec_result;
    rec_result.setSize(sf::Vector2f(1700, 800));
    rec_result.setPosition(100, 200);
    rec_result.setFillColor(sf::Color(175, 211, 226));

    sf::RectangleShape rec_favor;
    rec_favor.setSize(sf::Vector2f(300, 50));
    rec_favor.setPosition(1400, 300);
    rec_favor.setFillColor(sf::Color(246, 241, 241));

    sf::Font font;
    font.loadFromFile("../Font/arial_narrow_7.ttf");

    string user_text;
    string meaning;
    bool check_save = false;
    sf::Text dis_text("", font, 50);
    dis_text.setPosition(350, 50);
    dis_text.setFillColor(sf::Color::White);

    sf::Text favor_text("Save to favorite list", font, 30);
    favor_text.setPosition(1415, 305);
    favor_text.setFillColor(sf::Color::Black);

    sf::Text found("", font, 45);
    found.setPosition(120, 220);
    found.setFillColor(sf::Color::Black);

    bool alter = false;
    sf::Color color1(246, 241, 241);
    sf::Color color2(175, 211, 226);
    float x = 100, y = 200;
    //
    sf::RectangleShape row;
    row.setSize(sf::Vector2f(1700, 80));
    row.setPosition(x, y);

    sf::Text text("", font, 45);
    text.setPosition(x, y);
    text.setFillColor(sf::Color::Black);
    //
    bool enter = false;
    sf::Cursor cursor;
    while (window.isOpen())
    {
        sf::Event event;

        if (!enter) {
            dis_text.setString(user_text);
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (event.type == sf::Event::MouseButtonPressed) {
                if (rec_enter.getGlobalBounds().contains(mousePos)) enter = true;
                else enter = false;
            }
            if (enter == true) {
                if (rec_enter.getGlobalBounds().contains(mousePos) && cursor.loadFromSystem(sf::Cursor::Text)) {
                    window.setMouseCursor(cursor);
                }
                else {
                    if (cursor.loadFromSystem(sf::Cursor::Arrow))
                        window.setMouseCursor(cursor);
                }
                if (event.type == Event::TextEntered) {
                    if (event.text.unicode < 128 && event.text.unicode != '\b' && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) == false) {
                        user_text += event.text.unicode;
                        dis_text.setString(user_text + "_");
                    }
                    else if (event.text.unicode == '\b' && !dis_text.getString().isEmpty()) {
                        if (user_text.size() > 0) {
                            user_text.pop_back();
                        }
                    }
                    if (trie.search(user_text)) {
                        meaning = trie.search(user_text)->meaning;
                        found.setString(trie.search(user_text)->meaning);
                        if (!trie.search(user_text)->isFavorite) {
                            favor_text.setString("Save to favorite list");
                            rec_favor.setFillColor(sf::Color(246, 241, 241));
                        }
                        else {
                            favor_text.setString("Saved");
                        }
                    }
                    else {
                        found.setString("This word is not exist!");
                        favor_text.setString("");
                        rec_favor.setFillColor(sf::Color(246, 241, 241));
                    }
                }
                dis_text.setString(user_text + "_");
            }
            if (rec_favor.getGlobalBounds().contains(mousePos)) {
                if (cursor.loadFromSystem(sf::Cursor::Hand)) {
                    window.setMouseCursor(cursor);
                }
                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    check_save = true;
                    trie.search(user_text)->isFavorite = true;
                    favor_text.setString("Saved");
                    rec_favor.setFillColor(sf::Color(20, 108, 148));
                }
            }
            else {
                if (cursor.loadFromSystem(sf::Cursor::Arrow)) {
                    window.setMouseCursor(cursor);
                }
            }
        }
        window.clear();
        window.draw(rec);
        window.draw(rec_enter);
        window.draw(dis_text);
        window.draw(rec_result);
        window.draw(found);
        window.draw(rec_favor);
        window.draw(favor_text);
        window.display();
        if (check_save) {
            favor_trie.insert(user_text, meaning);
            ofstream fout;
            fout.open("../Dictionary/favorite.txt", ios::app);
            cout << user_text << ' ' << meaning << '\n';
            fout << user_text << ' ' << meaning;
            fout << '\n';
            fout.close();
            window.draw(text);
            check_save = false;
        }
    }
}