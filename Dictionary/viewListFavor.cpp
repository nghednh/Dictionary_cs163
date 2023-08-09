#include "viewListFavor.h"
#include "search_saveFavorList.h"
#include "Operation.h"

string hiden_text(float width, Text text) {
    string s = "";
    string originalText = text.getString();
    string word;
    string testString = "";
    istringstream iss(originalText);

    while (iss >> word) {
        sf::Text tempText = text;
        testString += word + ' ';
        tempText.setString(testString);
        if (tempText.getGlobalBounds().width > width - 40) {
            s += "...";
            return s;
        }
        s += word + ' ';
    }
    return s;
}
void viewlistFavor(RenderWindow& window, string typeDictionary, Trie& trie, Trie favor_trie) {
    vector<string> favor_word;
    vector<string> favor_def;
    ifstream fin;
    fin.open("Data/" + typeDictionary +  "/favorite.txt");
    cout << fin.is_open(); 
    string line;
    while (getline(fin, line, '\n')) {
        int i = 0;
        string word = "", meaning = "";
        while (line[i] != '\0') {
            if (line[i] != '\t') word += line[i];
            else break;
            i++;
        }
        i++;
        while (line[i] != '\0') {
            meaning += line[i];
            i++;
        }
        favor_word.push_back(word);
        favor_def.push_back(meaning);
    }
    fin.close();
    //Background
    sf::Texture scene;
    scene.loadFromFile("../Dictionary/content/favorite_scene.png");

    sf::Sprite spr_scene;
    spr_scene.setTexture(scene);
    //Pre & Click_Pre
    sf::Texture b_pre1, b_pre2, b_pre3;
    b_pre1.loadFromFile("../Dictionary/content/left.png");
    b_pre2.loadFromFile("../Dictionary/content/left_point.png");
    b_pre3.loadFromFile("../Dictionary/content/left_valid.png");

    sf::Sprite prev;
    prev.setTexture(b_pre1);
    prev.setPosition(825, 1005);
    prev.scale(Vector2f(2, 2));

    //Next & Click_next
    sf::Texture b_next1, b_next2, b_next3;
    b_next1.loadFromFile("../Dictionary/content/right.png");
    b_next2.loadFromFile("../Dictionary/content/right_point.png");
    b_next3.loadFromFile("../Dictionary/content/right_valid.png");

    sf::Sprite nxt;
    nxt.setTexture(b_next1);
    nxt.setPosition(960, 1005);
    nxt.scale(Vector2f(2, 2));
    //Bin 
    sf::Texture bin;
    bin.loadFromFile("../Dictionary/content/bin.png");
    
    Sprite* bins = new Sprite[11];
    for (int i = 0; i < 11; i++) {
        bins[i].setTexture(bin);
    }
    //Font
    sf::Font font;
    font.loadFromFile("content/Oswald-Light.ttf");
    sf::Font font1;
    font1.loadFromFile("content/Oswald-Regular.ttf");

    //Color
    Color* color = new Color[4];
    color[1] = Color(236, 248, 249);
    color[0] = Color(165, 215, 232);
    color[2] = Color(45, 67, 86);
    color[3] = Color(79, 112, 156);

    Color* color_touch = new Color[2];
    color_touch[1] = Color(226, 246, 202);
    color_touch[0] = Color(248, 253, 207);

    button word;
    word.set_up("Word", font1, 30, color, 200, 350, 220, 365, Vector2f(300, 70));

    button def;
    def.set_up("Definition", font1, 30, color, 500, 350, 720, 365, Vector2f(950, 70));

    button item[11];
    button item_def[11];
    string full_def[11];

    bool display_def = false;
    sf::RectangleShape rec_dis;
    rec_dis.setSize(sf::Vector2f(700, 150));
    rec_dis.setFillColor(color[3]);

    sf::Text dis_text("", font, 30);
    dis_text.setFillColor(sf::Color::White);
    //Back
    float x = 430;
    for (int i = 0; i < 11; i++) {
        if (i < favor_word.size()) {
            item[i].set_up(favor_word[i], font, 30, color, 200, x, 220, x + 5, Vector2f(300, 50));
            sf::Text text(favor_def[i], font, 30);
            item_def[i].set_up(hiden_text(950, text), font, 30, color, 500, x, 520, x + 5, Vector2f(950, 50));
            bins[i].setPosition(1460, x + 5);
            full_def[i] = favor_def[i];
        }
        else {
            item[i].set_up("", font, 30, color, 200, x, 220, x + 5, Vector2f(300, 50));
            item_def[i].set_up("", font, 30, color, 500, x, 520, x + 5, Vector2f(950, 50));
        }
        if (i % 2 != 0) swap(color[0], color[1]);
        else swap(color[1], color[0]);
        x += 50;
    }
    button mid;
    mid.set_up("Page 1", font, 25, color, 870, 1000, 880, 1005, Vector2f(80, 50));

    int page = 1;
    int sizeofFavor_word = favor_word.size();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            display_def = false;
            Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                Operation(window, typeDictionary, trie, favor_trie);
            }
            if (prev.getGlobalBounds().contains(mousePos)) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (page > 1) {
                        --page;
                        float x = 430;
                        int cnt = 0;
                        mid.text.setString("Page " + to_string(page));
                        prev.setTexture(b_pre3);
                        for (int i = 11 * (page - 1); i < 11 * page; i++) {
                            item[cnt].set_up(favor_word[i], font, 30, color, 200, x, 220, x + 5, Vector2f(500, 50));
                            sf::Text text(favor_def[i], font, 30);
                            item_def[cnt].set_up(hiden_text(950, text), font, 30, color, 500, x, 520, x + 5, Vector2f(950, 50));
                            full_def[cnt] = favor_def[i];
                            if (i % 2 != 0) swap(color[0], color[1]);
                            else swap(color[1], color[0]);
                            x += 50;
                            cnt++;
                        }
                    }
                    else prev.setTexture(b_pre2);
                }
                else prev.setTexture(b_pre1);
            }
            else if (nxt.getGlobalBounds().contains(mousePos)) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (11 * page < favor_word.size()) {
                        ++page;
                        float x = 430;
                        int cnt = 0;
                        mid.text.setString("Page " + to_string(page));
                        nxt.setTexture(b_next3);
                        for (int i = 11 * (page - 1); i < 11 * page; i++) {
                            if (i < favor_word.size()) {
                                item[cnt].set_up(favor_word[i], font, 30, color, 200, x, 220, x + 5, Vector2f(500, 50));
                                sf::Text text(favor_def[i], font, 30);
                                item_def[cnt].set_up(hiden_text(950, text), font, 30, color, 500, x, 520, x + 5, Vector2f(950, 50));
                                full_def[cnt] = favor_def[i];
                                if (i % 2 != 0) swap(color[0], color[1]);
                                else swap(color[1], color[0]);
                                x += 50;
                                cnt++;
                            }
                            else {
                                item[cnt].set_up("", font, 30, color, 200, x, 220, x + 5, Vector2f(500, 50));
                                item_def[cnt].set_up("", font, 30, color, 500, x, 520, x + 5, Vector2f(950, 50));
                                if (i % 2 != 0) swap(color[0], color[1]);
                                else swap(color[1], color[0]);
                                x += 50;
                                cnt++;
                            }
                        }
                    }
                    else nxt.setTexture(b_next2);
                }
                else nxt.setTexture(b_next1);
            }
            for (int i = 0; i < 11; i++) {
                if (item_def[i].isTouched(window, event) && item_def[i].text.getString() != "") {
                    item_def[i].color[0] = color_touch[(i + 1) % 2];
                    display_def = true;
                    rec_dis.setPosition(mousePos.x, mousePos.y - 150);
                    dis_text.setString(full_def[i]);
                    dis_text.setPosition(mousePos.x + 10, mousePos.y - 150 + 10);
                    wrapped_text(rec_dis, dis_text);
                    float newHeight = dis_text.getLocalBounds().height;
                    rec_dis.setSize(sf::Vector2f(700, newHeight));

                    if (dis_text.getPosition().y + newHeight > window.getSize().y) {
                        float delta = dis_text.getPosition().y + newHeight - window.getSize().y;
                        dis_text.setPosition(mousePos.x + 10, mousePos.y - 150 + 10 - delta);
                        rec_dis.setPosition(mousePos.x, mousePos.y - 150 - delta);
                    }
                }
                else item_def[i].color[0] = color[(i)%2];
            }
        }
        window.clear();
        window.draw(spr_scene);
 
        word.drawButton(window, event);
        word.text.setFont(font1);
        window.draw(word.text);

        def.drawButton(window, event);
        def.text.setFont(font1);
        window.draw(def.text);
        for (int i = 0; i < 11; i++) {
            item[i].drawButton(window, event);
            item[i].text.setFont(font);
            window.draw(item[i].text);

            item_def[i].drawButton(window, event);
            item_def[i].text.setFont(font);
            window.draw(item_def[i].text);
            
            window.draw(bins[i]);
        }
        window.draw(prev);

        mid.drawButton(window, event);
        mid.text.setFont(font);
        window.draw(mid.text);

        window.draw(nxt);
        if (display_def) {
            window.draw(rec_dis);
            window.draw(dis_text);
        }
        window.display();
    }
}