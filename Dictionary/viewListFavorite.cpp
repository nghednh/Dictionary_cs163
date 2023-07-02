#include "MainScreen.h"\

void viewlistFavor(RenderWindow& window, Trie favor_trie) {
    bool alter = false;
    sf::Color color1(246, 241, 241);
    sf::Color color2(175, 211, 226);

    sf::Font font;
    font.loadFromFile("../Font/arial_narrow_7.ttf");

    sf::RectangleShape title;
    title.setSize(sf::Vector2f(500, 80));
    title.setFillColor(color2);
    title.setPosition(750, 80);

    sf::Text tl_txt("List of favortite words", font, 50);
    tl_txt.setFillColor(sf::Color::Black);
    tl_txt.setPosition(760, 85);

    ifstream fin;
    fin.open("../Dictionary/favorite.txt");
    string s;
    vector<string> list_favor;

    while (!fin.eof()) {
        getline(fin, s, '\n');
        if (s != "") list_favor.push_back(s);
    }
    fin.close();
    while (window.isOpen()) {
        window.clear();
        window.draw(title);
        window.draw(tl_txt);
        float x = 100, y = 200;
        for (int i = 0; i < list_favor.size(); i++) {
            y += 80;
            sf::RectangleShape row;
            row.setSize(sf::Vector2f(1700, 80));
            row.setPosition(x, y);
            row.setFillColor(sf::Color::Blue);

            sf::Text text("", font, 45);
            text.setPosition(x, y);
            text.setFillColor(sf::Color::Black);

            if (alter == false) {
                row.setFillColor(color1);
                alter = true;
            }
            else {
                row.setFillColor(color2);
                alter = false;
            }
            text.setString(list_favor[i]);
            window.draw(row);
            window.draw(text);
        }
        window.display();
    }
}