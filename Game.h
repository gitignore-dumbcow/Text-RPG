#include "ArtworkLibrary.h"
#include "Monster.h"
#include "Sprite.h"
#include "Random.h"
#include "Player.h"
#include "StringModifier.h"
#include "ActionManager.h"
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
	bool gameRunning = false;
	bool createNewMonster = true;
	bool currentMonsterDead = false;
	int screenIndex = 0;
	char input = ' ';

	ArtworkLibrary library;

	//Title
	string titleArt = library.title;
	Sprite* title = new Sprite(titleArt);

	//Monster
	string corpseArt = library.corpse;
	string batArt = library.bat;
	string ratArt = library.rat;


	Monster* bat = new Monster("BAT", "A flying mouse, weak but agile. Its wings provide excelent cover.", batArt, 3, 1, 0, 3);
	Monster* rat = new Monster("RAT", "A non-flying mouse, weak. It always carries a slice of cheese.", ratArt, 2, 1, 0, 1);

	std::vector<Monster*> monsters = {bat, rat};

	Monster* currentMonster = nullptr;

	//Player
	string name;

	Player* player = new Player();

	//Settings
	bool showMonster = true;
	bool showPlayer = false;
	bool showAction = true;
	bool showDeathInfo = true;

	//Recorder
	string killedBy = "";
	int monsterKilled = 0;
};

