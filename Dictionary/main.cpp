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
    bool search(const string& word) {
        TrieNode* cur = root;

        for (char c : word) {
            int index = c - 'a';
            if (cur->children[index] == nullptr) {
                return false;
            }
            cur = cur->children[index];
        }

        return cur->isEndOfWord;
    }
    bool partSearch(const string& prefix) {
        TrieNode* cur = root;

        for (char c : prefix) {
            int index = c - 'a';
            if (cur->children[index] == nullptr) {
                return false;
            }
            cur = cur->children[index];
        }

        return true;
    }
    void remove(const string& word) {
        removeOrigin(root, word, 0);
    }

    bool isEmpty(TrieNode* node) {
        for (TrieNode* child : node->children) {
            if (child != nullptr) {
                return false;
            }
        }
        return true;
    }

    bool removeOrigin(TrieNode* node, const string& word, int index) {
        if (index == word.length()) {
            if (!node->isEndOfWord) {
                return false;
            }
            node->isEndOfWord = false;
            node->meaning = "";
            return isEmpty(node);
        }

        int charIndex = word[index] - 'a';
        if (node->children[charIndex] == nullptr) {
            return false;
        }

        bool shouldDelete = removeOrigin(node->children[charIndex], word, index + 1);

        if (shouldDelete) {
            delete node->children[charIndex];
            node->children[charIndex] = nullptr;
            return isEmpty(node);
        }

        return false;
    }
};
void readDatasetToTrie(const string& filename, Trie& trie) {
    ifstream file(filename);
    if (!file) {
        cout << "Failed to open the file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string word, meaning;

        if (iss >> word) {
            getline(iss, meaning);
            trie.insert(word, meaning);
        }
    }

    file.close();
}
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