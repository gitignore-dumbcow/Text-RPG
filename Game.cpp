#include "Game.h"

void Game::Start()
{
	screenIndex = 0;
	gameRunning = true;
	Update();
}

void Game::Update()
{
	while (gameRunning)
	{
		Random::Update();
		input = ' ';
		switch (screenIndex)
		{
		case 1:

			name = "";

			if (player != nullptr)
			{
				delete player;

			}

			player = new Player(
				tier0Weapons.at(Random::Range(0, (int)tier0Weapons.size() - 1)),
				tier0Armors.at(Random::Range(0, (int)tier0Armors.size() - 1)),
				tier0Accessories.at(Random::Range(0, (int)tier0Accessories.size() - 1))
			);

			
			break;
		case 2:
			
			//Player
			player->Update();

			if (player != nullptr)
			{
				playerDead = player->currentHP <= 0;

				if (isAdmin)
				{
					player->level = 100;
					player->hitpoints = 20;
					player->currentHP = 20;
					player->baseAttack = 99;
					player->baseDefence = 99;
					player->baseSpeed = 99;
					player->attackMod = 1;
					player->defenceMod = 1;
					player->speedMod = 1;
				}
			}

			//Monster

			if (createNewMonster)
			{
				createNewMonster = false;

				if(currentMonster != nullptr) delete currentMonster;

				currentMonster = new Monster(*monsters.at(Random::Range(0, (int)monsters.size() - 1)));
			}

			if (currentMonster != nullptr)
			{
				currentMonster->Update();

				currentMonsterDead = currentMonster->currentHP == 0;

			}



			break;
		default:
			break;
		}
		Draw();
		InputHandle();
		LateUpdate();
		Clear();
	}
	Exit();
}

void Game::InputHandle()
{
	switch (screenIndex)
	{
	case 1:
		cin >> name;
		break;
	default:
		input = _getch();
		break;
	}
	
}

void Game::LateUpdate()
{
	switch (screenIndex)
	{
	case 0:
		if (input == 'a') screenIndex++;
		if (input == 'b') screenIndex = 98;
		if (input == 'c') gameRunning = false;
		
		break;
	case 1:
		name = StringModifier::ToUpper(name);
		isAdmin = name == "ADMIN";
		player->name = name;
		screenIndex++;
		break;
	case 2:
		if (input == 'p') showPlayer = !showPlayer;
		if (input == 'm') showMonster = !showMonster;
		if (input == 'a') showAction = !showAction;

		//Actions
		if (!playerDead)
		{
			if (input == '1')
			{
				if (currentMonsterDead)
				{
					screenIndex = 97;
				}
				else
				{
					ActionManager::Duel(player, currentMonster);
					ActionManager::Duel(currentMonster, player);
				}

				
			}
			if (input == '2')
			{
				delete currentMonster;
				currentMonster = nullptr;
				createNewMonster = true;
				break;
			}
		}
		else
		{
			if (input == 'c')
			{
				screenIndex = 99;
				if (currentMonster != nullptr)
				{
					
					killedBy = currentMonster->name;
					delete currentMonster;
					currentMonster = nullptr;
					createNewMonster = true;
				}
				
				
			}
		}
		
		if (currentMonster != nullptr)
		{
			//Monster
			if (currentMonster->currentHP <= 0)
			{
				monsterKilled++;
				currentMonster->artwork = corpseArt;
			}
		}

		break;
	case 97:
		if (input == 'r') screenIndex = 2;
		break;
	case 98:
		if (input == '1') showMonster = !showMonster;
		if (input == '2') showPlayer = !showPlayer;
		if (input == '3') showAction = !showAction;
		if (input == '4') showDeathInfo = !showDeathInfo;
		if (input == 'r') screenIndex = 0;
		break;
	case 99:
		if (input == 'a') screenIndex = 0;
		if (input == 'b') gameRunning = false;
		if (input == 'i') showDeathInfo = !showDeathInfo;
		break;
	default:
		cin.get();
		break;
	}
}

void Game::Exit()
{
	
}

void Game::Draw()
{
	switch (screenIndex)
	{
	case 0:
		
		title->Draw();
		cout << "\n\n";
		cout << "\t\t====  MENU  ====------------------------------------";
		cout << "\n\n";
		cout << "\t\t \x1B[33ma\033[0m > Start a new game ";
		cout << endl;
		cout << "\t\t \x1B[33mb\033[0m > Setting ";
		cout << endl;
		cout << "\t\t \x1B[33mc\033[0m > Exit game ";
		cout << "\n\n";
		cout << "\t\t";
		
		break;
	case 1:

		title->Draw();
		cout << "\n\n";
		cout << "\t\t====  START  ====-----------------------------------";
		cout << "\n\n";
		cout << "\t\t > Enter your name: ";
		
		break;
	case 2:
		//Monster
		currentMonster->Draw();
		cout << endl;
		cout << "\t\t====  " + StringModifier::Shorten(currentMonster->name,3) + "  ====------------------------------------ [\x1B[33mm\033[0m]";

		if (showMonster)
		{
			cout << "\n\n";
			cout << "\t\t > Name: " + currentMonster->name << " (Lvl. " << currentMonster->level << ")";
			cout << "\n\n";
			cout << "\t\t > Description\n\t\t" + currentMonster->description;
		}

		cout << "\n\n";
		cout << "\t\t > Hitpoints: [";
		for (int i = 0; i < currentMonster->currentHP; i++)
		{
			cout << "\x1B[32m|\033[0m";
		}
		for (int i = 0; i < currentMonster->hitpoints - currentMonster->currentHP; i++)
		{
			cout << "\x1B[31m|\033[0m";
		}
		cout << "]";
		cout << "\n\n";
		cout << "\t\t > ATK: ";
		cout << currentMonster->baseAttack + currentMonster->attackMod;
		cout << "\t > DEF: ";
		cout << currentMonster->baseDefence + currentMonster->defenceMod;
		cout << "\t > SPD: ";
		cout << currentMonster->baseSpeed + currentMonster->speedMod;

		//Player
		cout << "\n\n";
		cout << "\t\t====  " + StringModifier::Shorten(player->name, 3) + "  ====------------------------------------ [\x1B[33mp\033[0m]";
		
		if (showPlayer)
		{
			cout << "\n\n";
			cout << "\t\t > Name: " + player->name  << " (Lvl. " << player->level << ")";
		
		}

		cout << "\n\n";
		cout << "\t\t > Hitpoints: [";
		for (int i = 0; i < player->currentHP; i++)
		{
			cout << "\x1B[32m|\033[0m";
		}
		for (int i = 0; i < player->hitpoints - player->currentHP; i++)
		{
			cout << "\x1B[31m|\033[0m";
		}
		cout << "]";
		cout << "\n\n";
		cout << "\t\t > ATK: ";
		cout << player->baseAttack + player->attackMod;
		cout << "\t > DEF: ";
		cout << player->baseDefence + player->defenceMod;
		cout << "\t > SPD: ";
		cout << player->baseSpeed + player->speedMod;
		
		if (showPlayer)
		{
			cout << "\n\n";
			cout << "\t\t > Weapon: \t";
			cout << player->weapon->name << ": " << player->weapon->description;
			cout << "\n\t\t > Armor: \t";
			cout << player->armor->name << ":" << player->armor->description;
			cout << "\n\t\t > Accessory: \t";
			cout << player->accessory->name << ": " << player->accessory->description;
		}
		
		//Action
		cout << "\n\n";
		cout << "\t\t====  ACT  ====------------------------------------ [\x1B[33ma\033[0m]";

		if (showAction)
		{
			cout << "\n\n";
			if (playerDead)
			{
				cout << "\t\t " << "\x1B[33mc\033[0m > Continue";
			}
			else if (currentMonsterDead)
			{
				cout << "\t\t " << "\x1B[33m1\033[0m > Loot";
				cout << "\n\t\t " << "\x1B[33m2\033[0m > Continue";
			}
			else
			{
				cout << "\t\t " << "\x1B[33m1\033[0m > Attack";
				cout << "\n\t\t " << "\x1B[33m2\033[0m > Escape";
			}
			cout << "\n\n\t\t";
		}

		break;
	case 97:
		currentMonster->Draw();
		cout << endl;
		cout << "\t\t====  LOOT  ====------------------------------------ [\x1B[33ml\033[0m]";
		cout << "\n\n";
		cout << "\t\t====  INV  ====------------------------------------- [\x1B[33mi\033[0m]";
		cout << "\n\n";
		cout << "\t\t \x1B[33mr\033[0m > Return";
		cout << "\n\n\t\t";
		break;
	case 98:
		title->Draw();
		cout << "\n\n";
		cout << "\t\t====  SETTING  ====---------------------------------";
		cout << "\n\n";
		cout << "\t\t \x1B[33m1\033[0m > Show detailed monster info: " << (showMonster ? "\x1B[32mTRUE\033[0m" : "FALSE");
		cout << endl;
		cout << "\t\t \x1B[33m2\033[0m > Show detailed player info: " << (showPlayer ? "\x1B[32mTRUE\033[0m" : "FALSE");
		cout << endl;
		cout << "\t\t \x1B[33m3\033[0m > Show actions: " << (showAction ? "\x1B[32mTRUE\033[0m" : "FALSE");
		cout << endl;
		cout << "\t\t \x1B[33m4\033[0m > Show death info: " << (showDeathInfo ? "\x1B[32mTRUE\033[0m" : "FALSE");
		cout << "\n\n";
		cout << "\t\t \x1B[33mr\033[0m > Return ";
		cout << "\n\n";
		cout << "\t\t";

		break;
	case 99:
		title->Draw();
		cout << "\n\n";
		cout << "\t\t====  GAMEOVER  ====--------------------------------";
		cout << "\n\n";
		cout << "\t\t \x1B[33ma\033[0m > Return to main menu";
		cout << endl;
		cout << "\t\t \x1B[33mb\033[0m > Exit game";

		cout << "\n\n";
		cout << "\t\t====  INFO  ====------------------------------------ [\x1B[33mi\033[0m]";

		if (showDeathInfo)
		{
			
			cout << "\n\n";
			cout << "\t\t > Killed by: " << killedBy;
			cout << endl;
			cout << "\t\t > Monsters killed: " << monsterKilled;
		}

		cout << "\n\n\t\t";
		break;
	default:
		cout << "ERROR";
	}
	
}

void Game::Clear()
{
	system("cls");
}


