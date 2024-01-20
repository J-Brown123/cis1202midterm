// Jordan Brown 
// CIS 1202.800
// Sept. 15, 2022

#include <iostream>
#include <string>
#include <random>
#include <iomanip>

using namespace std;

//Enum
enum type { HUMANOID, BEAST, UNDEAD, MATERIAL };
enum items { LONGSWORD, CLAYMORE, SHIELD, RUNE_STAFF };
enum spells { FIREBALL, HEAL, SMITE };
enum characterNames { MAGE, KNIGHT, DRAGON, PRIEST, SKELETON, VAMPIRE, PALADIN, GOLEM, WEREWOLF };

//Struct
struct Spells
{
	int spell1 = -1;
	int spell2 = -1;
};

//Constants
int const CHARS = 9;
int const STATS = 9;
int const MAX_STAT = 255;
int const MIN_STAT = 0;
int const MAX_HP = 511;

//Function prototypes
int menu();
int damageSim(int[], int[]);
void battle(int[][STATS], string[]);
void displayCharStats(string[], int[][STATS]);
void displayItems();
void magicSim(int*, int*, Spells, int);
void search(const int[][STATS], const string[]);

int main()
{
	//Arrays
	string characters[CHARS] = { "MAGE", "KNIGHT", "DRAGON", "PRIEST", "SKELETON", "VAMPIRE",
		"PALADIN", "GOLEM", "WEREWOLF" };
	//Elements of following array (second subscript): 
	//0: HP, 1 : MP, 2: Attack, 3: Defense, 4: Intelligence, 5: Wisdom, 6: Speed, 7: Type, 8: Item Slot 
	int battleStats[CHARS][STATS] = { {200, 225, 90, 75, 230, 155, 80, 0, -1}, //Mage 0
									{375, 0, 230, 190, 35, 55, 115, 0, -1}, //Knight 1
									{500, 245, 225, 255, 235, 250, 75, 1, -1}, //Dragon 2
									{190, 235, 65, 85, 200, 235, 75, 0, -1}, //Priest 3
									{150, 0, 175, 35, 0, 35, 45, 2, -1}, //Skeleton 4
									{255, 0, 190, 135, 145, 190, 245, 2, -1}, //Vampire 5
									{400, 100, 200, 225, 115, 225, 100, 0, -1}, //Paladin 6
									{500, 0, 215, 255, 0, 50, 25, 3, -1}, //Golem 7
									{350, 0, 245, 190, 0, 45, 235, 1, -1} }; //Werewolf 8

	//Variables
	int selection;
	
	//Main Program Start
	cout << left << "ULTRA FANTASY BATTLE SIMULATOR\n\n";
	search(battleStats, characters);
	return 0;
}

int menu()
{
	string input;
	int selection;
	cout << "Choose from the following options:\n";
	cout << "1 - View Characters\n2 - View Items\n3 - Begin Battle\n4 - Exit\n";
	getline(cin, input);
	selection = stoi(input);
	while (selection < 1 || selection > 5)
	{
		cout << "Invalid response.\n";
		cout << "Choose from the following options:\n";
		cout << "1 - View Characters\n2 - View Items\n3 - Begin Battle\n4 - Search Highest\n5 - Exit\n";
		getline(cin, input);
		selection = stoi(input);
	}
	return selection;
}

void battle(int stat[][STATS], string chars[])
{
	string choice1, choice2, itemResponse, itemChoice, playerChoiceString, magicChoiceString;
	int index1, index2, item, random, response, playerChoice, enemyChoice, magicChoice, arr1[STATS], arr2[STATS];
	random_device Engine;
	uniform_int_distribution<int> quarterInt(75, 125);
	float variance;

	//Select first create dedicated array
	cout << "Choose your character:\n";
	for (int i = 0; i < CHARS; i++)
	{
		cout << i + 1 << " - " << chars[i] << endl;
	}
	getline(cin, choice1);
	index1 = stoi(choice1);
	while (index1 < 1 || index1 > CHARS)
	{
		cout << "Invalid response.\n";
		cout << "Choose your character:\n";
		for (int i = 0; i < CHARS; i++)
		{
			cout << i + 1 << " - " << chars[i] << endl;
		}
		getline(cin, choice1);
		index1 = stoi(choice1);
	}
	for (int i = 0; i < STATS; i++)
	{
		arr1[i] = stat[index1 - 1][i];
	}

	//Select second
	cout << "Choose your opponent:\n";
	for (int i = 0; i < CHARS; i++)
	{			
		cout << i + 1 << " - " << chars[i] << endl;
	}
	getline(cin, choice2);
	index2 = stoi(choice2);
	while (index2 < 1 || index2 > CHARS)
	{
		cout << "Invalid response.\n";
		cout << "Choose your character:\n";
		for (int i = 0; i < CHARS; i++)
		{
			cout << i + 1 << " - " << chars[i] << endl;
		}
		getline(cin, choice2);
		index2 = stoi(choice2);
	}
	for (int i = 0; i < STATS; i++)
	{
		arr2[i] = stat[index2 - 1][i];
	}

	//Get Items
	if (arr1[7] == HUMANOID || arr1[7] == UNDEAD)
	{
		cout << "Will " << chars[index1 - 1] << " have an item?\n1 - Yes\n2 - No\n";
		getline(cin, itemResponse);
		response = stoi(itemResponse);
		while (response != 1 && response != 2)
		{
			cout << "Invalid response\n1 - Yes\n2 - No\n";
			getline(cin, itemResponse);
			response = stoi(itemResponse);
		}
		cout << "Choose the item:\n";
		displayItems();
		getline(cin, itemChoice);
		item = stoi(itemChoice);
		while (item < 1 || item > 4)
		{
			cout << "Invalid reponse.\n";
			displayItems();
			getline(cin, itemChoice);
			item = stoi(itemChoice);
		}
		arr1[8] = item - 1;
	}
	if (arr2[7] == HUMANOID || arr2[7] == UNDEAD)
	{
		cout << "Will " << chars[index2 - 1] << " have an item?\n1 - Yes\n2 - No\n";
		getline(cin, itemResponse);
		response = stoi(itemResponse);
		while (response != 1 && response != 2)
		{
			cout << "Invalid response\n1 - Yes\n2 - No\n";
			getline(cin, itemResponse);
			response = stoi(itemResponse);
		}
		cout << "Choose the item:\n";
		displayItems();
		getline(cin, itemChoice);
		item = stoi(itemChoice);
		while (item < 1 || item > 4)
		{
			cout << "Invalid reponse.\n";
			displayItems();
			getline(cin, itemChoice);
			item = stoi(itemChoice);
		}
		arr2[8] = item - 1;
	}

	//Incorporate items
	if (arr1[8] == LONGSWORD)
		arr1[2] += 50;
	else if (arr1[8] == CLAYMORE)
		arr1[2] += 75;
	else if (arr1[8] == SHIELD)
		arr1[3] += 50;
	else if (arr1[8] == RUNE_STAFF)
		arr1[4] += 75;

	if (arr2[8] == LONGSWORD)
		arr2[2] += 50;
	else if (arr2[8] == CLAYMORE)
		arr2[2] += 75;
	else if (arr2[8] == SHIELD)
		arr2[3] += 50;
	else if (arr2[8] == RUNE_STAFF)
		arr2[4] += 75;

	//Battle Menu
	int damage;
	bool playerDefend = false;
	bool enemyDefend = false;
	do
	{
		//Reset Defense
		if (playerDefend == true)
		{
			playerDefend = false;
			arr1[3] -= 100;
		}
		if (enemyDefend == true)
		{
			enemyDefend = false;
			arr2[3] -= 100;
		}

		//Player Turn
		cout << "What would you like to do?\n";
		cout << "1 - Fight\n2 - Defend\n3 - Magic\n4 - Run\n";
		getline(cin, playerChoiceString);
		playerChoice = stoi(playerChoiceString);
		while (playerChoice < 1 || playerChoice > 4)
		{
			cout << "Invalid reponse.\n";
			cout << "1 - Fight\n2 - Defend\n3 - Magic\n4 - Run\n";
			getline(cin, playerChoiceString);
			playerChoice = stoi(playerChoiceString);
		}
		if (index1 - 1 == KNIGHT || index1 - 1 == SKELETON || index1 - 1 == VAMPIRE || index1 - 1 == WEREWOLF || index1 - 1 == GOLEM)
			while (playerChoice == 3)
			{
				cout << "This character cannot use magic.\nChoose another option.\n";
				cout << "1 - Fight\n2 - Defend\n3 - Magic\n4 - Run\n";
				getline(cin, playerChoiceString);
				playerChoice = stoi(playerChoiceString);
				while (playerChoice < 1 || playerChoice > 4)
				{
					cout << "Invalid reponse.\n";
					cout << "1 - Fight\n2 - Defend\n3 - Magic\n4 - Run\n";
					getline(cin, playerChoiceString);
					playerChoice = stoi(playerChoiceString);
				}
			}

		switch (playerChoice)
		{
		case 1: damage = damageSim(arr1, arr2);
			arr2[0] -= damage;
			break;
		case 2: playerDefend = true;
			arr1[3] += 100;
			break;
		case 3: 
		{
			Spells spellList;
			if (index1 - 1 == MAGE)
			{
				spellList.spell1 = FIREBALL;
			}
			else if (index1 - 1 == DRAGON)
			{
				spellList.spell1 = FIREBALL;
				spellList.spell2 = HEAL;
			}
			else if (index1 - 1 == PRIEST || index1 - 1 == PALADIN)
			{
				spellList.spell1 = SMITE;
				spellList.spell2 = HEAL;
			}

			cout << "Choose the spell\n";
			if (spellList.spell1 == FIREBALL)
				cout << "1 - Fireball\n";
			else if (spellList.spell1 == SMITE)
				cout << "1 - Smite\n";
			if (spellList.spell2 == HEAL)
				cout << "2 - Heal\n";
			getline(cin, magicChoiceString);
			magicChoice = stoi(magicChoiceString);
			while (magicChoice < 1 || magicChoice > 2)
			{
				cout << "Invalid response.\n";
				cout << "Choose the spell\n";
				if (spellList.spell1 == FIREBALL)
					cout << "1 - Fireball\n";
				else if (spellList.spell1 == SMITE)
					cout << "1 - Smite\n";
				if (spellList.spell2 == HEAL)
					cout << "2 - Heal\n";
				getline(cin, magicChoiceString);
				magicChoice = stoi(magicChoiceString);
			}
			int* ptr1 = arr1;
			int* ptr2 = arr2;
			magicSim(ptr1, ptr2, spellList, magicChoice);
		}
			break;
		case 4: int speed1, speed2;
			random = quarterInt(Engine);
			variance = random / 100.00;
			speed1 = arr1[6] * variance;
			random = quarterInt(Engine);
			variance = random / 100.00;
			speed2 = arr2[6] * variance;
			if (speed1 >= speed2)
			{
				cout << "You got away!";
				return;
			}
			else
				cout << "Not fast enough";
			break;
		}

		//Enemy Turn
		uniform_int_distribution<int> enemyInt(1, 3);
		uniform_int_distribution<int> enemyMagic(1, 2);

		int randomAI;
		randomAI = enemyInt(Engine);

		switch (randomAI)
		{
		case 1: damage = damageSim(arr2, arr1);
			arr1[0] -= damage;
			break;
		case 2: enemyDefend == true;
			arr2[3] += 100;
			break;
		case 3: randomAI = enemyMagic(Engine);
			Spells newSpellList;
			if (index1 - 1 == MAGE)
			{
				newSpellList.spell1 = FIREBALL;
			}
			else if (index1 - 1 == DRAGON)
			{
				newSpellList.spell1 = FIREBALL;
				newSpellList.spell2 = HEAL;
			}
			else if (index1 - 1 == PRIEST || index1 - 1 == PALADIN)
			{
				newSpellList.spell1 = SMITE;
				newSpellList.spell2 = HEAL;
			}
			int* newPtr1 = arr2;
			int* newPtr2 = arr1;

			magicSim(newPtr1, newPtr2, newSpellList, randomAI);
			break;
		}

	} while (arr1[0] > MIN_STAT && arr2[0] > MIN_STAT);
	return;
}

int damageSim(int arr1[], int arr2[])
{
	int att, def, final_att, random, damage;
	float variance;
	//0: HP, 1 : MP, 2: Attack, 3: Defense, 4: Intelligence, 5: Wisdom, 6: Speed, 7: Type, 8: Item Slot 
	random_device Engine;
	uniform_int_distribution<int> quarterInt(75, 125);
	att = arr1[2];
	def = arr2[3];

	//Apply variance
	random = quarterInt(Engine);
	variance = random / 100.00;
	final_att = att * variance;
	damage = final_att - def;
	//Return damage
	if (damage > 0)
		return damage;
	else
		return 1;
}

void displayCharStats(string chars[], int stat[][STATS])
{
	string statNames[STATS] = { "HP", "MP", "ATT", "DEF", "INT", "WIS", "SPD" };
	for (int i = 0; i < CHARS; i++)
	{
		cout << setw(10) << chars[i];
	}
	cout << endl;
	//0: HP, 1 : MP, 2: Attack, 3: Defense, 4: Intelligence, 5: Wisdom, 6: Speed, 7: Type, 8: Item Slot 
	for (int i = 0; i < STATS - 2; i++)
	{
		for (int j = 0; j < CHARS; j++)
		{
			cout << setw(5) << statNames[i] << setw(5) << stat[j][i];
		}
		cout << endl;
	}
	return;
}

void displayItems()
{
	cout << setw(16) << "1 - Longsword:" << setw(7) <<  "+50 ATT\n";
	cout << setw(16) << "2 - Claymore:" << setw(7) << "+75 ATT\n";
	cout << setw(16) << "3 - Shield:" << setw(7) << "+50 DEF\n";
	cout << setw(16) << "4 - Runestaff:" << setw(7) << "+75 INT\n";
	return;
}

void magicSim(int* ptr1, int* ptr2, Spells spellList, int choice)
{
	int damage, heal, random, modifier;
	random_device Engine;
	uniform_int_distribution<int> magicVar(50, 100);
	float variance;

	switch (choice)
	{
	case 1: if (spellList.spell1 == FIREBALL)
		{
			random = magicVar(Engine);
			variance = random / 100.00;
			modifier = *(ptr1 + 4) * variance;
			damage = 50 + modifier;
			*ptr2 -= damage;
			cout << damage << " damage dealt.\n";
			*(ptr1 + 1) -= 15;
		}
		  else if (spellList.spell2 == SMITE)
		{
			random = magicVar(Engine);
			variance = random / 100.00;
			if (*(ptr2 + 7) == UNDEAD)
				modifier = *(ptr1 + 4) * variance * 1.25;
			else
				modifier = *(ptr1 + 4) * variance;
			damage = 50 + modifier;
			*ptr2 -= damage;
			cout << damage << " damage dealt.\n";
			*(ptr1 + 1) -= 15;
		}
		  break;
	case 2: if (spellList.spell1 == HEAL)
		{
			random = magicVar(Engine);
			variance = random / 100.00;
			heal = *(ptr1 + 5) * variance;
			*ptr1 += heal;
			cout << heal << " health restored.\n";
			*(ptr1 + 1) -= 20;
		}
		  else if (spellList.spell2 == -1)
		{
			random = magicVar(Engine);
			variance = random / 100.00;
			modifier = *(ptr1 + 4) * variance;
			damage = 50 + modifier;
			*(ptr2) -= damage;
			cout << damage << " damage dealt.\n";
			*(ptr1 + 1) -= 15;
		}
		break;
	}
	return;
}

void search(const int arr[][STATS], const string names[])
{
	string selection;
	int choice;

	//0: HP, 1 : MP, 2: Attack, 3: Defense, 4: Intelligence, 5: Wisdom, 6: Speed
	cout << "Choose the stat to search for the highest\n";
	cout << "1 - HP\n2 - MP\n3 - ATT\n4 - DEF\n5 - INT\n5 - WIS\n6 - SPD\n";
	getline(cin, selection);
	choice = stoi(selection);
	while (choice < 1 || choice > 6)
	{
		cout << "Invalid response.\n";
		cout << "Choose the stat to search for the highest\n";
		cout << "1 - HP\n2 - MP\n3 - ATT\n4 - DEF\n5 - INT\n5 - WIS\n6 - SPD\n";
		getline(cin, selection);
		choice = stoi(selection);
	}

	//Search array
	int max, i;

	for (max = CHARS - 1; max > 0; max--)
	{
		for (i = 0; i < max; i++)
		{
			if (arr[i][choice - 1] < arr[i + 1][choice - 1])
			{
				swap(arr[i][choice - 1], arr[i + 1][choice - 1]);
				swap(names[i], names[i + 1]);
			}
		}
	}
	cout << "The highest is the " << names[0] << " with a value of " << arr[0][choice - 1];
	return;
}