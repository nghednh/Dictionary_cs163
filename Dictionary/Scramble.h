#pragma once
#include "Trie.h"
struct button1 {
    RectangleShape shape;
    Sprite but;
    Color* color = new Color[4];
    Text text;
    void set_up(string content, Font font, int sizefont, Color* color, float posX, float posY, float posX_t, float posY_t, Vector2f size, Sprite t) {
        //Set up rec
        shape.setPosition(posX, posY);
        shape.setSize(size);
        shape.setFillColor(color[0]);
        //Set up text
        text.setString(content);
        text.setCharacterSize(sizefont);
        text.setPosition(posX_t, posY_t);
        text.setFillColor(sf::Color::White);
        //Set up color
        for (int i = 0; i < 4; i++) {
            this->color[i] = color[i];
        }
        but = t;
        but.setPosition(posX, posY);
    }
    void wrapped_text(string& s) {
        float hei, wid;
        wid = shape.getGlobalBounds().width;
        hei = shape.getGlobalBounds().height;
        string originalText = text.getString();
        string word;
        istringstream iss(originalText);
        while (iss >> word) {
            sf::Text tempText = text;
            string testString = s + word;
            tempText.setString(testString);
            if (tempText.getGlobalBounds().width > wid - 40)  s += '\n';
            hei = max(hei, tempText.getGlobalBounds().height);
            s += word + ' ';
        }
        shape.setSize(sf::Vector2f(wid, hei));
        text.setString(s);
    }
    bool isPressed(RenderWindow& window, Event& e) {
        Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (shape.getGlobalBounds().contains(mousePos)) {
            //if (window.pollEvent(e)) {
            if (e.type == Event::MouseButtonPressed) {
                return true;
            }
            //}
        }
        return false;
    }
    bool isReleased(RenderWindow& window, Event& e) {
        Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (shape.getGlobalBounds().contains(mousePos)) {
            //if (window.pollEvent(e)) {
            if (e.type == Event::MouseButtonReleased) {
                return true;
            }
            //}
        }
        return false;
    }
    bool isTouched(RenderWindow& window, Event& e) {
        Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (shape.getGlobalBounds().contains(mousePos)) {
            return !(window.pollEvent(e));
        }
        return false;
    }
};
void gameScrumble(RenderWindow& window, string input, string meaning);