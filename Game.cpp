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
		input = ' ';
		switch (screenIndex)
		{
		case 1:
			name = "";
			
			break;
		case 2:
			
			//Monster

			if (createNewMonster)
			{
				createNewMonster = false;

				if(currentMonster != nullptr) delete currentMonster;

				currentMonster = new Monster(*monsters.at(Random::Range(0, (int)monsters.size() - 1)));
			}

			if (currentMonster != nullptr)
			{
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

		player->name = name;
		screenIndex++;
		break;
	case 2:
		if (input == 'p') showPlayer = !showPlayer;
		if (input == 'm') showMonster = !showMonster;
		if (input == 'a') showAction = !showAction;

		//Actions
		if (input == '1')
		{
			if (currentMonsterDead)
			{

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

		//Monster
		if (currentMonster->currentHP == 0)
		{
			monsterKilled++;
			currentMonster->artwork = corpseArt;
		}

		//Player
		if (player->currentHP <= 0)
		{
			input = _getch();
			killedBy = currentMonster->name;
			delete currentMonster;
			screenIndex = 99;
		}
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
		cout << "\t\t a > Start A New Game ";
		cout << endl;
		cout << "\t\t b > Setting ";
		cout << endl;
		cout << "\t\t c > Exit Game ";
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
		cout << "\t\t====  " + StringModifier::Shorten(currentMonster->name,3) + "  ====------------------------------------ [m]";

		if (showMonster)
		{
			cout << "\n\n";
			cout << "\t\t > Name: " + currentMonster->name;
			cout << "\n\n";
			cout << "\t\t > Description\n\t\t" + currentMonster->description;
		}

		cout << "\n\n";
		cout << "\t\t > Hitpoints: ";
		for (int i = 0; i < currentMonster->currentHP; i++)
		{
			cout << "[] ";
		}
		for (int i = 0; i < currentMonster->hitpoints - currentMonster->currentHP; i++)
		{
			cout << "__ ";
		}
		cout << "\n\n";
		cout << "\t\t > ATK: ";
		cout << currentMonster->baseAttack + currentMonster->attackMod << "(" << currentMonster->baseAttack << ")";
		cout << "\t > DEF: ";
		cout << currentMonster->baseDefence + currentMonster->defenceMod << "(" << currentMonster->baseDefence << ")";
		cout << "\t > SPD: ";
		cout << currentMonster->baseSpeed + currentMonster->speedMod << "(" << currentMonster->baseSpeed << ")";

		//Player
		cout << "\n\n";
		cout << "\t\t====  " + StringModifier::Shorten(player->name, 3) + "  ====------------------------------------ [p]";
		
		if (showPlayer)
		{
			cout << "\n\n";
			cout << "\t\t > Name: " + player->name;
		
		}

		cout << "\n\n";
		cout << "\t\t > Hitpoints: ";
		for (int i = 0; i < player->currentHP; i++)
		{
			cout << "[] ";
		}
		for (int i = 0; i < player->hitpoints - player->currentHP; i++)
		{
			cout << "__ ";
		}
		cout << "\n\n";
		cout << "\t\t > ATK: ";
		cout << player->baseAttack + player->attackMod << "(" << player->baseAttack << ")";
		cout << "\t > DEF: ";
		cout << player->baseDefence + player->defenceMod << "(" << player->baseDefence << ")";
		cout << "\t > SPD: ";
		cout << player->baseSpeed + player->speedMod << "(" << player->baseSpeed << ")";
		
		if (showPlayer)
		{
			cout << "\n\n";
			cout << "\t\t > Weapon: \t";
			cout << "(+" << player->attackMod << ") " << player->GetWeapon();
			cout << "\n\t\t > Armor: \t";
			cout << "(+" << player->defenceMod << ") " << player->GetArmor();
			cout << "\n\t\t > Accessory: \t";
			cout << "(+" << player->speedMod << ") " << player->GetAccessory();
		}
		
		//Action
		cout << "\n\n";
		cout << "\t\t====  ACT  ====------------------------------------ [a]";

		if (showAction)
		{
			cout << "\n\n";
			cout << "\t\t " << (currentMonsterDead ? "1 > Loot" : "1 > Attack");
			cout << "\n\t\t " << (currentMonsterDead ? "2 > Continue" : "2 > Escape");
		}

		break;
	case 97:
		currentMonster->Draw();
		cout << endl;
		cout << "\t\t====  LOOT  ====------------------------------------ [l]";
		cout << "\n\n";
		cout << "\t\t====  INV  ====------------------------------------- [i]";
		break;
	case 98:
		title->Draw();
		cout << "\n\n";
		cout << "\t\t====  SETTING  ====---------------------------------";
		cout << "\n\n";
		cout << "\t\t 1 > Show detailed monster info: " << (showMonster ? "TRUE" : "FALSE");
		cout << endl;
		cout << "\t\t 2 > Show detailed player info: " << (showPlayer ? "TRUE" : "FALSE");
		cout << endl;
		cout << "\t\t 3 > Show actions: " << (showAction ? "TRUE" : "FALSE");
		cout << endl;
		cout << "\t\t 4 > Show actions: " << (showDeathInfo ? "TRUE" : "FALSE");
		cout << "\n\n";
		cout << "\t\t r > Return ";
		cout << "\n\n";
		cout << "\t\t";

		break;
	case 99:
		title->Draw();
		cout << "\n\n";
		cout << "\t\t====  GAMEOVER  ====--------------------------------";
		cout << "\n\n";
		cout << "\t\t a > Return to main menu";
		cout << endl;
		cout << "\t\t b > Exit game";

		cout << "\n\n";
		cout << "\t\t====  INFO  ====------------------------------------ [i]";

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


