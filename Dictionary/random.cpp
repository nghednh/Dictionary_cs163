#include <iostream>
#include <cstdlib>
using namespace std;

int randominrange(int range) {
	return (rand() % range)+1; //random in range 1->n
}
int randomz() {
	return rand() % 26; //random a letter
}
int randominrange2(int n, int m) {
	return n + (rand() % (m - n + 1));
}