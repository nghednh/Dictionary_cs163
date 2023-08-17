#pragma once
#include "Trie.h"
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
//        text.setFillColor(sf::Color::Black);
//        //Set up color
//        for (int i = 0; i < 4; i++) {
//            this->color[i] = color[i];
//        }
//    }
//    bool isPressed(RenderWindow& window, Event& e) {
//        Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//        if (shape.getGlobalBounds().contains(mousePos)) {
//            if (e.type == Event::MouseButtonPressed) {
//                return true;
//            }
//            else return false;
//        }
//        return false;
//    }
//    bool isReleased(RenderWindow& window, Event& e) {
//        Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//        if (shape.getGlobalBounds().contains(mousePos)) {
//            if (e.type == Event::MouseButtonReleased) {
//                return true;
//            }
//        }
//        return false;
//    }
//    bool isTouched(RenderWindow& window, Event& e) {
//        Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//        if (shape.getGlobalBounds().contains(mousePos)) {
//            return true;
//        }
//        return false;
//    }
//    void drawButton(RenderWindow& window, Event& e) {
//        if (isPressed(window, e)) shape.setFillColor(color[3]);
//        else if (isTouched(window, e)) shape.setFillColor(color[0]);
//        else shape.setFillColor(color[0]);
//        window.draw(shape);
//    }
//};
//-----------------Function--------------------------
void wrapped_text(RectangleShape shape, Text& text);

//-----------------Draw Scene--------------------------
void search_addfavorite(RenderWindow& window, Trie* trie, string typeDictionary, Trie& favor_trie, Trie& history_trie);
void searchByDef(RenderWindow& window, Trie* trie, string typeDictionary, Trie& favor_trie, Trie& history_trie);
void display(TrieNode* root, string str, ofstream& fout);
void findDef(TrieNode* root, string input, vector<pair<string, string>>& ans);
