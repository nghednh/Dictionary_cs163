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

int main()
{
    //debug
    Trie trie;
    readDatasetToTrie("words.txt", trie);
    cout << trie.searchWord("abaction") << endl;
    cout << trie.searchWord("abactor") << endl;
    cout << trie.searchWord("car") << endl;
    cout << trie.searchWord("cat:))") << endl;
    cout << trie.searchWord("dog") << endl;

    cout << trie.partSearch("ab") << endl;
    cout << trie.partSearch("ba") << endl;
    cout << trie.partSearch("ca") << endl;
    //return 0;
    //gui
    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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

    return 0;*/
}