//#include "Trie.h"
//
//struct button {
//    RectangleShape shape;
//    Color* color = new Color[4];
//    Text text;
//    void set_up(string content, Font font, int sizefont, Color* color, float posX, float posY, float posX_t, float posY_t, Vector2f size) {
//        //Set up rec
//        shape.setPosition(posX, posY);
//        shape.setSize(size);
//        shape.setFillColor(color[0]);
//        //Set up text
//        text.setString(content);
//        text.setCharacterSize(sizefont);
//        text.setPosition(posX_t, posY_t);
//        text.setFillColor(sf::Color::White);
//        //Set up color
//        for (int i = 0; i < 4; i++) {
//            this->color[i] = color[i];
//        }
//    }
//    bool isPressed(RenderWindow& window, Event& e) {
//        Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//        if (shape.getGlobalBounds().contains(mousePos)) {
//            //if (window.pollEvent(e)) {
//            if (e.type == Event::MouseButtonPressed) {
//                return true;
//            }
//            //}
//        }
//        return false;
//    }
//    bool isReleased(RenderWindow& window, Event& e) {
//        Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//        if (shape.getGlobalBounds().contains(mousePos)) {
//            //if (window.pollEvent(e)) {
//            if (e.type == Event::MouseButtonReleased) {
//                return true;
//            }
//            //}
//        }
//        return false;
//    }
//    bool isTouched(RenderWindow& window, Event& e) {
//        Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//        if (shape.getGlobalBounds().contains(mousePos)) {
//            return !(window.pollEvent(e));
//        }
//        return false;
//    }
//    void drawButton(RenderWindow& window, Event& e) {
//        if (isPressed(window, e)) shape.setFillColor(color[2]);
//        else shape.setFillColor(color[0]);
//        window.draw(shape);
//    }
//};
//void viewlistFavor(RenderWindow& window, Trie favor_trie) {
//    vector<string> favor;
//    ifstream fin;
//    fin.open("../Dictionary/favorite.txt");
//    while (!fin.eof()) {
//        string t;
//        getline(fin, t, '\n');
//        if (t != "") favor.push_back(t);
//    }
//    fin.close();
//    //Background
//    sf::Texture scene;
//    scene.loadFromFile("../Dictionary/content/scene.png");
//
//    sf::Sprite spr_scene;
//    spr_scene.setTexture(scene);
//    //Pre & Click_Pre
//    sf::Texture b_pre1, b_pre2, b_pre3;
//    b_pre1.loadFromFile("../Dictionary/content/left.png");
//    b_pre2.loadFromFile("../Dictionary/content/left_point.png");
//    b_pre3.loadFromFile("../Dictionary/content/left_valid.png");
//
//    sf::Sprite prev;
//    prev.setTexture(b_pre1);
//    prev.setPosition(625, 855);
//    prev.scale(Vector2f(2, 2));
//
//    //Next & Click_next
//    sf::Texture b_next1, b_next2, b_next3;
//    b_next1.loadFromFile("../Dictionary/content/right.png");
//    b_next2.loadFromFile("../Dictionary/content/right_point.png");
//    b_next3.loadFromFile("../Dictionary/content/right_valid.png");
//
//    sf::Sprite nxt;
//    nxt.setTexture(b_next1);
//    nxt.setPosition(760, 855);
//    nxt.scale(Vector2f(2, 2));
//
//    //Font
//    sf::Font font;
//    font.loadFromFile("../Font/Oswald-Light.ttf");
//    sf::Font font1;
//    font1.loadFromFile("../Font/Oswald-Regular.ttf");
//
//    //Color
//    Color* color = new Color[4];
//    color[0] = Color(79, 112, 156);
//    color[1] = Color(165, 215, 232);
//    color[2] = Color(45, 67, 86);
//    color[3] = Color(79, 112, 156);
//
//    button title;
//    title.set_up("Favorite list", font, 60, color, 200, 200, 320, 210, Vector2f(500, 100));
//
//    button word;
//    word.set_up("Word", font1, 30, color, 200, 350, 220, 365, Vector2f(500, 70));
//
//    button def;
//    def.set_up("Definition", font1, 30, color, 700, 350, 720, 365, Vector2f(500, 70));
//
//    button item[9];
//    float x = 430;
//    for (int i = 0; i < 8; i++) {
//        item[i].set_up(favor[i], font, 30, color, 200, x, 220, x + 5, Vector2f(500, 50));
//        if (i % 2 != 0) swap(color[0], color[1]);
//        else swap(color[1], color[0]);
//        x += 50;
//    }
//    button mid;
//    mid.set_up("Page 1", font, 25, color, 670, 850, 680, 855, Vector2f(80, 50));
//
//    int page = 1;
//    int sizeofFavor = favor.size();
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//            if (event.type == sf::Event::Closed) window.close();
//            if (prev.getGlobalBounds().contains(mousePos)) {
//                if (event.type == sf::Event::MouseButtonPressed) {
//                    if (page > 1) {
//                        --page;
//                        float x = 430;
//                        int cnt = 0;
//                        mid.text.setString("Page " + to_string(page));
//                        prev.setTexture(b_pre3);
//                        for (int i = 8 * (page - 1); i < 8 * page; i++) {
//                            item[cnt].set_up(favor[i], font, 30, color, 200, x, 220, x + 5, Vector2f(500, 50));
//                            if (i % 2 != 0) swap(color[0], color[1]);
//                            else swap(color[1], color[0]);
//                            x += 50;
//                            cnt++;
//                        }
//                    }
//                    else prev.setTexture(b_pre2);
//                }
//                else prev.setTexture(b_pre1);
//            }
//            else if (nxt.getGlobalBounds().contains(mousePos)) {
//                if (event.type == sf::Event::MouseButtonPressed) {
//                    if (8 * page < favor.size()) {
//                        ++page;
//                        float x = 430;
//                        int cnt = 0;
//                        mid.text.setString("Page " + to_string(page));
//                        nxt.setTexture(b_next3);
//                        for (int i = 8 * (page - 1); i < 8 * page; i++) {
//                            if (i < favor.size()) {
//                                item[cnt].set_up(favor[i], font, 30, color, 200, x, 220, x + 5, Vector2f(500, 50));
//                                if (i % 2 != 0) swap(color[0], color[1]);
//                                else swap(color[1], color[0]);
//                                x += 50;
//                                cnt++;
//                            }
//                            else {
//                                item[cnt].set_up("", font, 30, color, 200, x, 220, x + 5, Vector2f(500, 50));
//                                if (i % 2 != 0) swap(color[0], color[1]);
//                                else swap(color[1], color[0]);
//                                x += 50;
//                                cnt++;
//                            }
//                        }
//                    }
//                    else nxt.setTexture(b_next2);
//                }
//                else nxt.setTexture(b_next1);
//            }
//        }
//        window.clear();
//        window.draw(spr_scene);
//        title.drawButton(window, event);
//        title.text.setFont(font1);
//        window.draw(title.text);
//
//        word.drawButton(window, event);
//        word.text.setFont(font1);
//        window.draw(word.text);
//
//        def.drawButton(window, event);
//        def.text.setFont(font1);
//        window.draw(def.text);
//        for (int i = 0; i < 8; i++) {
//            item[i].drawButton(window, event);
//            item[i].text.setFont(font);
//            window.draw(item[i].text);
//        }
//        window.draw(prev);
//
//        mid.drawButton(window, event);
//        mid.text.setFont(font);
//        window.draw(mid.text);
//
//        window.draw(nxt);
//
//        window.display();
//    }
//}