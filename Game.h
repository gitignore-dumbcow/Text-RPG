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
#include <cmath>
#include "Log.h"
#pragma once

using namespace std;

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
	int currentTier = 1;
	int currentDifficulty = 1;
	int difficultyMultiplier = 1;
	char input = ' ';

	ArtworkLibrary library;

	//Title
	string titleArt = library.title;
	Sprite* title = new Sprite(titleArt);


#pragma region LootDatabase
#pragma region Definitions
	//Starter
	Equipable* fist = new Equipable("Fist", "Martials art never let you down.", 0, 0, 0, 2, Weapon);
	Equipable* naked = new Equipable("None", "Feels lika a barbarian.", 0, 0, 0, 1, Armor);
	Equipable* none = new Equipable("None", "No trinket, no problem.", 1, 0, 0, 0, Accessory);

	//Weapons
	Equipable* woodenKnife = new Equipable("Wooden Knife", "Quick but a little dull.", 0, 1, 0, 0, Weapon);
	Equipable* woodenSword = new Equipable("Wooden Sword", "Heafty, deal great amount of blunt damage.", 0, 3, 0, 0, Weapon);
	Equipable* rustyKnife = new Equipable("Rusty Knife", "A knife, damaged by time, and blood.", 0, 3, 0, 0, Weapon);
	Equipable* shadowDagger = new Equipable("Shadow Dagger", "You can see it, but scared of it.", 0, 4, 0, 1, Weapon);
	Equipable* deathScythe = new Equipable("Death Scythe", "1 Soul, 2 Souls, 3 Souls...", 0, 5, 0, 0, Weapon);
	Equipable* obsidianClaw = new Equipable("Obsidian Claw", "Why nature is always scary.", 0, 7, 0, -1, Weapon);
	Equipable* godKiller = new Equipable("God Killer", "Once there were ruler of the world.", 0, 10, 0, 0, Weapon);
	Equipable* nebulaBlade = new Equipable("Nebula Blade", "You are unfair.", 0, 12, 0, 0, Weapon);

	//Armors
	Equipable* tShirt = new Equipable("T-Shirt", "Just a piece of comfy cloth.", 1, 0, 0, 0, Armor);
	Equipable* woodenPlates = new Equipable("Wooden Plates", "A double-sided wooden plate, will protect you from few scratches.", 0, 0, 1, 0, Armor);
	Equipable* jacket = new Equipable("Jacket", "It protect you from your fear.", 3, 0, 0, 0, Armor);
	Equipable* hardShell = new Equipable("Hard Shell", "Hardened, tight, no room for movement.", 4, 0, 2, -2, Armor);
	Equipable* ironChestPlates = new Equipable("Iron Chest Plate", "The art of medieval is metal, and glory.", 1, 0, 5, -3, Armor);
	Equipable* holyCloak = new Equipable("Holy Cloak", "Embeded in the humanity belief.", 7, 0, 1, 0, Armor);
	Equipable* shadowScales = new Equipable("Shadow Scales", "It helps to camouflage from predators.", 0, 0, 1, 6, Armor);
	Equipable* crystalFur = new Equipable("Crystal Fur", "The sharp fur make it a great weapon while being an funny-looking armor.", 5, 2, 1, -2, Armor);
	Equipable* lightBinded = new Equipable("Light Binded", "Light is good, dark is evil.", 5, -2, 3, 1, Armor);
	Equipable* sunGuard = new Equipable("Sun Guard", "You don't fear anything now.", 5, 0, 6, 0, Armor);
	Equipable* mythWeaved = new Equipable("Myth Weaved", "Sound like a legendary, a myth. Unreal.", 5, 5, 5, 5, Armor);

	//Accessories
	Equipable* ringOfHaste = new Equipable("Ring of Haste", "The green aura makes your adrenaline flich.", 0, 0, 0, 1, Accessory);
	Equipable* ringOfGiant = new Equipable("Ring of Giant", "This ring is really big, 30 push-ups to lift it.", 5, 0, 0, 0, Accessory);
	Equipable* ringOfStone = new Equipable("Ring of Stone", "BOLD.", 0, 0, 1, 0, Accessory);
	Equipable* ringOfPower = new Equipable("Ring of Power", "The red aura makes you think you have to make it quick.", 0, 1, 0, 0, Accessory);
	Equipable* batWings = new Equipable("Bat Wings", "I'm Batman.", 2, 0, 0, 1, Accessory);

	Equipable* ringOfDestruction = new Equipable("Ring of Destruction", "It's the rule of life, to kill or be destroyed.", 0, 4, -1, 0, Accessory);
	Equipable* ringOfAbsorbant = new Equipable("Ring of Absorbant", "You don't have any enemy.", 5, 0, 2, 0, Accessory);
	Equipable* ringOfVelocity = new Equipable("Ring of Velocity", "V = d/t.", 0, -1, 0, 4, Accessory);
	Equipable* ringOfResitance = new Equipable("Ring of Resistance", "It even resits yourself.", -5, 0, 5, 0, Accessory);

	Equipable* bagOfBones = new Equipable("Bag of Bones", "Calcium is good, far better than silicium.", 3, 0, 1, 0, Accessory);
	Equipable* shadowPhaser = new Equipable("Shadow Phaser", "aka. invisibility.", -5, 0, 0, 3, Accessory);
	Equipable* lightKiller = new Equipable("Light Killer", "The predator goes for the hunt.", -5, 1, 0, 2, Accessory);
	Equipable* ancientHorn = new Equipable("Ancient Horn", "At the beginning, when there is no weapon, horns took the match.", 5, 3, 0, -1, Accessory);
	Equipable* deathSensor = new Equipable("Death Sensor", "At the neck, always the neck.", 0, 6, 0, -1, Accessory);
	Equipable* everScream = new Equipable("Ever Scream", "aaaaaaaaaaaaaaaaAAAAAAAAAA.", 6, 6, 6, -6, Accessory);
	Equipable* jukebox = new Equipable("Juke Box", "C F Dm G Am A.", 0, 0, 0, 7, Accessory);
	Equipable* amuletOfPrecision = new Equipable("Amulet of Precision", "One shot, one kill.", 10, 0, 0, 0, Accessory);
	Equipable* amuletOfProtection = new Equipable("Amulet of Protection", "A hundred blows, where did it go.", 0, 0, 10, 0, Accessory);

	//Consumables
	Consumable* smallHPotion = new Consumable("Small Health Potion", "Look and taste like strawberry.", 3);
	Consumable* cheese = new Consumable("Cheese", "Fun fact rats don't like cheese.", 2);
	Consumable* HPotion = new Consumable("Health Potion", "Look and taste like lemon.", 5);
	Consumable* biglHPotion = new Consumable("Big Health Potion", "Blood.", 8);
	Consumable* calcium = new Consumable("Calcium", "Ca.", 3);
	Consumable* biteOfLight = new Consumable("Bite of Light", "Photon.", 6);
	Consumable* restorativeWater = new Consumable("Restorative Water", "Holified water.", 7);
	Consumable* theApple = new Consumable("the Apple", "No wonder why it is the beginning of life.", 10);

#pragma endregion
#pragma region Table
	//Starter
	vector<Equipable*> starter[3] = {
		//Weapons
			{fist, woodenKnife},
		//Armors
			{ tShirt, naked},
		//Accessories
			{ ringOfHaste, ringOfGiant, ringOfStone, ringOfPower, none },

	};

	vector<Item*> batLoot = { tShirt, batWings, smallHPotion, ringOfHaste};
	vector<Item*> ratLoot = { cheese };
	vector<Item*> bugLoot = { hardShell, bagOfBones, calcium , smallHPotion, ringOfStone };
	vector<Item*> gloomLoot = { woodenKnife, woodenSword, woodenPlates, shadowDagger, deathScythe, shadowScales, shadowPhaser, biglHPotion, biteOfLight, ringOfAbsorbant, ringOfDestruction };
	vector<Item*> murkLoot = { jacket, woodenSword, woodenPlates, woodenKnife, lightKiller , HPotion, biteOfLight, ringOfPower, ringOfResitance };
	vector<Item*> behemothLoot = { obsidianClaw, godKiller, crystalFur, ancientHorn, restorativeWater, ringOfGiant, ringOfResitance, ringOfAbsorbant, ringOfStone };
	vector<Item*> assassinLoot = { rustyKnife, jacket, woodenKnife, deathSensor, deathScythe, biglHPotion, restorativeWater, ringOfDestruction,ringOfHaste, ringOfPower,ringOfVelocity };
	vector<Item*> horrorLoot = { godKiller, lightBinded, everScream, ironChestPlates, biglHPotion, biteOfLight, ringOfAbsorbant, ringOfDestruction,ringOfHaste,ringOfPower,ringOfVelocity };
	vector<Item*> lunaticLoot = { rustyKnife, holyCloak, jukebox, biglHPotion, biteOfLight, ringOfDestruction,ringOfHaste,ringOfPower, ringOfVelocity };
	vector<Item*> artemisLoot = { nebulaBlade, sunGuard, mythWeaved, amuletOfPrecision, biglHPotion, restorativeWater, theApple, deathScythe };
	vector<Item*> orionLoot = { nebulaBlade, sunGuard, mythWeaved, amuletOfProtection, biglHPotion, restorativeWater, theApple };
	vector<Item*> bossLoot = { };


#pragma endregion
#pragma endregion

	//Monster
	string corpseArt = library.corpse;
	string batArt = library.bat;
	string ratArt = library.rat;
	string bugArt = library.bug;
	string gloomArt = library.gloom;
	string murkArt = library.murk;
	string behemothArt = library.behemoth;
	string assassinArt = library.assassin;
	string horrorArt = library.horror;
	string lunaticArt = library.lunatic;
	string artemisArt = library.artemis;
	string orionArt = library.orion;
	string bossArt = library.boss;

	//Monster(name, des, art, loot, hp, atk, def, spd, special)
	Monster* bat = new Monster("BAT", "A flying mouse, weak but agile. Its wings provide excelent cover.",
								batArt, batLoot, 3, 2, 0, 2);
	Monster* rat = new Monster("RAT", "A non-flying mouse, weak. It always carries cheese.",
								ratArt, ratLoot, 4, 2, 0, 1);
	Monster* bug = new Monster("BONE BUG", "A micro-sized bug, hard to hit. It chews your bones.",
								bugArt, bugLoot, 1, 4, 2, 12);
	Monster* gloom = new Monster("GLOOM STRIKE", "It's more terrifying if you don't know what hit you.",
								gloomArt, gloomLoot, 7, 5, 2, 3);
	Monster* murk = new Monster("MURK", "Stare at the dark too long and you eventually see what isn't there.",
								murkArt, murkLoot, 5, 3, 2, 3);
	Monster* behemoth = new Monster("BEHEMOTH", "A mythical giant creature. Don't ever think about riding it.",
								behemothArt, behemothLoot, 10, 4, 5, 3);
	Monster* assassin = new Monster("ASSASSIN", "You've gone too far, there will eventually someone hunting you down.",
								assassinArt, assassinLoot, 7, 9, 3, 6);
	Monster* horror = new Monster("CORRUPT HORROR", "Not even it could escape the corruption. The most feared, terrifying beast that lurks within every shadow.",
								horrorArt, horrorLoot, 12, 6, 4, 3);
	Monster* lunatic = new Monster("LUNATIC", "Withered, cold blooded, corrupted. Broken.",
								lunaticArt, lunaticLoot, 4, 4, 2, 20);
	Monster* artemis = new Monster("ARTEMIS", "The goddess of the hunt.",
								artemisArt, artemisLoot, 12, 8, 6, 9);
	Monster* orion = new Monster("ORION", "The godfather of the hunt.",
								orionArt, orionLoot, 15, 10, 8, 5);
	
	Monster* boss = new  Monster("LORD VRAXX", "The guardian of the cosmos.",
								bossArt, bossLoot, 30, 16, 4, 16);

	std::vector<Monster*> tier1monsters = { bat, rat };
	std::vector<Monster*> tier2monsters = { bug, murk };
	std::vector<Monster*> tier3monsters = { gloom, assassin};
	std::vector<Monster*> tier4monsters = { horror, lunatic , behemoth};
	std::vector<Monster*> tier5monsters = { orion, artemis };

	Monster* currentMonster = nullptr;


	//Player
	string name;

	Player* player = nullptr;

	//Settings
	bool showMonster = true;
	bool showPlayer = true;
	bool showAction = true;
	bool showDeathInfo = true;
	bool showLoot = true;
	bool showInventory = false;
	bool showLog = false;

	int mode = 0;

	//Recorder
	string killedBy = "";
	int monsterKilled = 0;

	//Functions
	void NextFight();
	void ConfigEquipable();
	void ConfigConsumable();

	//Draw
	void DrawMenu();
	void DrawStart();
	void DrawSetting();
	void DrawDeath();
	void DrawStats();
	void DrawWin();

	void DrawCombatAct();
	void DrawLootAct();

	void DrawPlayer();
	void DrawMonster();

	void DrawLoot();
	void DrawInventory();

	void DrawLog();
};

