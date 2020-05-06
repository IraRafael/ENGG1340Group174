#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

int randNumber(int upper, int lower){ // the program that will generate the random number
	int Y = rand() % upper + lower;
	//cout<< Y << endl; // testing to see what numbers come out

}

int main(){
	int monster;
	srand(time(0)); // this will trigger the ability for random events to occur with the rand() command
	cout << "Welcome Wandering Warrior!"<<endl<< "Wizzard Wallace: I, Wizzard Wallace, have heard from the King that you, Warrior, will be embarking on a journey to a distant land!" << endl << "Wizzard Wallace: May I graciously ask you humble warrior how many monsters you expect to encounter in this journey?" << endl;
	cout << "How many monsters do you think you'll encounter: ";
	cin >> monster;









}
