#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

int randNumber(int upper, int lower) { // the program that will generate the random number
	int Y = rand() % upper + lower;
	return Y;
	//cout<< Y << endl; // testing to see what numbers come out

}

int main() {
	int monster;
	string gover = "Game Over\n\nScore: ";
	srand(time(0)); // this will trigger the ability for random events to occur with the rand() command
	cout << "Welcome Wandering Warrior!" << endl<<endl << "Wizzard Wallace: I, Wizzard Wallace, have heard from the King that you, Warrior, will be embarking on a journey to a distant land!" << endl <<endl << "Wizzard Wallace: May I graciously ask you humble warrior how many monsters you expect to encounter in this journey?" << endl<<endl;
	cout << "How many monsters do you think you'll encounter: ";
	int x = 0, crazy = 0, end = 0, potions = 3, hp=35;
	while (x == 0) {
		cin >> monster;
		if (monster >= 100 and crazy !=3) {
			cout << endl;
			cout << "Wizzard Wallace: WHAT!!!" << endl << endl << "Wizzard Wallace: That's simply impossible! The lands don't have that many monsters out there" << endl << endl << "Wizzard Wallace: You can't possibly be serious warrior" << endl << endl;
			cout << "How many monsters do you think you'll encounter: ";
			crazy++;
		}
		else if (crazy == 3) {
			cout << endl;
			cout << "Wizzard Wallace: I- I see... Who told you that that many monsters exist!" << endl << endl << "Wizzard Wallace: Gurads, kill this man! He knows too much." << endl << endl;
			cout << gover;
			x++;
		}
		else {
			cout << endl;
			cout << "Wizzard Wallace: WOW! That's great, I'm glad we found a true warrior for this journey!" << endl << endl << "Wizzard Wallace: I am sure you are familiar with your weapon the Blade, it does 3 damage when it hits and has a 20% chance to critically strike." << endl << endl;
			x++;
		}
		cout << "Wizzard Wallace: We will be sending you off on your journey now. You may just follow the path and you surely will be fine! Best of luck Warrior!" << endl << endl << endl;


		cout << "A monster blocks your path "
	}
