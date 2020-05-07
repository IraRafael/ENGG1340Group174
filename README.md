# ENGG1340Group174

ENGG1340 Project of 3035691054. I am Cheng Ira Rafael D and I am a year 1 BENGG strudent with the UID 3035691054; this is a solo project as my group mate hasn't to my emails for the group project, I was in group 144, and we made zero progress therefore this is my solo project.

The game I will be implementing will be called Wandering Warrior, it is a text based monster battling adventure game where a player will be able to fight monsters in a text based style. The player will have to respond using inputs of the corresponding numbers as shown in the UI 

The game will start by asking how many monsters you would like to encounter and the player can input the number and he will then fight monsters with random names and statistics.

I intend to implement a critical strike mechanic which will increase the damage output of the player by 50% and randomly occurs.

Players can chose to continue on their journey and immediately fight a monster or rest at an Inn. Resting at an inn will break their combo. Implemented a combo mechanic where the player's score increases faster for each consecutive monster Killed without stopping at an inn using a multiplier that is passed on after each consecutive fight:

score += 10 + legendMonsterBonus + highMonsterBonus + multiplier * (10 + legendMonsterBonus + highMonsterBonus);

Above is the equation used to calculate the score using the multiplier as shown, legendMonsterBonus and highMonsterBonus are bonuses you recieve after defeating certain stronger monsters; 


Many events from the game, namely the chance of critical strike, what monsters will appear, and what attacks they will use against you, will make use of a random number generator. This includes codes from <rand>, <ctime> and <cstdlib>. The random number generator will be a function returning the random number for use in the main code. The function used from my code is shown bellow: 
 
int randNumber(int upper, int lower) {
	//upper is the upper limit number and lower is the lower limit number
	//this function is made to generate a number between upper adn lower
	int Y = rand() % ((upper - lower) + 1) + lower;
	
	return Y;
}

Where Y is the number that is then used for the process that this code was sued for: eg, critical strike chance calculation.
Also the random number generator is linked with vector lists from <vector> which are lists of the monsters and a list of their attributes like health and their attacking moves and the respective damage.
