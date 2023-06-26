#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime> 
#include <sstream>
using namespace std;
using namespace sf;
const int sizee = 128;
class TrieNode {
public:
    vector<TrieNode*> children;
    bool isEndOfWord;
    string meaning;
    TrieNode() {
        children = vector<TrieNode*>(sizee, nullptr);
        isEndOfWord = false;
        meaning = "";
    }
};
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word, const string& meaning) {
        TrieNode* cur = root;

        for (char c : word) {
            int index = c - 'a';
            if (cur->children[index] == nullptr) {
                cur->children[index] = new TrieNode();
            }
            cur = cur->children[index];
        }

        cur->isEndOfWord = true;
        cur->meaning = meaning;
    }
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}