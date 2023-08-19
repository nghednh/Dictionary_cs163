#include <iostream>
#include "Trie.h"
#include <cstdlib>
using namespace std;
extern Trie dictrie[5];
int randominrange(int range) {
	return (rand() % range)+1; //random in range 1->n
}
int randomz() {
	return rand() % 26; //random a letter
}
int randominrange2(int n, int m) {
	return n + (rand() % (m - n + 1));
}
//bool compareRan(Trie trie) {
//	if (trie == dictrie[0] || trie == dictrie[1] || trie == dictrie[2])
//		return true;
//	else return false;
//}