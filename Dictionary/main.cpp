#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>
#include "Trie.h"
using namespace std;
using namespace sf;
void removeWordScreen(RenderWindow& window, Trie& trie) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    sf::RectangleShape inputBox(sf::Vector2f(500, 50));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color(150, 150, 150)); // Light gray outline color

    std::string inputText;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                // Check if the typed character is a printable character (ASCII 32 to 126)
                if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                    inputText += static_cast<char>(event.text.unicode);
                }
                // Handle backspace to erase characters
                else if (event.text.unicode == '\b' && !inputText.empty()) {
                    inputText.pop_back();
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                // Check if the Enter key is pressed (sf::Keyboard::Key::Enter)
                if (event.key.code == sf::Keyboard::Key::Enter) {
                    if (trie.searchWord(inputText)) {
                        trie.removeWord(inputText);
                        cout << "success";
                    }
                    else cout << "That word doesn't exist!";
                    inputText.clear();
                    cout << endl << trie.searchWord("abaction") << endl;
                    cout << trie.searchWord("abactor") << endl;
                    cout << trie.searchWord("car") << endl;
                    cout << trie.searchWord("cat:))") << endl;
                    cout << trie.searchWord("dog") << endl;
                }
                if (event.key.code == sf::Keyboard::Key::Escape) {
                    return;
                }
            }
        }

        // Update text and inputBox position
        text.setString(inputText);
        inputBox.setPosition(window.getSize().x / 2 - inputBox.getSize().x / 2,
            window.getSize().y / 2 - inputBox.getSize().y / 2);

        // Center the text inside the input box
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(inputBox.getPosition().x + inputBox.getSize().x / 2 - textBounds.width / 2,
            inputBox.getPosition().y + inputBox.getSize().y / 2 - textBounds.height / 2);

        window.clear(sf::Color::White);
        window.draw(inputBox);
        window.draw(text);
        window.display();
    }
}
void insertWordScreen(RenderWindow &window, Trie &trie) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text text1;
    text1.setFont(font);
    text1.setCharacterSize(24);
    text1.setFillColor(sf::Color::Black);
    text1.setString("Key: ");

    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(24);
    text2.setFillColor(sf::Color::Black);
    text2.setString("Definition: ");

    //sf::Text text11;
    //text1.setFont(font);
    //text1.setCharacterSize(24);
    //text1.setFillColor(sf::Color::Black);

    //sf::Text text22;
    //text2.setFont(font);
    //text2.setCharacterSize(24);
    //text2.setFillColor(sf::Color::Black);

    sf::RectangleShape inputBox1(sf::Vector2f(500, 50));
    inputBox1.setFillColor(sf::Color::White);
    inputBox1.setOutlineThickness(2);
    inputBox1.setOutlineColor(sf::Color(150, 150, 150)); // Light gray outline color

    sf::RectangleShape inputBox2(sf::Vector2f(500, 50));
    inputBox2.setFillColor(sf::Color::White);
    inputBox2.setOutlineThickness(2);
    inputBox2.setOutlineColor(sf::Color(150, 150, 150)); // Light gray outline color

    sf::Text text11;
    text11.setFont(font);
    text11.setCharacterSize(24);
    text11.setFillColor(sf::Color::Black);
    sf::Text text22;
    text22.setFont(font);
    text22.setCharacterSize(24);
    text22.setFillColor(sf::Color::Black);

    std::string inputText1;
    std::string inputText2;

    bool enteringText1 = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                // Check if the typed character is a printable character (ASCII 32 to 126)
                if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                    if (enteringText1)
                        inputText1 += static_cast<char>(event.text.unicode);
                    else
                        inputText2 += static_cast<char>(event.text.unicode);
                }
                // Handle backspace to erase characters
                else if (event.text.unicode == '\b') {
                    if (enteringText1 && !inputText1.empty())
                        inputText1.pop_back();
                    else if (!enteringText1 && !inputText2.empty())
                        inputText2.pop_back();
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                // Check if the Enter key is pressed (sf::Keyboard::Key::Enter)
                if (event.key.code == sf::Keyboard::Key::Enter) {
                    if (enteringText1) {
                        enteringText1 = false;
                    }
                    else {
                        trie.insertWord(inputText1, inputText2);
                        inputText1.clear();
                        inputText2.clear();
                        enteringText1 = true;
                        cout << endl << trie.searchWord("abaction") << endl;
                        cout << trie.searchWord("abactor") << endl;
                        cout << trie.searchWord("car") << endl;
                        cout << trie.searchWord("cat:))") << endl;
                        cout << trie.searchWord("dog") << endl;
                    }
                }
                if (event.key.code == sf::Keyboard::Key::Escape) {
                    return;
                }
            }
        }
        inputBox1.setPosition(200, window.getSize().y / 2 - 100);
        inputBox2.setPosition(200, window.getSize().y / 2);
        text11.setString(inputText1);
        sf::FloatRect textBounds11 = text11.getLocalBounds();
        text11.setPosition(inputBox1.getPosition().x + inputBox1.getSize().x / 2 - textBounds11.width / 2,
            inputBox1.getPosition().y + inputBox1.getSize().y / 2 - textBounds11.height / 2);
        text22.setString(inputText2);
        sf::FloatRect textBounds22 = text22.getLocalBounds();
        text22.setPosition(inputBox2.getPosition().x + inputBox2.getSize().x / 2 - textBounds22.width / 2,
            inputBox2.getPosition().y + inputBox2.getSize().y / 2 - textBounds22.height / 2);
        
        // Update text1 and inputBox1 position
        text1.setPosition(50, window.getSize().y / 2 - 100);
        
        // Center the text inside inputBox1
        sf::FloatRect text1Bounds = text1.getLocalBounds();
        text1.setPosition(inputBox1.getPosition().x - text1Bounds.width,
            inputBox1.getPosition().y + inputBox1.getSize().y / 2 - text1Bounds.height / 2);

        // Update text2 and inputBox2 position
        text2.setPosition(50, window.getSize().y / 2);

        // Center the text inside inputBox2
        sf::FloatRect text2Bounds = text2.getLocalBounds();
        text2.setPosition(inputBox2.getPosition().x - text2Bounds.width,
            inputBox2.getPosition().y + inputBox2.getSize().y / 2 - text2Bounds.height / 2);
        window.clear(sf::Color::White);
        window.draw(inputBox1);
        window.draw(text1);
        window.draw(inputBox2);
        window.draw(text2);
        window.draw(text11);
        window.draw(text22);
        window.display();
    }
}
int main() {
    Trie trie;
    trie.readDatasetToTrie("words.txt");
    trie.removeWord("3213");
    trie.insertWord("231", "fsdf");
    cout << trie.searchWord("abaction") << endl;
    cout << trie.searchWord("abactor") << endl;
    cout << trie.searchWord("car") << endl;
    cout << trie.searchWord("cat:))") << endl;
    cout << trie.searchWord("dog") << endl;
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Text Input");
    insertWordScreen(window, trie);
    cout << "Menu screen";

    return 0;
}