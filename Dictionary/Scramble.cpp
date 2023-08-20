#include "game.h"
#include "viewListFavor.h"
#include "Scramble.h"

void gameScrumble(RenderWindow& window, string input, string meaning, string typeDictionary, Trie* trie, Trie& favor_trie, Trie& history_trie) {

    sf::Texture scene;
    scene.loadFromFile("../Dictionary/content/background/game_scene.png");
    sf::Sprite spr_scene;
    spr_scene.setTexture(scene);

    sf::Texture but0;
    but0.loadFromFile("../Dictionary/content/Scrumble/button1.png");
    sf::Texture but1;
    but1.loadFromFile("../Dictionary/content/Scrumble/button2.png");
    sf::Texture but2;
    but2.loadFromFile("../Dictionary/content/Scrumble/button3.png");
    sf::Texture but3;
    but3.loadFromFile("../Dictionary/content/Scrumble/button4.png");

    sf::Texture cor;
    cor.loadFromFile("../Dictionary/content/Scrumble/Correct.png");
    sf::Texture incor;
    incor.loadFromFile("../Dictionary/content/Scrumble/Incorrect.png");
    sf::Texture non;
    non.loadFromFile("../Dictionary/content/Scrumble/None.png");

    sf::Texture nxt;
    nxt.loadFromFile("../Dictionary/content/Scrumble/Next.png");
    sf::Texture skp;
    skp.loadFromFile("../Dictionary/content/Scrumble/Skip.png");

    sf::Texture hint;
    hint.loadFromFile("../Dictionary/content/Scrumble/Hint.png");

    Sprite hnt;
    hnt.setPosition(1300, 700);

    Sprite link;
    link.setPosition(1300, 900);

    Sprite but[4];
    but[0].setTexture(but0);
    but[1].setTexture(but1);
    but[2].setTexture(but2);
    but[3].setTexture(but3);

    Sprite state;
    state.setTexture(non);
    state.setPosition(1300, 800);

    sf::Font font;
    font.loadFromFile("content/Oswald-Light.ttf");

    Color* color = new Color[4];
    color[0] = Color(79, 112, 156);
    color[1] = Color(165, 215, 232);
    color[2] = Color(45, 67, 86);
    color[3] = Color(187, 100, 100);

    sf::Text ansTxt;
    ansTxt.setFont(font);
    ansTxt.setFillColor(sf::Color::Black);
    ansTxt.setPosition(250, 500);
    sf::Text ansWord;
    ansWord.setFont(font);
    ansWord.setFillColor(sf::Color::Black);
    ansWord.setPosition(250, 450);
    ansWord.setCharacterSize(40);

    sf::RectangleShape ansRec;
    ansRec.setPosition(250, 450);
    ansRec.setSize(sf::Vector2f(1240, 500));
    ansRec.setFillColor(Color::Transparent);

    sf::Text ht;
    ht.setFont(font);
    ht.setFillColor(Color::Black);
    ht.setPosition(250, 450);

    int siz = input.size();
    int state_ans = 0;
    bool gaming = true;
    vector<pair<bool, button1>> list;
    vector<pair<int, button1>> listAns;

    string ans = "";
    string preans = "";
    int* arrAns = new int[siz];
    vector<int> arrRan;
    for (int i = 0; i < siz; i++) {
        arrAns[i] = -1;
        arrRan.push_back(i);
    }
    unsigned seed = 0;

    random_shuffle(arrRan.begin(), arrRan.end());

    float x = (1740 - 80*siz) / 2;
    for (int i = 0; i < arrRan.size(); i++) {
        pair<bool, button1> cur;
        pair<int, button1> curAns;
        string tmp = "";
        tmp.push_back(input[arrRan[i]]);
        cur.first = false;
        curAns.first = arrRan[i];
        cur.second.set_up(tmp, font, 30, color, x, 600, x + 25, 610, Vector2f(50, 50), but[0]);
        curAns.second.set_up("", font, 30, color, x, 350, x + 25, 360, Vector2f(50, 50), but[0]);
        list.push_back(cur);
        listAns.push_back(curAns);
        x += 80;
    }
    int cnt = 0;
    Cursor mou;
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            for (int i = 0; i < list.size(); i++) {
                if (list[i].second.but.getGlobalBounds().contains(mousePos)) {
                    list[i].second.but.setTexture(but1);
                    if (event.type == sf::Event::MouseButtonPressed) {
                        gaming = true;
                        if (listAns[siz - 1].second.text.getString() != "") {
                            list[i].second.but.setTexture(but3);
                        }
                        else if (list[i].first != true) {
                            string tmp = list[i].second.text.getString();
                            ans += tmp;
                            list[i].second.but.setTexture(but2);
                            list[i].first = true;
                            listAns[cnt].first = i;
                            arrAns[cnt] = i;
                            listAns[cnt].second.text.setString(tmp);
                            cnt++;
                        }
                    }
                }
                else list[i].second.but.setTexture(but0);
                if (listAns[i].second.but.getGlobalBounds().contains(mousePos)) {
                    listAns[i].second.but.setTexture(but1);
                    string tmp = listAns[i].second.text.getString();
                    if (tmp != "" && event.type == sf::Event::MouseButtonPressed) {
                        gaming = true;
                        listAns[i].second.but.setTexture(but2);
                        cout << tmp << '\n';
                        cout << listAns[i].first << '\n';
                        list[listAns[i].first].first = false;
                        arrAns[i] = -1;
                        listAns[i].second.text.setString("");
                        cnt--;
                    }
                    else if (tmp == "" && event.type == sf::Event::MouseButtonPressed) {
                        listAns[i].second.but.setTexture(but3);
                    }
                }
                else listAns[i].second.but.setTexture(but0);
            }
            string cur;
            for (int i = 0; i < siz; i++) {
                if (arrAns[i] >= 0) {
                    cur.push_back(input[arrRan[arrAns[i]]]);
                }
            }
            if (cur == input) {//Correct
                state.setTexture(cor);
                link.setTexture(nxt);
                ansWord.setString(input);
                ansTxt.setString(meaning);
                wrapped_text(ansRec, ansTxt);
                
                hnt.setTexture(non);
                if (link.getGlobalBounds().contains(mousePos)) {
                    if (mou.loadFromSystem(Cursor::Hand)) {
                        window.setMouseCursor(mou);
                    }
                    if (event.type == Event::MouseButtonPressed) {
                        //Chuyen tab
                    }
                }
                else if (mou.loadFromSystem(Cursor::Arrow)) {
                    window.setMouseCursor(mou);
                }
            }
            else if (cur != input && cnt == siz) { //Incorrect
                state.setTexture(incor);
                link.setTexture(skp);
                ansTxt.setString("");
                ansWord.setString("");
                hnt.setTexture(hint);
                if (hnt.getGlobalBounds().contains(mousePos)) {
                    if (mou.loadFromSystem(Cursor::Hand)) {
                        window.setMouseCursor(mou);
                    }
                    if (event.type == Event::MouseButtonPressed) {
                        ht.setString(input);
                    }
                    else ht.setString("");
                }
                else if (link.getGlobalBounds().contains(mousePos)) {
                    if (mou.loadFromSystem(Cursor::Hand)) {
                        window.setMouseCursor(mou);
                    }
                    if (event.type == Event::MouseButtonPressed) {
                        //Chuyen tab
                    }
                }
                else if (mou.loadFromSystem(Cursor::Arrow)) {
                    window.setMouseCursor(mou);
                }
            }
            else { // Playing
                state.setTexture(non);
                link.setTexture(non);
                ansTxt.setString("");
                ansWord.setString("");
                hnt.setTexture(non);
            }
        }
        window.clear();
        window.draw(spr_scene);
        for (int i = 0; i < list.size(); i++) {
            if (list[i].first != true) {
                window.draw(list[i].second.but);
                list[i].second.text.setFont(font);
                window.draw(list[i].second.text);
            }
            window.draw(listAns[i].second.but);
            listAns[i].second.text.setFont(font);
            window.draw(listAns[i].second.text);
        }
        window.draw(state);
        window.draw(link);
        window.draw(ansTxt);
        window.draw(ansWord);
        window.draw(ht);
        window.draw(hnt);
        window.display();
    }
}