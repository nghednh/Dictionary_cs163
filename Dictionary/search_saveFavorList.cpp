#include "search_saveFavorList.h"
#include "Operation.h"
void wrapped_text(RectangleShape shape, Text& text) {
    float hei, wid;
    string s = "";
    wid = shape.getGlobalBounds().width;
    hei = shape.getGlobalBounds().height;
    string originalText = text.getString();
    string word;
    string testString = "";
    istringstream iss(originalText);

    while (iss >> word) {
        sf::Text tempText = text;
        testString += word + ' ';
        tempText.setString(testString);
        if (tempText.getGlobalBounds().width > wid - 10) {
            s += '\n';
            testString = word + ' ';
        }
        s += word + ' ';
    }
    text.setString(s + "\n");
}
void display(TrieNode* root, string str, ofstream &fout)
{
    if (root->isEndOfWord)
    {   
        for (int j = 0; j < root->meaning.size(); j++) {
            fout << str << '\t' << root->meaning[j] << '\n';
        }  
    }
    int i;
    for (i = 0; i < sizee; i++)
    {
        if (root->children[i])
        {
            str.push_back(i + ' ');
            display(root->children[i], str, fout);
            str.pop_back();
        }
    }
}
void search_addfavorite(RenderWindow& window, Trie trie, string typeDictionary, Trie favor_trie) {
    Clock clickClock;
    //Scene
    sf::Texture scene;
    scene.loadFromFile("../Dictionary/content/scene.png");
    //Search_bar
    sf::Texture search_bar;
    search_bar.loadFromFile("../Dictionary/content/searchBar.png");
    sf::Texture bar_move;
    bar_move.loadFromFile("../Dictionary/content/searchBarMove.png");
    sf::Texture bar_press;
    bar_press.loadFromFile("../Dictionary/content/searchBarPressed.png");
    //Magni
    sf::Texture magni;
    magni.loadFromFile("../Dictionary/content/magnifier.png");
    //Star
    sf::Texture star;
    star.loadFromFile("../Dictionary/content/star.png");
    sf::Texture starSaved;
    starSaved.loadFromFile("../Dictionary/content/starSaved.png");
    //Back
    Object back = createObject("content/back.png", 200, 980);
    Object backMove = createObject("content/backMove.png", 200, 980);
    Object backPressed = createObject("content/backPressed.png", 200, 980);
    int backState = 0;
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
    spr_favor.setPosition(1200, 450);

    //Button
    sf::RectangleShape rec_enter;
    rec_enter.setSize(sf::Vector2f(1000, 60));
    rec_enter.setPosition(170, 350);
    rec_enter.setFillColor(sf::Color::Transparent);

    sf::RectangleShape rec_result;
    rec_result.setSize(sf::Vector2f(1000, 500));
    rec_result.setPosition(170, 450);
    rec_result.setFillColor(sf::Color(175, 211, 226));

    //View
    sf::View static_view(sf::FloatRect(0, 0, 1740, 1080));
    window.setView(static_view);

    sf::View view(sf::FloatRect(170, 450, 1000, 500));
    view.setViewport(sf::FloatRect(0.0977f, 0.4166f, 0.5747f, 0.4629f));
    window.setView(view);

    float scrollSpeed = 20.0f;

    sf::Font font;
    font.loadFromFile("content/Oswald-Light.ttf");
    string user_text;
    //Text
    sf::Text dis_text("Search", font, 40);
    dis_text.setPosition(250, 355);
    dis_text.setFillColor(sf::Color(107, 114, 142));

    vector<sf::Text> found;
    vector<string> meaning;
    Color* color = new Color[1];
    color[0] = sf::Color::Black;

    bool alter = false;
    sf::Color color1(246, 241, 241);
    sf::Color color2(175, 211, 226);
    float totalHeight = 0.0f;
    float y_text = 0;
    float cnt_move = 0;
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
            Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                backState = 2;
                clickClock.restart();
            }
            else if (event.type == Event::MouseMoved) {
                if (isHere(back.bound, mousePos)) {
                    backState = 1;
                }
                else {
                    backState = 0;
                }
            }
            //Check Touch Search_bar
            if (rec_enter.getGlobalBounds().contains(mousePos)) spr_bar.setTexture(bar_move);
            else spr_bar.setTexture(search_bar);
            //Check Press
            if (event.type == sf::Event::MouseButtonPressed) {
                if (isHere(back.bound, mousePos)) {
                    clickClock.restart();
                    backState = 2;
                }
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
                        found.clear();
                        cnt_move = 0;
                        totalHeight = 0.0f;
                        meaning = trie.searchWordNode(user_text)->meaning;
                        for (const auto& data : meaning)
                        {
                            sf::Text text(data, font, 30);
                            text.setFillColor(sf::Color::Black);
                            wrapped_text(rec_result, text);
                            totalHeight += text.getLocalBounds().height;
                            found.push_back(text);
                        }
                        sf::Text line("\n", font, 30);
                        totalHeight -= line.getLocalBounds().height;

                        view.setCenter(1000 / 2, (totalHeight) / 2);
                        y_text = view.getCenter().y - view.getSize().y / 2;

                        if (!favor_trie.searchWord(user_text)) {
                            spr_favor.setTexture(star);
                            display_star = true;
                        }
                        else {
                            spr_favor.setTexture(starSaved);
                            display_star = true;
                        }

                    }
                    else {
                        found.clear();
                        totalHeight = 0.0f;
                        sf::Text text("This word is not exist!", font, 30);
                        text.setFillColor(sf::Color::Black);
                        found.push_back(text);
                        display_star = false;
                    }
                }
                dis_text.setString(user_text + "_");
            }
            //Move the list data
            if (rec_result.getGlobalBounds().contains(mousePos)) {
                if (event.type == sf::Event::MouseWheelScrolled) {
                    // Check if the mouse is within the scrollable area
                    float x = mousePos.x / sf::Vector2f(window.getSize()).x;
                    float y = mousePos.y / sf::Vector2f(window.getSize()).y;
                    if (view.getViewport().contains(Vector2f(x, y)))
                    {
                        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                        {
                            float delta = scrollSpeed * event.mouseWheelScroll.delta;
                            cnt_move += delta;
                            if (cnt_move > 0) {
                                cnt_move -= delta;
                                continue;
                            }
                            if (cnt_move < 0) {
                                if (cnt_move < -totalHeight + rec_result.getSize().y - scrollSpeed - 20) {
                                    cnt_move -= delta;
                                    continue;
                                }
                            }
                            view.move(0, -scrollSpeed * event.mouseWheelScroll.delta);

                        }
                    }
                }
            }
            //Press favorite button
            if (spr_favor.getGlobalBounds().contains(mousePos)) {
                if (cursor.loadFromSystem(sf::Cursor::Hand)) {
                    window.setMouseCursor(cursor);
                }
                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (trie.searchWordNode(user_text)->isFavorite == false) {
                        trie.searchWordNode(user_text)->isFavorite = true;
                        for (int i = 0; i < meaning.size(); i++) {
                            favor_trie.insertWord(user_text, meaning[i]);
                        }
                        spr_favor.setTexture(starSaved);
                        display_star = true;
                    }
                    else {
                        trie.searchWordNode(user_text)->isFavorite = false;
                        favor_trie.removeWord(user_text);
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
        if (backState == 2 && clickClock.getElapsedTime().asMilliseconds() >= 100) {
            string str = "";
            ofstream fout;
            fout.open("Data/" + typeDictionary + "/favorite.txt");
            if (fout.is_open()) display(favor_trie.getRoot(), str, fout);
            fout.close();
            Operation(window, typeDictionary, trie, favor_trie);
        }
        window.clear();
        window.draw(spr_scene);
        window.draw(spr_bar);
        window.draw(spr_magni);
        window.draw(rec_enter);
        window.draw(dis_text);
        window.draw(rec_result);
        if (display_star) {
            window.draw(spr_favor);
        }
        window.setView(view);
        sf::FloatRect viewBounds = view.getViewport();
        float sum = y_text + 10;
        for (int i = 0; i < found.size(); i++)
        {
            found[i].setPosition(viewBounds.left * 100, sum);
            sum += found[i].getLocalBounds().height;
            window.draw(found[i]);
        }
        window.setView(static_view);
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