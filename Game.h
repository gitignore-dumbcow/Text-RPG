#include "ArtworkLibrary.h"
#include "Monster.h"
#include "Sprite.h"
#include "Random.h"
#include "Player.h"
#include "StringModifier.h"
#include "ActionManager.h"
#include "Equipable.h"
#include "Consumable.h"
#include <vector>
#include <conio.h>

class Game
{	
public:
	Game() {};

	void Start();
	void Exit();
	void Update();
	void InputHandle();
	void LateUpdate();
	void Draw();
	void Clear();
	
private:
	bool isAdmin = false;
	bool gameRunning = false;
	bool createNewMonster = true;
	bool currentMonsterDead = false;
	bool playerDead = false;
	int screenIndex = 0;
	char input = ' ';

	ArtworkLibrary library;

	//Title
	string titleArt = library.title;
	Sprite* title = new Sprite(titleArt);


#pragma region LootDatabase
#pragma region Definitions
	//Starter
	Equipable* fist = new Equipable("Fist", "( \x1B[33m+1\033[0m SPD ) Martials art never let you down", 0, 0, 0, 2);
	Equipable* naked = new Equipable("None", " ( \x1B[33m+1\033[0m SPD ) Feels lika a barbarian.", 0, 0, 0, 1);
	Equipable* none = new Equipable("None", "No trinket, no problem.", 0, 0, 0, 0);


	//Weapons
	Equipable* woodenKnife = new Equipable("Wooden Knife", "( \x1B[33m+1\033[0m ATK ) Quick but a little dull.", 0, 1, 0, 0);
	Equipable* woodenSword = new Equipable("Wooden Sword", "( \x1B[33m+3\033[0m ATK ) Heafty, deal great amount of blunt damage.", 0, 3, 0, -1);
	//Armors
	Equipable* tShirt = new Equipable("T-Shirt", " ( \x1B[33m+1\033[0m HP ) Just a piece of comfy cloth.", 1, 0, 0, 0);
	Equipable* woodenPlates = new Equipable("Wooden Plates", " ( \x1B[33m+1\033[0m DEF ) A double-sided wooden plate, will protect you from few scratches.", 0, 0, 1, 0);
	Equipable* jacket = new Equipable("Jacket", "( \x1B[33m+3\033[0m HP ) It protect you from your fear.", 3, 0, 0, 0);

	//Accessories
	Equipable* ringOfHaste = new Equipable("Ring of Haste", "( \x1B[33m+1\033[0m SPD ) The green aura makes your adrenaline flich.", 0, 0, 0, 1);
	Equipable* ringOfGiant = new Equipable("Ring of Giant", "( \x1B[33m+5\033[0m HP ) This ring is really big, 30 push-ups to lift it.", 5, 0, 0, 0);
	Equipable* ringOfStone = new Equipable("Ring of Stone", "( \x1B[33m+1\033[0m DEF ) BOLD.", 0, 0, 1, 0);
	Equipable* ringOfPower = new Equipable("Ring of Power", "( \x1B[33m+1\033[0m ATK ) The red aura makes you think you have to make it quick.", 1, 0, 0, 0);
#pragma endregion
#pragma region Table
	//Tier 0
	vector<Equipable*> tier0Weapons = {fist, woodenKnife};
	vector<Equipable*> tier0Armors = { tShirt, naked};
	vector<Equipable*> tier0Accessories = { ringOfHaste, ringOfGiant, ringOfStone, ringOfPower, none };


	//Tier 1
	vector<Equipable*> tier1Weapons = {woodenKnife, woodenSword};
	vector<Equipable*> tier1Armors = {tShirt, woodenPlates, jacket};
	vector<Equipable*> tier1Accessories = {ringOfHaste, ringOfGiant, ringOfStone, ringOfPower};

	//Tier 2
	vector<Equipable*> tier2Weapons = {};
	vector<Equipable*> tier2Armor = {};
	vector<Equipable*> tier2Accessories = {};

	//Tier 3
	vector<Equipable*> tier3Weapons = {};
	vector<Equipable*> tier3Armors = {};
	vector<Equipable*> tier3Accessories = {};
#pragma endregion
#pragma endregion

	//Monster
	string corpseArt = library.corpse;
	string batArt = library.bat;
	string ratArt = library.rat;

	Monster* bat = new Monster("BAT", "A flying mouse, weak but agile. Its wings provide excelent cover.", batArt, 3, 2, 0, 2);
	Monster* rat = new Monster("RAT", "A non-flying mouse, weak. It always carries a slice of cheese.", ratArt, 2, 2, 0, 1);

	std::vector<Monster*> monsters = {bat, rat};

	Monster* currentMonster = nullptr;

	//Player
	string name;

	Player* player = nullptr;

	//Settings
	bool showMonster = true;
	bool showPlayer = false;
	bool showAction = true;
	bool showDeathInfo = true;

	//Recorder
	string killedBy = "";
	int monsterKilled = 0;
};

