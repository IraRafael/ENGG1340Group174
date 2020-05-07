#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

int randNumber(int upper, int lower) { // the program that will generate the random number
	int Y = rand() % ((upper - lower) + 1) + lower;
	
	return Y;
	//cout<< Y << endl; // testing to see what numbers come out

}

void fightMonster(int &potions, int &hp, int score, vector<string> monsterlist, vector<vector<string>> movelist, vector<vector<int>> monhealthlist){//, vector for abilities and such) {
	cout << "A monster blocks your path " << endl << endl;
	int call = randNumber(100, 0);
	cout << call << endl << monsterlist[call] << endl;
	int hpUpperLimit = monhealthlist[call][0], hpLowerLimit = monhealthlist[call][1]; 
	cout << hpUpperLimit << endl << hpLowerLimit << endl << randNumber(hpUpperLimit, hpLowerLimit) << endl << randNumber(hpUpperLimit, hpLowerLimit);

}

int main() {
	int monster;


	vector<string> monsterlist = { "Slow Slime", "Swift Slime", "Goblin Hoard", "Shadow Mage", "Leviathan Worshiper", "Haunted Sword", "Blind Priest", "Lucky Larry", "Grime Mage", "Hungry Tom", "Mutant Hog", "Swarming Bees", "Biding Bison", "Rat King", "Tree Ogre", "Feral Wolf", "Other Warrior", "Overgrown Lizard", "River Spirit","Three Headed Snake", "Upper Half of A Giant", "Lava Mage", "Blood Bat", "Shadow Ninja", "Lower Half of A Giant", "Headless Man-horse", "Fire Goose", "The Rock", "Cactus Toad", "Desert Bandit", "Leviathan", "Arctic Fox", "Huge Snowman", "Apex Sandworm", "Spike Raptor", "Spiked Dolphin", "Vampire Turtle", "Infected Bat", "Steel Armadillo", "Frostbitten Dragon", "Hammer Crab", "Mermaid", "Diver Falcon", "Sonic Bear", "Thunder Raven", "Dimension-hopping Scientist", "Fragrant Flytrap", "Lancehorn Rhino", "Devil's General", "Land Pirannahs", "Boot Head", "Mr Dodge", "Vine Witch", "Sneaky Rat", "Enlightend Elephant Mage", "Reaper", "Lion Of War", "Tiger Of Battle", "Puma Of Engage", "Goblin Emperor", "Windmill Keeper", "Cannon Snail", "Karate Rabbitman", "Gatling Rooster", "Old Tree Spirit", "Swamp Anglerfish", "Coat Ghost", "Insane Baker", "Trident Fishman", "Flower Ghoul", "Orchid Salamander", "Sand Hedgehog", "Ore Tortoise", "Trap-mouth Hippo", "Radar Owl", "Mud Titan", "Wrath Wyvern", "Fungus Ant", "Chang Baitu", "Athune the Brave", "Lightning Wolf", "Bog Bridge Troll", "Spirit Drummer", "Zap Mouse", "Lake Serpent", "Tower Saver", "Foul Shroom", "Rose Queen", "Spear Gazelle", "Echo Wasp", "Horned Pig", "Haunted Practice Dummy", "Pile Raiders", "Jaguar of Savagery", "Tunneling Meerkat Crew", "Aether Jellyfish", "Boulder Pufferfish", "Scythe Tucan", "Lime Slime", "Bad Trumpeter", "Honey Grizzly" };


	vector<vector<string>> movelist = { {"Lunge", "Plop"},
{"Lunge", "Plop", "Strike"},
{"Combined Attack", "Combined Attack", "Toss A Mate", "Multihit"},
{"Shadow Orb","Blast","Divinity", "Blast"},
{"Blast", "Blast", "Sea Orb", "Divinity"},
{"Strike", "Shadow Orb"},
{"Divinity", "Blast", "Blast", "Blind Blast"},
{"Luck Strike","Lucky Harm", "Blast"},
{"Blast", "Blast", "Gunk Chuck"},
{"Chomp", "Chow", "Bite"},
{"Lunge","Lunge","Strike"},
{"Multihit", "Strike", "Sting"},{"Charge","Lunge","Strike"},
{"Multihit","Rat Parry","Decisive Lunge", "Lunge","Multihit"},
{"Tree Smash", "Strike", "Strike"},
{"Rabbies", "Dashing Bite", "Bite"},
{"Mocking Strike", "Mocking Slash","Mocking Lunge"}, {"Tail Lash","Chomp", "Back Stab"},
{"Sea Orb", "Tidal Vortex", "Blast", "Sea Orb"},
{"Tri-Bite", "Multihit","Strike", "Multihit"},
{"Hand Slam","Sonorous Roar", "Hand Slam","Heavy Strike"},
{"Fire Orb", "Fire Orb", "Divinity", "Blast"},
{"Strike", "Agility Dive", "Lunge", "Drain"},
{"Duplicate Strike","Shadow Orb","Blast","Blast","Shadow Orb"},
{"Foot Stomp","Heavy Strike","Rapid Stomping","Foot Stomp"},
{"Lunge","Charge","Lunge","Galloping Havoc"},
{"Strike","Flaming Wing Strike", "Lunge"},
{"Strike", "Roar", "Gatling Fists", "Strike"},
{"Blast", "Toung Lash", "Hold Position"},
{"Back Stab", "Lunge", "Blast"},
{"Tsunami", "Whirlpool", "Lightning Storm", "Tidal Vortex", "Blast", "Blast", "Blast","Strike"},
{"Lunge", "Strike","Snowball"},
{"Strike", "Hand Slam", "Snowball", "Avalanche"},
{"Burrowing Strike", "Strike", "Strike", "Sandball"},
{"Lunge", "Strike","Bite", "Bite"},
{"Jet Stream Slam","Bite", "Hold Position"},
{"Bite", "Snap", "Drain", "Bash"},
{"Infect", "Bite","Bite","Strike"},
{"Roll", "Lunge","Bash","Steel Bash"},
{"Ice Age Breath","Ice Orb", "Glacial Fissure", "Blast","Blast"},
{"Hammer Smash", "Strike", "Bash", "Lunge"},
{"Allure", "Blast", "Blast", "Sea Orb"},
{"Lunge","Agility Dive", "Strike", "Lunge"},
{"Raging Roar", "Strike", "Slash","Strike"},
{"Strike", "Agility Dive", "Blast", "Light Speed"},
{"Blast","Invent","Blast","Blast"},
{"Allure", "Chomp","Strike","Strike"},
{"Back Stab", "Charge", "Charge","Lunge", "Strike"},
{"Death Wish", "Axe Slash", "Strike","Strike","Fire Orb", "Fire Pit"},
{"Multihit", "Chomp", "Strike","Toss A Mate"},
{"Strike","Strike","Lunge", "Blast"},
{"Taunt","Pitty Strike"},
{"Strike", "Blast", "Divinity","Strike"},
{"Back Stab", "Strike", "Blast","Blast"},
{"Divinity", "Exorcise","Orb Of The Sun", "Blast", "Strike"},
{"Strike","Foreshadow", "Strike"},
{"Tempest", "Strike","Strike"},
{"Tempest", "Lunge","Lunge"},
{"Tempest", "Blast","Blast"},
{"Strike", "Decisive Lunge", "Multihit", "Toss A Mate", "Strike"},
{"Blast", "Fire Orb", "Sea Orb", "Shadow Orb", "Blast"},
{"Blast", "FIRE!"},
{"Bite", "Chomp", "Fury Strike", "Strike", "Bite"},
{"Blast","Egg Rapid Fire", "Blast"},
{"Blast", "Divinity","Drain","Blast"},
{"Chomp", "Strike", "Chomp", "Light Burst"},
{"Blast", "Lunge","Blast", "Shadow Orb"},
{"Bake Some 'Bread'", "Strike", "Strike", "Lunge"},
{"Strike", "Trident Strike", "Sea Orb"},
{"Allure", "Shadow Orb", "Blast", "Blast"},
{"Allure", "Tail Lash", "Blast", "Bash", "Bite"},
{"Roll","Lunge","Bash","Bash","Roll", "Roll"},
{"Hold Position", "Snap", "Snap"},
{"Chomp","Clobber","Jaw Swing", "Chomp"},
{"Strike", "Agility Dive","Strike","Blast"},
{"Mud Slam", "Blast", "Strike", "Blast"},
{"Malevolent Breath", "Blast", "Strike","Agility Dive", "Call Of Hades"},
{"Blast","Chomp","Chomp"},
{"Moonlit Bite","Strike", "Sea Orb", "Blast","Blast"},
{"Strike","Decisive Lunge", "Fire Orb", "Strike"},
{"Bite", "Volt Strike", "Blast", "Bite"},
{"Strike", "Backstab", "Lunge"},
{"Divinity", "Blast", "Blast","Strike"},
{"Strike", "Volt Strike", "Blast", "Strike"},
{"Sea Orb","Tidal Vortex", "Blast", "Blast"},
{"Divinity", "Blast", "Strike", "Strike", "Lunge"},
{"Blast","Toxic Fume","Blast"},
{"Allure", "Decisive Lunge", "Lunge", "Lunge", "Blast"},
{"Charge", "Charge", "Strike"},
{"Multihit", "Strike", "Sting","Strike","Roaring Buzz"},
{"Strike", "Bash", "Strike"},
{"Blast", "Hold Position", "Shadow Orb", "Blast"},
{"Back Stab", "Strike", "Lunge", "Multihit"},
{"Tempest", "Fire Orb","Sea Orb"},
{"Multihit","Toss A Mate", "Strike"},
{"Blast", "Blast","Sea Orb", "Volt Strike"},
{"Roll", "Expand", "Strike", "Strike", "Strike", "Strike", "Contract"},
{"Strike", "Agility Dive","Lunge","Slash"},
{"Plop", "Multihit", "Lunge"},{"Roar", "Strike", "Blast"},{"Strike", "Bash", "Back Stab", "Silence"}};


	vector<vector<int>> monhealthlist = {{25,15},{30,25},{32,30},{35,30},{37,30},{25,20},{25,25},{30,23},{25,20},{32,28},{30,27},{35,30},{40,37},{50,40},{55,40},{35,30},{35,35},{45,43},{39,37},{35,32},{50,45},{40,37},{25,20},{35,32},{50,45},{37,33},{27,23},{45,43},{27,22},{30,25},{105,60},{32,25},{40,38},{46,30},{33,30},{27,25},{30,25},{22,20},{40,32},{105,60},{35,30},{35,32},{27,25},{32,30},{32,25},{40,32},{30,23},{32,30},{60,45},{30,24},{29,21},{7,7},{29,25},{28,25},{41,39},{45,35},{50,42},{50,42},{50,42},{53,40},{30,27},{23,19},{32,28},{32,24},{32,22},{37,29},{27,23},{34,23},{32,30},{32,27},{37,35},{29,23},{43,40},{43,37},{29,23},{42,40},{80,47},{23,19},{35,27},{39,32},{32,30},{29,23},{29,23},{27,26},{33,29},{31,26},{27,19},{29,26},{27,23},{30,25},{29,23},{30,23},{32,30},{50,42},{30,25},{35,25},{35,30},{32,29},{25,20},{29,27},{35,30}
	};


	string gover = "Game Over\n\nScore: ", startplaceholder;
	srand(time(0)); // this will trigger the ability for random events to occur with the rand() command
	cout << "Welcome Wandering Warrior!" << endl<<endl << "Wizzard Wallace: I, Wizzard Wallace, have heard from the King that you, Warrior, will be embarking on a journey to a distant land!" << endl <<endl << "Wizzard Wallace: May I graciously ask you humble warrior how many monsters you expect to encounter in this journey?" << endl<<endl;
	cout << "How many monsters do you think you'll encounter: ";
	int x = 0, crazy = 0, end = 0, potions = 3, hp=35, score = 0;
	while (x == 0) {
		cin >> monster;
		if (monster >= 100 and crazy != 3) {
			cout << endl;
			cout << "Wizzard Wallace: WHAT!!!" << endl << endl << "Wizzard Wallace: That's simply impossible! The lands don't have that many monsters out there" << endl << endl << "Wizzard Wallace: You can't possibly be serious warrior" << endl << endl;
			cout << "How many monsters do you think you'll encounter: ";
			crazy++;
		}
		else if (crazy == 3 and monster >= 100) {
			cout << endl;
			cout << "Wizzard Wallace: I- I see... Who told you that that many monsters exist!" << endl << endl << "Wizzard Wallace: Gurads, kill this man! He knows too much." << endl << endl;
			cout << gover;
			x++;
		}
		else {
			cout << endl;
			cout << "Wizzard Wallace: WOW! That's great, I'm glad we found a true warrior for this journey!" << endl << endl << "Wizzard Wallace: I am sure you are familiar with your weapon the Blade, it does 7 damage when it hits and has a 20% chance to critically strike." << endl << endl;
			x++;
		}

		

	}



	cout << "Wizzard Wallace: We will be sending you off on your journey now, have 3 potions, you may need it to restore 10 HP. You may just follow the path and you surely will be fine! Best of luck Warrior!" << endl << endl << endl;

	cout << "Type anything and hit enter to start: ";
	cin >> startplaceholder;
	cout << endl << endl << endl;

	cout << "A monster blocks your path " << endl << endl;
	int call = randNumber(100, 0);
	cout << call << endl << monsterlist[call]<<endl;
	int hpUpperLimit = monhealthlist[call][0], hpLowerLimit = monhealthlist[call][1];
	cout << hpUpperLimit << endl << hpLowerLimit << endl << randNumber(hpUpperLimit, hpLowerLimit) << endl << randNumber(hpUpperLimit, hpLowerLimit);
}
