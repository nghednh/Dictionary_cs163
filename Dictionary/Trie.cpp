#include "Trie.h"
#include <iostream>
using namespace std;

extern Trie dictrie[5];
bool Trie::compareRan() {
	if (root == dictrie[0].root || root == dictrie[1].root || root == dictrie[2].root) {
		cout << 1;
		return true;
	}
	
	else {
		cout << 0;
		return false;
	}
}