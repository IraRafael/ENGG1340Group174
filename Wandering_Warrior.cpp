#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int randNumber(int upper, int lower) {
	//upper is the upper limit number and lower is the lower limit number
	//this function is made to generate a number between upper adn lower
	int Y = rand() % ((upper - lower) + 1) + lower;
	
	return Y;
	//cout<< Y << endl; // testing to see what numbers come out

}

void critCalculator(int CritVal, int &Damage, int CritChance, int &CritIndicator){
	//CritVal is the "wall" which determines whether an attack critically strikes
	//Damage is the initial damage that the attack would do if it weren't to critically strike, if it were to it would be put into the bellow equztion so as to be amplified
	//CritChance is the randomly generated value that will get tested against CritChance to see if the attack will critically strike
	//CritIndicator is the test case to be tested later inorder to display certain dialogue if the attack critically struck
	//if CritVal(pre-determined) is smaller tham CritChance (randomly generated), the attacck will thereby critically strike
	

	if (CritChance > CritVal) {
		if (Damage % 2 == 0) { Damage = Damage * 1.5; }
		else {
			Damage = (Damage + 1) * 1.5;
		}
		CritIndicator = 1;
	}
}

int usePotion(int& hp, int& potionIndicator, int maxHP, int healVal) {
	//hp is the current health of the user
	//potionIndicator is an integer for a test case to see if the player or monster used a healing item or attack inorder to output the appropriate dialogue
	//maxHP is the maximum possible health of the user
	//healVal is the ammount that was healed by the user to be outputted by the system

	if ((hp+healVal) > maxHP) {
		hp = maxHP;
		potionIndicator++;
		return (maxHP - hp);
	}
	else { hp += healVal; potionIndicator++; return healVal; }
	
}

void fightMonster(int &maxMultiplier,int &hpAura, int &attackAura, vector<string>&resultVector, int &monster, int j, int& end, int& multiplier, int& potions, int& hp, int& score, vector<string> monsterList, vector<vector<string>> moveList, vector<vector<int>> monHealthList, vector<vector<int>> moveValues) {
	//maxMultiplier is a global variable that will be updated later in the code and will be used for the player's final score at the end of game summary
	//hpAura and attackAura are bonuses given after defeating a difficult monster
	//resultVector is a vector that stores the monsters you have faught for the end of game summary
	//monster is the number of monsters the player will fight that he/she inputted at the start
	//j is the jth monster that the player is fighting, its purpose is simply for displaying the player's progress
	//end is a test case integer to see if the player has died or not warranting a "game over"
	//multiplier is the ongiong multiplier applied onto the player's score
	//potions is the current number of potions the player has at the moment
	//hp is the current health of the player
	//score is the current score of the player
	//monsterList is the vector with all the names of the monsters (100 different monsters)
	//moveList is the vector containing vectors of the moves a monster can use
	//monHealth is the vector of all the health ranges of each monster in the format {upperLimit, lower,Limit}
	//moveValues is the vector containing vectors of the damage each move can deal



	int call = randNumber(100, 0); //which monster the player will encounter
	int playerAction = 0;
	
	cout << "A " << monsterList[call] << " blocks your path " << endl << endl;
	
	//monster stats
	int hpUpperLimit = monHealthList[call][0], hpLowerLimit = monHealthList[call][1]; 
	int maxHpMonster = randNumber(hpUpperLimit, hpLowerLimit); //randomly generates the health of the monster within a given range
	int monMoveVectorMax = moveList[call].size(), monMoveVectorMin=0;
	int currentHpMonster = maxHpMonster;
	

	string playerAttackName = ""; //placeholder for what the name player's chose attack

	
	int futureValue = 0, expandConstant = 0, contractConstant = 0, legendMonsterBonus = 0, highMonsterBonus = 0, strikeDmg = 5, lungeDmg = 7, parryDmg = 5, tempestIndicator = 0;

	//list of "legend" monsters for the bonus after defeating them
	if (call == 25 or call == 30 or call == 39 or call == 48 or call == 54 or call == 55 or call == 76 or call == 78) {
		legendMonsterBonus = 10; }
	//list of "high" monsters for the bonus
	if (call == 20 or call == 13 or call == 14 or call == 17 or call == 18 or call == 24 or call == 56 or call == 57 or call == 58 or call == 59 or call == 87 or call == 93 or call == 70){ 
		highMonsterBonus = 5; }

	
	//All the below code represents one round 
	while (hp > 0 and currentHpMonster > 0) {
		int playerMaxHealth = 50 + (hpAura * 5);
		int playerDodgeVal = 90, monDodgeVal = 90, playerCritVal = 70, monCritVal = 80;//base stats of the player and the monster
		//special characteristics for certain monsters
		if (call == 51) { monDodgeVal = 10; }
		if (call == 7) { monCritVal = 40; }

		string UI = "Player HP: " + to_string(hp) + "/" + to_string(playerMaxHealth) +"     "+"		"+ monsterList[call] + " HP: " + to_string(currentHpMonster) + "/" + to_string(maxHpMonster) + "\n"
			+ "Potions: " + to_string(potions) + "\n"
			+ "Action:	(1) Strike " + to_string(strikeDmg + attackAura) + " power	- Higher chance to critically strike\n	(2) Lunge " + to_string(lungeDmg + attackAura) + " power		- Decreases your chance to dodge the enemy's attack\n	(3) Parry " + to_string(parryDmg + attackAura) + " power		- Increases your chance to dodge the enemy's attack\n	(4) Potion		- Heals 10 HP\n	(5) Block			- Decreases the damage of enemy's incoming attack"; // using 4 tabs of separation

		
		//Evalluating which attack the monster will use
		int monAttackValue = randNumber((monMoveVectorMax-1), monMoveVectorMin);
		//Evaluating the critical strike chance and dodge chance for both player and monster, whether a player or monster crits or dodges
		int critChanceMon = randNumber(100, 0), dodgeChanceMon = randNumber(100, 0), critChancePlayer = randNumber(100, 0), 
			dodgeChancePlayer = randNumber(100, 0), playerBonus= (randNumber(2,0))-1, monBonus= (randNumber(2, 0)) - 1, noMulti = randNumber(3, 2);;

		int playerDamage = 0, monDamage = 0, playerCritIndicator = 0, monCritIndicator = 0, monHealVal = 0,
			playerDodgeIndicator = 0, monDodgeIndicator = 0, playerBlockIndicator = 0, playerPotionIndicator = 0, monMultiIndicator = 0, monPotionIndicator = 0,
			deathWishIndicator = 0, divinityIndicator = 0, contractIndicator=0, expandIndicator = 0;

		//player damage calculation, after this we assume the player's damage value is ready to be inputted
		int y = 0;
		while (y == 0) {
			cout << UI << endl << endl << "Select the number of your action: ";
			cin >> playerAction;
			if (playerAction == 1) {		//Strike
				playerCritVal -= 30;
				playerDamage = 5 + playerBonus;
				//if a player lands a critical strike
				critCalculator(playerCritVal, playerDamage, critChancePlayer, playerCritIndicator);
				y++;
				playerAttackName = "Strike";
			}
			else if (playerAction == 2) {	//Lunge
				playerDodgeVal += 5; 
				playerDamage = 7 + playerBonus;
				critCalculator(playerCritVal, playerDamage, critChancePlayer, playerCritIndicator);
				y++;
				playerAttackName = "Lunge";
			}
			else if (playerAction == 3) {	//Parry
				playerDodgeVal -= 5;
				playerDamage = 5 + playerBonus;
				critCalculator(playerCritVal, playerDamage, critChancePlayer, playerCritIndicator);
				y++;
				playerAttackName = "Parry";
			}
			else if (playerAction == 4) {
				if (potions > 0)
				{
					usePotion(hp, playerPotionIndicator, 50, 10);
					y++;
					potions--;
				}
				else { cout << "No potions left."<<endl<<endl; }
			}
			else if (playerAction == 5) { playerBlockIndicator += 1; y++; }
			cout << endl;

		}

		
		
		//monster damage calculation
		string monAttackName = moveList[call][monAttackValue];
		monDamage = moveValues[call][monAttackValue] + monBonus;

		//if the monster used a futureAttack the last round which empoers the current round's attack
		if (futureValue != 0) { monDamage += 5; futureValue = 0;}

		//Tempest is an effecct inflicted by a monster which makes players unable to dodge 
		if (tempestIndicator == 1) { playerDodgeVal = 0; tempestIndicator = 0; }
		
		//checking the type of attack the monster uses: strikeAttacks, multiAttacks, lungeAttacks, divinity, agileAttacks, snowAttacks, drain, futureAttacks, invent, 
		//deathWish, orbOfTheSun, tempestAttacks, expand, contract, and holdPosition 
		//this is because these attack categories have different effects

		//strikeAttacks: +25% critical strike chance
		if (monAttackName == "Strike" or monAttackName == "Fire Orb" or monAttackName == "Axe Slash" or monAttackName == "Malevolant Breath" or monAttackName == "Bake Some 'Bread'" or monAttackName == "Trident Strike") {
			monCritVal -= 25;
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
		}

		//multiAttacks: chance to hit 2 to 3 times in succession in one round and if one attack crits they all critically strike
		else if (monAttackName == "Duplicate Strike" or monAttackName == "Multihit" or monAttackName == "Whirlpool") {
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
			monDamage = noMulti * monDamage;
			monMultiIndicator=1;
		}

		//lungeAttacks: -10% dodge chance for its user
		else if (monAttackName == "Lunge" or monAttackName == "Decisive Lunge") {
			monDodgeVal += 10;
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
		}

		//blastAttacks: -5% dodge chance for players
		else if (monAttackName == "Blast" or monAttackName == "Sea Orb") { 
			playerDodgeVal += 5;
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
		}

		//divinity: +10 HP for its user
		else if (monAttackName == "Divinity") { 
			monPotionIndicator = 0; 
			monHealVal=usePotion(currentHpMonster, monPotionIndicator, maxHpMonster, 10);
			divinityIndicator = 1;
		}

		//agileAttacks: -15% dodge chance for the player
		else if (monAttackName == "Allure" or monAttackName == "Agility Dive") { 
			playerDodgeVal += 15; 
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
		}

		//snowAttacks: +5% dodge chance for its users
		else if (monAttackName == "Snowball" or monAttackName == "Sandball" or monAttackName == "Avalanche" or monAttackName == "Moonlit Bite") {
			monDodgeVal -= 5;
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
		}

		//drain: heals 2 damage when attack lands
		else if (monAttackName == "Drain") {
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
			monHealVal=usePotion(currentHpMonster, monPotionIndicator, maxHpMonster, 2);
		}

		//futureAttacks: empower the next round's attack by 5 damage
		else if (monAttackName == "Ice Age Breath" or monAttackName == "Lightning Storm" or monAttackName == "Toxic Fume" or monAttackName == "Galloping Havoc" or monAttackName == "Foreshadow" or monAttackName == "Call Of Hades") {
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
			futureValue = 1;
		}

		//deathWish: the signature atack of Devil's General dealing 10 damage to both the player and herself
		else if (monAttackName == "Death Wish") { deathWishIndicator == 1; }

		//invent: the signature attack of the Dimension-Hopping Scientist heals 5 HP and gives 10% dodge chance for the user
		else if (monAttackName == "Invent") {
			monHealVal = usePotion(currentHpMonster, monPotionIndicator, maxHpMonster, 5);
			monDodgeVal -= 10;
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
			
		}

		//orbOfTheSun: the signature attack of the Enlightend Elephant Mage which heals him for 5 HP upon dealing damage
		else if (monAttackName == "Orb Of The Sun") {
			monHealVal = usePotion(currentHpMonster, monPotionIndicator, maxHpMonster, 5);
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
		}

		//tempestAttacks: Prevent players from dodging an attack
		else if (monAttackName == "Tempest") {
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
			tempestIndicator = 1;
		}

		//expand: a passive attack increasing the users size which increases its health by 20 being able to go over its health maximum value
		else if (monAttackName == "Expand") {
			if (expandConstant == 0) {
				expandConstant++;
			}
			expandIndicator== 1;
		}

		//contract: a passive attack decreasing the users size which decreases its health by 20 not going under 1 HP
		else if (monAttackName == "Contract") {
			currentHpMonster -= 20;
			if (currentHpMonster <= 0) {
				currentHpMonster = 1;
			}
			contractIndicator = 1;
		}

		//holdPosition: user holds its position reducing incoming damage to 2 damage and dealing damage to the player, this attack cannot critically strike
		else if (monAttackName == "Hold Position") {
			playerDamage = 2;

		}
		
		//for all other attacks
		else {
			critCalculator(monCritVal, monDamage, critChanceMon, monCritIndicator);
		}


		if (playerPotionIndicator == 0) {
			if (dodgeChanceMon > monDodgeVal) {
				if (deathWishIndicator > 0) {
					currentHpMonster -= 10;
					cout << "The enemy " << monsterList[call] << " dealt 10 damage to herself with " << monAttackName << "." << endl << endl;
				}
				cout << "The enemy " << monsterList[call] << " dodged your " << playerAttackName << " and took no damage." << endl << endl;

			}
			else if (playerBlockIndicator==0){
				if(deathWishIndicator > 0) {
					currentHpMonster -= 10;
					cout << "The enemy " << monsterList[call] << " dealt 10 damage to herself with " << monAttackName << "." << endl << endl;
				}
				if (playerCritIndicator == 0) {
					cout << "You attacked the enemy " << monsterList[call] << " with " << playerAttackName << " dealing " << playerDamage << "." << endl << endl;
					currentHpMonster -= playerDamage;
				}
				else {
					cout << "You critically struck the enemy " << monsterList[call] << " with " << playerAttackName << " dealing " << playerDamage << "!" << endl << endl;
					currentHpMonster -= playerDamage;
				}
			}
		}
		//if the player used a potion is below
		else {
			cout << "You healed yourself for 10 HP consuming 1 potion."<<endl<<endl;
		}
		
		
		if(currentHpMonster>0){
			//if the player successfully dodges the attack
			if (dodgeChancePlayer > playerDodgeVal) {
				//deathWish's effect	
				if (deathWishIndicator > 0) {
						hp -= 10;
						cout << "The enemy " << monsterList[call] << " dealt 10 damage to the player with " << monAttackName << "." << endl << endl;
						if (playerBlockIndicator > 1) { cout << "You could not block this attack." << endl << endl; }

					}
					else { cout << "You dodged the enemy "<< monsterList[call] << "'s " << monAttackName << " and took no damage."<<endl<<endl; }
			}

			else {
				
				//if the player used Block
				if (playerBlockIndicator > 0 and divinityIndicator ==0) {
					if (monDamage <= 10) { monDamage = 0; }
					else { monDamage -= 10; }
					cout << "You blocked the enemy " << monsterList[call] << "'s " << monAttackName << " taking " << monDamage << " HP damage." << endl << endl;
					
				}

				//if it was any attack
				else if (monMultiIndicator == 0 and divinityIndicator == 0 and contractIndicator == 0 and expandIndicator == 0){
					if (monCritIndicator == 0) {
						cout << "The enemy " << monsterList[call] << "'s " << monAttackName << " dealt " << monDamage << " HP." << endl << endl;
						hp -= monDamage;

					}
					else {
						cout << "The enemy " << monsterList[call] << "'s " << monAttackName << " critically struck and dealt " << monDamage << " HP!" << endl << endl;
						hp -= monDamage;
					}
				}

				//if the monster used a multiAttack
				else if (monMultiIndicator > 0) {
					if (monCritIndicator == 0) {
						cout << "The enemy " << monsterList[call] << "'s " << monAttackName << " hit " << noMulti << " times and dealt a total of " << monDamage << "." << endl << endl;
						hp -= monDamage;
					}
					else {
						cout << "The enemy " << monsterList[call] << "'s " << monAttackName << " hit " << noMulti << " times, critically struck and dealt a total of " << monDamage << "!" << endl << endl;
						hp -= monDamage;
					}
				}

				//if the monster used divinity
				else if (divinityIndicator > 0) {
					cout << "The enemy " << monsterList[call] << "'s " << monAttackName << " healed itself for " << monHealVal << " HP." << endl << endl;
				}

				//if the monster used Contract or Expand
				else if (contractIndicator > 0 or expandIndicator > 0) {
					if (expandIndicator > 0 and expandConstant == 1) {
						cout << monsterList[call] << " used Expand and expanded its body increasing its health." << endl << endl;
						currentHpMonster += 20;
					}
					else if (expandIndicator > 0 and expandConstant > 1) {
						cout << monsterList[call] << " couldn't expand further." << endl << endl;
					}
					else if (contractIndicator > 0) {
						cout << monsterList[call] << " used Contract and contracted its body and decreasing its health." << endl << endl;
					}
				}

				//if the monster healed not using divinity
				if (monPotionIndicator > 0 and divinityIndicator == 0) {
					cout << "The enemy " << monsterList[call] << "'s " << monAttackName << " healed itself for " << monHealVal << " HP." << endl << endl;
				}

				//if the monster used a futureAttack
				if (futureValue > 0) {
					cout << monAttackName << " empowers " << monsterList[call] << "'s next attack." << endl << endl;
				}

				//if a monster used a tempestAttack
				if (tempestIndicator > 0) {
					cout << "A Tempest is roaring behing the enemy's back, You can't dodge his next attack.";
				}

			}
		
		}
		//what shows up after you have defeated a monster
		if (currentHpMonster <= 0) {
			score += 10 + legendMonsterBonus + highMonsterBonus + multiplier * (10 + legendMonsterBonus + highMonsterBonus);
			multiplier++;
			resultVector.push_back(monsterList[call]);
			if (legendMonsterBonus > 0) {
				cout << "You have slain the " << monsterList[call] << " and abtained the Legend Monster Score Bonus!" << endl << endl;
				legendMonsterBonus = 0;
				cout << "You obtained Legend's Aura. All attacks are empowered and health increased until the game ends." << endl << endl;
				hpAura++;
				attackAura++;
			}
			else if (highMonsterBonus > 0) {
				cout << "You have slain the " << monsterList[call] << " and abtained the Legend Monster Score Bonus!" << endl << endl;
				highMonsterBonus = 0;
				cout << "You obtained High's Aura. Health increased until the game ends." << endl << endl;
				hpAura++;
			}
			else {
				cout << "You have slain the " << monsterList[call] << "!" << endl << endl;
			}
			if (randNumber(10, 1) > 5) {
				cout << "You obtained 1 potion." << endl << endl;
				potions += 1;
			}
			if (j + 1 == monster) {
				end++;
			}
			if (end == 0){
				cout << "Score: " << score << "		Multiplier: " << multiplier << "		Monsters: " << j + 1 << "/" << monster << endl << endl << "Would you like to stop at an inn and rest? (This will reset your score multiplier)" << endl << endl << "(1) - Rest at the Inn		(2) - Continue onwards" << endl << endl << "Please type the number of your choice: ";
			}
			
		}
		//or if you were killed by one
		else if (hp <= 0)
		{
			cout << "You have been slain by the " << monsterList[call] << "." << endl << endl;
			end++;
		}
		if (multiplier > maxMultiplier) { maxMultiplier = multiplier; }
		
	}

	



	

}



int main() {
	int monster;

	//list of monster/enemy names
	vector<string> monsterList = { "Slow Slime", "Swift Slime", "Goblin Hoard", 
		"Shadow Mage", "Leviathan Worshiper", "Haunted Sword", "Blind Priest", "Lucky Larry", "Grime Mage", "Hungry Tom", "Mutant Hog", "Swarming Bees", "Biding Bison", "Rat King", "Tree Ogre", "Feral Wolf", "Other Warrior", "Overgrown Lizard", "River Spirit","Three Headed Snake", "Upper Half of A Giant", "Lava Mage", "Blood Bat", "Shadow Ninja", "Lower Half of A Giant", "Headless Man-horse", "Fire Goose", "The Rock", "Cactus Toad", "Desert Bandit", "Leviathan", "Arctic Fox", "Huge Snowman", "Apex Sandworm", "Spike Raptor", "Spiked Dolphin", "Vampire Turtle", "Infected Bat", "Steel Armadillo", "Frostbitten Dragon", "Hammer Crab", "Mermaid", "Diver Falcon", "Sonic Bear", "Thunder Raven", "Dimension-hopping Scientist", "Fragrant Flytrap", "Lancehorn Rhino", "Devil's General", "Land Pirannahs", "Boot Head", "Mr Dodge", "Vine Witch", "Sneaky Rat", "Enlightend Elephant Mage", "Reaper", "Lion Of War", "Tiger Of Battle", "Puma Of Engage", "Goblin Emperor", "Windmill Keeper", "Cannon Snail", "Karate Rabbitman", "Gatling Rooster", "Old Tree Spirit", "Swamp Anglerfish", "Coat Ghost", "Insane Baker", "Trident Fishman", "Flower Ghoul", "Orchid Salamander", "Sand Hedgehog", "Ore Tortoise", "Trap-mouth Hippo", "Radar Owl", "Mud Titan", "Wrath Wyvern", "Fungus Ant", "Chang Baitu", "Athune the Brave", "Lightning Wolf", "Bog Bridge Troll", "Spirit Drummer", "Zap Mouse", "Lake Serpent", "Tower Saver", "Foul Shroom", "Rose Queen", "Spear Gazelle", "Echo Wasp", "Horned Pig", "Haunted Practice Dummy", "Pile Raiders", "Jaguar of Savagery", "Tunneling Meerkat Crew", "Aether Jellyfish", "Boulder Pufferfish", "Scythe Tucan", "Lime Slime", "Bad Trumpeter", "Honey Grizzly" };

	//list of monster/enemy moves/attacks
	vector<vector<string>> moveList = { {"Lunge", "Plop"},
	{"Lunge", "Plop", "Strike"},
	{"Combined Attack", "Combined Attack", "Toss A Mate", "Multihit"},
	{"Shadow Orb","Blast","Divinity", "Blast"},
	{"Blast", "Blast", "Sea Orb", "Divinity"},
	{"Strike", "Shadow Orb","Strike","Blast"},
	{"Divinity", "Blast", "Blast", "Blind Blast"},
	{"Luck Strike","Lucky Harm","Lucky Harm", "Lucky Harm", "Blast"},
	{"Blast", "Blast", "Gunk Chuck"},
	{"Chomp", "Bite", "Bite"},
	{"Lunge","Lunge","Strike"},
	{"Multihit", "Strike", "Sting"},
	{"Charge","Lunge","Strike"},
	{"Multihit","Rat Parry","Decisive Lunge", "Lunge","Multihit"},
	{"Tree Smash", "Strike", "Strike"},
	{"Rabbies", "Dashing Bite", "Bite"},
	{"Mocking Strike", "Mocking Slash","Mocking Lunge"},
	{"Tail Lash","Chomp", "Back Stab"},
	{"Sea Orb", "Tidal Vortex", "Blast", "Sea Orb"},
	{"Tri-Bite", "Multihit","Strike", "Multihit"},
	{"Hand Slam","Sonorous Roar", "Hand Slam","Heavy Strike"},
	{"Fire Orb", "Fire Orb", "Divinity", "Blast"},
	{"Strike", "Agility Dive", "Lunge", "Drain"},
	{"Duplicate Strike","Shadow Orb","Blast","Blast","Shadow Orb","Multihit"},
	{"Foot Stomp","Heavy Strike","Rapid Stomping","Foot Stomp"},
	{"Lunge","Charge","Lunge","Galloping Havoc"},
	{"Strike","Flaming Wing Strike", "Lunge"},
	{"Strike", "Roar", "Gatling Fists", "Strike"},
	{"Blast", "Toung Lash", "Hold Position"},
	{"Back Stab", "Lunge", "Blast"},
	{"Tsunami", "Whirlpool", "Lightning Storm", "Tidal Vortex", "Blast", "Blast", "Blast","Strike"},
	{"Lunge", "Strike","Snowball"},
	{"Strike", "Hand Slam", "Snowball", "Avalanche","Strike"},
	{"Burrowing Strike", "Strike", "Strike", "Sandball"},
	{"Lunge", "Strike","Bite", "Bite"},
	{"Jet Stream Slam","Bite", "Hold Position"},
	{"Bite", "Snap", "Drain", "Bash"},
	{"Infect", "Bite","Bite","Strike"},
	{"Roll", "Lunge","Bash","Steel Bash"},
	{"Ice Age Breath","Ice Orb", "Glacial Fissure", "Blast","Blast","Strike"},
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
	{"Strike", "Foreshadow", "Strike"},
	{"Tempest", "Strike", "Strike"},
	{ "Tempest", "Lunge","Lunge" },
	{ "Tempest", "Blast","Blast" },
	{ "Strike", "Decisive Lunge", "Multihit", "Toss A Mate", "Strike" },
	{ "Blast", "Fire Orb", "Sea Orb", "Shadow Orb", "Blast" },
	{ "Blast", "FIRE!" },
	{ "Bite", "Chomp", "Fury Strike", "Strike", "Bite" },
	{ "Blast","Egg Rapid Fire", "Blast" },
	{ "Blast", "Divinity","Drain","Blast" },
	{ "Chomp", "Strike", "Chomp", "Light Burst" },
	{ "Blast", "Lunge","Blast", "Shadow Orb" },
	{"Bake Some 'Bread'", "Strike", "Strike", "Lunge"},
	{ "Strike", "Trident Strike", "Sea Orb" },
	{ "Allure", "Shadow Orb", "Blast", "Blast" },
	{ "Allure", "Tail Lash", "Blast", "Bash", "Bite" },
	{ "Roll","Lunge","Bash","Bash","Roll", "Roll" },
	{ "Hold Position", "Snap", "Snap" },
	{ "Chomp","Clobber","Jaw Swing", "Chomp" },
	{ "Strike", "Agility Dive","Strike","Blast" },
	{ "Mud Slam", "Blast", "Strike", "Blast"},
	{"Malevolent Breath","Blast","Strike","Agility Dive","Call Of Hades","Eclipse"},
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
	{"Plop", "Multihit", "Lunge"},{"Roar", "Strike", "Blast"},{"Strike", "Bash", "Back Stab", "Silence"} };

	//list of the damage of the moves/attacks
	vector<vector<int>> moveValues = {
	{5, 4},
	{5,4,4},
	{6,7,4,4},
	{6,4,0,5},
	{4,5,6,0},
	{3,6,4,5},
	{0,4,5,7},
	{5,0,3,10,4},
	{6,5,4},
	{5,4,3},
	{4,5,6},
	{3,4,5},
	{6,5,3},
	{4,7,7,5,4},
	{7,3,4},
	{4,7,4},
	{5,7,5},
	{6,5,9},
	{4,7,4,6},
	{9,3,3,3},
	{7,9,8,5},
	{5,5,0,4},
	{4,5,5,4},
	{5,5,5,4,4,3},
	{9,9,5,6},
	{5,6,5,9},
	{4,6,5},
	{4,3,6,4},
	{5,7,4},
	{8,3,4},
	{15,7,9,7,6,6,6,5},
	{5,3,4},
	{4,7,4,9,4},
	{6,4,4,5},
	{5,3,4,5},
	{6,5,3},
	{5,5,4,5},
	{5,4,4,5},
	{5,5,4,7},
	{9,15,8,8,8,7},
	{10,4,5,5},
	{5,5,4,6},
	{6,5,5,7},
	{5,4,5,6},
	{4,5,5,6},
	{5,2,4,5},
	{5,5,4,5},
	{9,6,5,5,3},
	{10,7,5,5,4,8},
	{3,5,3,4},
	{3,4,5,5},
	{0,1},
	{3,5,0,3},
	{9,3,5,4},
	{0,7,9,6,5},
	{4,3,4},
	{4,5,4},
	{4,6,5},
	{4,6,5},
	{4,7,3,4,4},
	{5,4,5,6,5},
	{5,7},
	{5,6,6,4,4},
	{5,7,5},
	{5,0,4,5},
	{4,4,5,5},
	{5,5,4,6},
	{7,4,5,5},
	{3,5,5},
	{5,6,5,4},
	{5,7,5,5,4},
	{5,5,4,3,6,5},
	{3,5,4},
	{5,6,7,4},
	{3,5,4,5},
	{7,5,3,4},
	{15,7,5,8,8,5},
	{5,4,6},
	{9,5,6,5,4},
	{3,7,5,4},
	{4,6,5,5},
	{3,7,5},
	{0,5,4,4},
	{3,7,5,4},
	{6,7,5,4},
	{0,5,3,3,5},
	{4,5,4},
	{5,7,5,5,4},
	{6,5,3},
	{3,3,5,4,6},
	{3,6,4},
	{5,3,6,5},
	{7,3,5,4},
	{4,5,5},
	{3,5,4},
	{4,5,6,6},
	{5,0,3,5,3,3,0},
	{3,6,5,7},
	{4,3,5},{5,4,5},{3,5,5,4} };

	//list of the ranges of theri health
	vector<vector<int>> monHealthList = {{25,15},{30,25},{32,30},{35,30},{37,30},{25,20},{25,25},{30,23},{25,20},{32,28},{30,27},{35,30},{40,37},{50,40},{55,40},{35,30},{35,35},{45,43},{39,37},{35,32},{50,45},{40,37},{25,20},{35,32},{50,45},{37,33},{27,23},{45,43},{27,22},{30,25},{105,60},{32,25},{40,38},{46,30},{33,30},{27,25},{30,25},{22,20},{40,32},{105,60},{35,30},{35,32},{27,25},{32,30},{32,25},{40,32},{30,23},{32,30},{60,45},{30,24},{29,21},{5,5},{29,25},{28,25},{41,39},{45,35},{50,42},{50,42},{50,42},{53,40},{30,27},{23,19},{32,28},{32,24},{32,22},{37,29},{27,23},{34,23},{32,30},{32,27},{37,35},{29,23},{43,40},{43,37},{29,23},{42,40},{80,47},{23,19},{35,27},{39,32},{32,30},{29,23},{29,23},{27,26},{33,29},{31,26},{27,19},{29,26},{27,23},{30,25},{29,23},{30,23},{32,30},{50,42},{30,25},{35,25},{35,30},{32,29},{25,20},{29,27},{35,30}
	};

	//list to store the monsters the player has faught
	vector<string> resultVector;


	string gover = "Game Over\n\nScore: ", startplaceholder;
	srand(time(0)); // this will trigger the ability for random events to occur with the rand() command
	cout << "Welcome Wandering Warrior!" << endl<<endl << "Wizzard Wallace: I, Wizzard Wallace, have heard from the King that you, Warrior, will be embarking on a journey to a distant land!" << endl <<endl << "Wizzard Wallace: May I graciously ask you humble warrior how many monsters you expect to encounter in this journey?" << endl<<endl;
	cout << "How many monsters do you think you'll encounter: ";
	int x = 0, crazy = 0, end = 0, potions = 3, hp=50, score = 0, multiplier = 0,  hpAura=0, attackAura = 0, maxMultiplier=0, killedMonster=0;
	
	//opening "cutscene"
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
	for (int j = 0; j < monster; j++) {
		int responseInn = 0;
		fightMonster(maxMultiplier,hpAura,attackAura,resultVector,monster,j,end,multiplier, potions, hp, score, monsterList, moveList, monHealthList, moveValues);
		if (end == 0) {
			cin >> responseInn;
			killedMonster++;
			if (responseInn == 1) {
				hp = 50+(hpAura*5);
				multiplier = 0;
				cout << endl << endl << "Your health was fully resored and your multiplier has been reset." << endl << endl;
			}
			else {
				cout << endl << endl << "You decided to continue your journey." << endl << endl << endl;
			}
		}
		else { cout << gover << score << endl << endl; j += 100000; }
	}
	cout << "Wizzard Wallace: My my, welcome back Warrior. Your journey truly was succesful wasn't it. Could we possible have your name so we know to summon you when we need you again?" << endl << endl;
	string playerName;
	cout << "What's your name: ";
	cin >> playerName;
	string Score = "Name: ";
	Score += playerName + "\nScore: " + to_string(score) + "\nMaximum Multiplier: "+to_string(maxMultiplier)+"\nHP Aura Bonus: "+to_string(hpAura)+"\nAttack Aura Bonus: "+to_string(attackAura)+"\nMonsters fought: ";
	for (int k=0; k <=killedMonster; k++) { Score += resultVector[k] + "\n"; }
	ofstream myfile;
	myfile.open("Score.txt");
	myfile << Score;
	myfile.close();
}
