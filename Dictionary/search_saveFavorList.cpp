#include "Trie.h"
void search_addfavorite(RenderWindow& window, Trie trie, Trie &favor_trie) {
    sf::Texture scene;
    scene.loadFromFile("../Dictionary/content/scene.png");

    sf::Texture search_bar;
    search_bar.loadFromFile("../Dictionary/content/searchBar.png");

    sf::Texture magni;
    magni.loadFromFile("../Dictionary/content/magnifier.png");

    sf::Texture star;
    star.loadFromFile("../Dictionary/content/star.png");

    sf::Texture starSaved;
    starSaved.loadFromFile("../Dictionary/content/starSaved.png");
    //Sprite
    sf::Sprite spr_scene;
    spr_scene.setTexture(scene);

    sf::Sprite spr_bar;
    spr_bar.setTexture(search_bar);
    spr_bar.setPosition(sf::Vector2f(170, 350));

    sf::Sprite spr_magni;
    spr_magni.setTexture(magni);
    spr_magni.setPosition(sf::Vector2f(180, 357));

    sf::Sprite spr_favor;
    spr_favor.setTexture(star);
    spr_favor.setPosition(1000, 500);

    //Button
    sf::RectangleShape rec_enter;
    rec_enter.setSize(sf::Vector2f(1000, 57));
    rec_enter.setPosition(170, 350);
    rec_enter.setFillColor(sf::Color::Transparent);

    sf::RectangleShape rec_result;
    rec_result.setSize(sf::Vector2f(1000, 400));
    rec_result.setPosition(170, 450);
    rec_result.setFillColor(sf::Color(175, 211, 226));

    sf::CircleShape cir_favor;
    cir_favor.setRadius(30);
    cir_favor.setPosition(1000, 500);
    cir_favor.setFillColor(sf::Color::Transparent);

    sf::Font font;
    font.loadFromFile("../Dictionary/content/Oswald-Light.ttf");

    string user_text;
    string meaning;
    bool check_save = false;
    //Text
    sf::Text dis_text("Search", font, 40);
    dis_text.setPosition(250, 355);
    dis_text.setFillColor(sf::Color(107, 114, 142));

    sf::Text found("", font, 45);
    found.setPosition(180, 460);
    found.setFillColor(sf::Color::Black);

    bool alter = false;
    sf::Color color1(246, 241, 241);
    sf::Color color2(175, 211, 226);
    float x = 100, y = 200;
    //
    bool enter = false;
    bool display_star = false;
    sf::Cursor cursor;
    while (window.isOpen())
    {
        sf::Event event;

        if (!enter && user_text == "") {
            dis_text.setString("Search");
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            //Check Press
            if (event.type == sf::Event::MouseButtonPressed) {
                if (rec_enter.getGlobalBounds().contains(mousePos)) enter = true;
                else enter = false;
            }

            if (enter == true) {
                //Set I-beam cursor
                if (rec_enter.getGlobalBounds().contains(mousePos) && cursor.loadFromSystem(sf::Cursor::Text)) {
                    window.setMouseCursor(cursor);
                }
                else {
                    if (cursor.loadFromSystem(sf::Cursor::Arrow))
                        window.setMouseCursor(cursor);
                }
                //Input the word
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
                    //Check whether word is exist in trie/favor_trie or not, 
                    if (trie.searchWord(user_text)) {
                        meaning = trie.searchWordNode(user_text)->meaning;
                        found.setString(trie.searchWordNode(user_text)->meaning);
                        if (!trie.searchWordNode(user_text)->isFavorite) {
                            spr_favor.setTexture(star);
                            display_star = true;
                        }
                        else {
                            spr_favor.setTexture(starSaved);
                            display_star = true;
                        }
                    }
                    else {
                        found.setString("This word is not exist!");
                        display_star = false;
                    }
                }
                dis_text.setString(user_text + "_");
            }
            //Press favorite button
            if (spr_favor.getGlobalBounds().contains(mousePos)) {
                if (cursor.loadFromSystem(sf::Cursor::Hand)) {
                    window.setMouseCursor(cursor);
                }
                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (trie.searchWordNode(user_text)->isFavorite == false) {
                        check_save = true;
                        trie.searchWordNode(user_text)->isFavorite = true;
                        spr_favor.setTexture(starSaved);
                        display_star = true;
                    }
                    else {
                        check_save = false;
                        trie.searchWordNode(user_text)->isFavorite = false;
                        spr_favor.setTexture(star);
                        display_star = true;
                    }
                }
            }
            else {
                if (cursor.loadFromSystem(sf::Cursor::Arrow)) {
                    window.setMouseCursor(cursor);
                }
            }
        }
        window.clear();
        window.draw(spr_scene);
        window.draw(spr_bar);
        window.draw(spr_magni);
        window.draw(rec_enter);
        window.draw(dis_text);
        window.draw(rec_result);
        if (display_star) {
            window.draw(cir_favor);
            window.draw(spr_favor);
        }
        window.draw(found);
        window.display();
        //Save favorite word to favorite list of words.
        if (check_save) {
            favor_trie.insertWord(user_text, meaning);
            ofstream fout;
            fout.open("../Dictionary/favorite.txt", ios::app);
            fout << user_text << ' ' << meaning;
            fout << '\n';
            fout.close();
            check_save = false;
        }
        else favor_trie.removeWord(user_text);
    }
}