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
			currentDifficulty = 1;

			name = "";

			if (player != nullptr)
			{
				delete player;

			}

			player = new Player(
				starter[0].at(Random::Range(0, (int)starter[0].size() - 1)),
				starter[1].at(Random::Range(0, (int)starter[1].size() - 1)),
				starter[2].at(Random::Range(0, (int)starter[2].size() - 1))
			);
			
			if (player->weapon != fist) player->inventory->AddItem(player->weapon);
			if (player->armor != naked) player->inventory->AddItem(player->armor);
			if (player->accessory != none) player->inventory->AddItem(player->accessory);

			player->weapon->active = true;
			player->armor->active = true;
			player->accessory->active = true;
			
			Log::AddLog("Welcome to Text RPG!");
			Log::AddLog("You have to slay the boss to achieve victory.");
			Log::AddLog("If you cannot fight, consider dodging, but the game will only get harder.");
			//Log::AddLog("Your adventure starts here!");
			Log::AddLog("Good luck!");

			break;
		case 2:
			
			//Player
			player->Update();

			if (player != nullptr)
			{
				playerDead = player->currentHP <= 0;

				if (isAdmin)
				{
					player->Admin();
				}
			}

			//Monster

			if (createNewMonster)
			{
				createNewMonster = false;

				if(currentMonster != nullptr) delete currentMonster;

				if (currentDifficulty >= 12)
				{
					currentMonster = new Monster(*boss);
				}
				else
				{
					if (currentDifficulty > 9)
					{
						int index = Random::Range(0, (int)tier5monsters.size() - 1);
						currentMonster = new Monster(*tier5monsters.at(index));
						tier5monsters.erase(tier5monsters.begin() + index);
						
					}
					else if (currentDifficulty > 6)
					{
						int index = Random::Range(0, (int)tier4monsters.size() - 1);
						currentMonster = new Monster(*tier4monsters.at(index));
						tier4monsters.erase(tier4monsters.begin() + index);
						
					}
					else if (currentDifficulty > 4)
					{
						int index = Random::Range(0, (int)tier3monsters.size() - 1);
						currentMonster = new Monster(*tier3monsters.at(index));
						tier3monsters.erase(tier3monsters.begin() + index);
						
					}
					else if (currentDifficulty > 2)
					{
						int index = Random::Range(0, (int)tier2monsters.size() - 1);
						currentMonster = new Monster(*tier2monsters.at(index));
						tier2monsters.erase(tier2monsters.begin() + index);
						
					}
					else if (currentDifficulty > 0)
					{
						int index = Random::Range(0, (int)tier1monsters.size() - 1);
						currentMonster = new Monster(*tier1monsters.at(index));
						tier1monsters.erase(tier1monsters.begin() + index);
						
					}
				}
				
				currentMonster->AddSkillPoint(currentDifficulty);
				currentMonster->currentHP = currentMonster->baseHP;

				std::string log = "";

				if (currentMonster->name == "LORD VRAXX")
				{
					log = "You've reached your destination, " YELLOW + currentMonster->name + RESET + "!";

				}
				else
				{
					log = "A wild " YELLOW + currentMonster->name + RESET + " and blocked your way!";

				}
				Log::AddLog("Combat: ");
				Log::AddLog(log);
				
			}

			if (currentMonster != nullptr)
			{
				currentMonster->Update();

				currentMonsterDead = currentMonster->currentHP == 0;

			}



			break;
		case 97:
			player->Update();
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
		if (input == 'i') showInventory = !showInventory;
		if (input == 'l') showLog = !showLog;

		//Actions
		if (!playerDead)
		{
			if (showInventory)
			{
				ConfigEquipable();
				ConfigConsumable();
			}
			else
			{
				if (input == '1')
				{
					if (currentMonsterDead)
					{
						showInventory = true;
						screenIndex = 97;
						mode = 0;
					}
					else
					{
						ActionManager::Duel(player, currentMonster);
						if (currentMonster->currentHP != 0)
						{
							ActionManager::Duel(currentMonster, player);
						}
						else
						{
							std::string log = YELLOW + currentMonster->GetName() + RESET + " dies!";
							Log::AddLog(log);
						}

					}


				}
				if (input == '2')
				{
					NextFight();
					break;
				}
			}
			
		}
		else
		{
			if (input == 'c')
			{
				screenIndex = 99;
				if (currentMonster != nullptr)
				{
					Log::AddLog("");
					std::string log = YELLOW + player->GetName() + RESET + " dies!";
					Log::AddLog(log);
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
				currentMonster->artwork = corpseArt;
			}
		}

		break;
	case 96:
		if (input == '1')
		{
			player->baseHP += 1;
			player->currentHP += 1;
		}
		else if (input == '2') player->baseAttack++;
		else if (input == '3') player->baseDefence++;
		else if (input == '4') player->baseSpeed++;

		screenIndex = 2;

		break;
	case 97:
		if (input == 'r')
		{
			showInventory = false;
			screenIndex = 2;
		}
		if (input == 'c')
		{
			showInventory = false;
			NextFight();
			break;
		}
		if (input == 'l') showLoot = !showLoot;
		if (input == 'i') showInventory = !showInventory;
		if (input == 'p') showPlayer = !showPlayer;
		if (input == 'a') showAction = !showAction;
		if (input == 'm')
		{
			mode++;
			if (mode == 3) mode = 0;
		}

		switch (mode)
		{
		case 0:
			//Loot

			if (player->inventory->getTotalSlots() < player->inventory->inventorySize)
			{
				for (int i = 0; i < currentMonster->inventory->equipableSlots.size(); i++)
				{
					Equipable* currrentItem = currentMonster->inventory->equipableSlots.at(i);

					if (input == std::to_string(i)[0])
					{
						player->inventory->AddItem(currrentItem);
						currentMonster->inventory->RemoveEquipable(i);
						goto exitLoot;
					}
				}

				for (int i = 0; i < currentMonster->inventory->consumableSlots.size(); i++)
				{
					Consumable* currrentItem = currentMonster->inventory->consumableSlots.at(i);

					if (input == std::to_string(currentMonster->inventory->equipableSlots.size() + i)[0])
					{
						player->inventory->AddItem(currrentItem);
						currentMonster->inventory->RemoveConsumable(i);
					}
				}

			}
			exitLoot:
			break;
		
		case 1:
			//Use
			ConfigEquipable();
			ConfigConsumable();

			break;
		case 2:
			//Discard

			for (int i = 0; i < player->inventory->equipableSlots.size(); i++)
			{
				Equipable* currrentItem = player->inventory->equipableSlots.at(i);

				if (input == std::to_string(i)[0])
				{
					if (currrentItem->active) break;
					currentMonster->inventory->AddItem(currrentItem);
					player->inventory->RemoveEquipable(i);
					goto exitDiscard;
				}
			}

			for (int i = 0; i < player->inventory->consumableSlots.size(); i++)
			{
				Consumable* currrentItem = player->inventory->consumableSlots.at(i);

				if (input == std::to_string(player->inventory->equipableSlots.size() + i)[0])
				{
					currentMonster->inventory->AddItem(currrentItem);
					player->inventory->RemoveConsumable(i);
				}
			}

		exitDiscard:
			break;
		}
		

		break;
	case 98:
		if (input == '1') showMonster = !showMonster;
		if (input == '2') showPlayer = !showPlayer;
		if (input == '3') showAction = !showAction;
		if (input == '4') showDeathInfo = !showDeathInfo;
		if (input == '5') showLoot = !showLoot;
		if (input == '6') showInventory = !showInventory;
		if (input == '7') showLog = !showLog;
		if (input == 'r') screenIndex = 0;
		break;
	case 95:
		if (input == 'a') screenIndex = 0;
		if (input == 'b') gameRunning = false;
		if (input == 'i') showDeathInfo = !showDeathInfo;
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
		
		DrawMenu();		
		break;
	case 1:

		DrawStart();		
		break;
	case 2:
		//Monster
		DrawMonster();
		cout << "\n\n";
		DrawLog();
		//Player
		cout << "\n";
		DrawPlayer();
		cout << "\n\n";
		DrawInventory();
		
		//Action
		DrawCombatAct();
		cout << "\n\n\t\t";

		break;
	case 95:
		DrawWin();
		break;
	case 96:
		
		DrawStats();
		break;
	case 97:
		currentMonster->Draw();
		cout << endl;
		DrawLoot();
		
		//Player
		cout << "\n";
		DrawPlayer();

		//Inventory
		cout << "\n\n";
		DrawInventory();
		DrawLootAct();

		
		cout << "\n\n\t\t";
		break;
	case 98:
		DrawSetting();

		break;
	case 99:
		DrawDeath();
		break;
	default:
		cout << "ERROR";
	}
	
}

void Game::Clear()
{
	system("cls");
}

void Game::NextFight()
{
	currentDifficulty += 1 * difficultyMultiplier;
	if (currentMonsterDead)
	{
		if (currentDifficulty >= 13)
		{
			screenIndex = 95;
		}
		else
		{
			screenIndex = 96;
		}
		monsterKilled++;
		player->level++;
		
	}


	delete currentMonster;
	currentMonster = nullptr;
	createNewMonster = true;
}

void Game::ConfigEquipable()
{
	for (int i = 0; i < player->inventory->equipableSlots.size(); i++)
	{
		Equipable* currrentItem = player->inventory->equipableSlots.at(i);


		if (input == std::to_string(i)[0])
		{
			if (currrentItem->active)
			{
				currrentItem->active = false;
				switch (currrentItem->type)
				{
				case Weapon:
				{

					player->weapon = fist;
					break;
				}
				case Armor:
				{
					player->armor = naked;
					break;
				}
				case Accessory:
				{
					player->accessory = none;
					break;
				}
				}
			}
			else
			{
				switch (currrentItem->type)
				{
				case Weapon:
				{
					Equipable* oldWeapon = player->weapon;
					oldWeapon->active = false;
					player->weapon = currrentItem;
					player->weapon->active = true;
					break;
				}
				case Armor:
				{
					Equipable* oldArmor = player->armor;
					oldArmor->active = false;
					player->armor = currrentItem;
					player->armor->active = true;
					break;
				}
				case Accessory:
				{
					Equipable* oldAccessory = player->accessory;
					oldAccessory->active = false;
					player->accessory = currrentItem;
					player->accessory->active = true;
					break;
				}
				}
			}
		}
	}
}

void Game::ConfigConsumable()
{
	for (int i = 0; i < player->inventory->consumableSlots.size(); i++)
	{
		Consumable* currrentItem = player->inventory->consumableSlots.at(i);

		if (input == std::to_string((int)(player->inventory->equipableSlots.size() + i))[0])
		{
			player->currentHP += currrentItem->hpRegain;
			player->inventory->RemoveConsumable(i);
		}
	}
}

void Game::DrawMenu()
{
	title->Draw();
	cout << "\n\n";
	cout << "\t\t====  MENU  ====------------------------------------";
	cout << "\n\n";
	cout << "\t\t \x1B[33ma\033[0m > Start a new game";
	cout << endl;
	cout << "\t\t \x1B[33mb\033[0m > Setting";
	cout << endl;
	cout << "\t\t \x1B[33mc\033[0m > Exit game";
	cout << "\n\n";
	cout << "\t\t";
}

void Game::DrawStart()
{
	title->Draw();
	cout << "\n\n";
	cout << "\t\t====  START  ====-----------------------------------";
	cout << "\n\n";
	cout << "\t\t > Enter your name: ";
}

void Game::DrawSetting()
{
	title->Draw();
	cout << "\n\n";
	cout << "\t\t====  SETTING  ====---------------------------------";
	cout << "\n\n";
	
	cout << "\t\t \x1B[33m1\033[0m > Show detailed monster info: " << (showMonster ? "\x1B[32mTRUE\033[0m" : "FALSE");
	cout << endl;
	cout << "\t\t \x1B[33m2\033[0m > Show detailed player info: " << (showPlayer ? "\x1B[32mTRUE\033[0m" : "FALSE");
	cout << endl;
	cout << "\t\t \x1B[33m3\033[0m > Show action: " << (showAction ? "\x1B[32mTRUE\033[0m" : "FALSE");
	cout << endl;
	cout << "\t\t \x1B[33m4\033[0m > Show loot: " << (showLoot ? "\x1B[32mTRUE\033[0m" : "FALSE");
	cout << endl;
	cout << "\t\t \x1B[33m5\033[0m > Show inventory: " << (showInventory ? "\x1B[32mTRUE\033[0m" : "FALSE");
	
	cout << endl;
	cout << "\t\t \x1B[33m6\033[0m > Show death info: " << (showDeathInfo ? "\x1B[32mTRUE\033[0m" : "FALSE");
	cout << endl;
	cout << "\t\t \x1B[33m7\033[0m > Show detailed log: " << (showLog ? "\x1B[32mTRUE\033[0m" : "FALSE");
	
	cout << "\n\n";
	cout << "\t\t \x1B[33mr\033[0m > Return ";
	cout << "\n\n";
	cout << "\t\t";
}

void Game::DrawDeath()
{
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
}

void Game::DrawStats()
{
	title->Draw();
	cout << "\n\n";
	cout << "\t\t====  STATS  ====-----------------------------------";
	cout << "\n\n";
	cout << "\t\t Level up! Spend your skill point!";
	cout << "\n\n";
	cout << "\t\t \x1B[33m1\033[0m > HP: \t" << player->hitpoints << " -> " << player->hitpoints + 1;
	cout << endl;
	cout << "\t\t \x1B[33m2\033[0m > ATK: \t" << player->baseAttack + player->attackMod << " -> " << player->baseAttack + player->attackMod + 1;
	cout << endl;
	cout << "\t\t \x1B[33m3\033[0m > DEF: \t" << player->baseDefence + player->defenceMod << " -> " << player->baseDefence + player->defenceMod + 1;
	cout << endl;
	cout << "\t\t \x1B[33m4\033[0m > SPD: \t" << player->baseSpeed + player->speedMod << " -> " << player->baseSpeed + player->speedMod + 1;
	cout << "\n\n\t\t";
}

void Game::DrawWin()
{
	title->Draw();
	cout << "\n\n";
	cout << "\t\t====  WIN  ====--------------------------------";
	cout << "\n\n";
	cout << "\t\t \x1B[33ma\033[0m > Return to main menu";
	cout << endl;
	cout << "\t\t \x1B[33mb\033[0m > Exit game";

	cout << "\n\n";
	cout << "\t\t====  INFO  ====------------------------------------ [\x1B[33mi\033[0m]";

	if (showDeathInfo)
	{

		cout << "\n\n";
		cout << "\t\t > Killed by: NONE!";
		cout << endl;
		cout << "\t\t > Monsters killed: " << monsterKilled;
	}

	cout << "\n\n\t\t";
}

void Game::DrawCombatAct()
{
	cout << "\t\t====  ACT  ====-------------------------------------- [\x1B[33ma\033[0m]";

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
	}
}

void Game::DrawLootAct()
{
	cout << "\t\t====  ACT  ====-------------------------------------- [\x1B[33ma\033[0m]";
	if (showAction)
	{
		cout << "\n\n\t\t \x1B[33mm\033[0m > Change Mode: ";
		switch (mode)
		{
		case 0:
			cout << "\x1B[33mLoot\033[0m";
			break;
		case 1:
			cout << "\x1B[33mUse\033[0m";
			break;
		case 2:
			cout << "\x1B[33mDiscard\033[0m";
			break;
		default:
			break;
		}
		cout << "\n\t\t \x1B[33mr\033[0m > Return";
		cout << "\n\t\t \x1B[33mc\033[0m > Continue";
	}
}

void Game::DrawPlayer()
{
	cout << "\t\t====  " + StringModifier::Shorten(player->name, 3) + "  ====-------------------------------------- [\x1B[33mp\033[0m]";

	if (showPlayer)
	{
		cout << "\n\n";
		cout << "\t\t > Name: " + player->name << " (Lvl. " << player->level << ")";

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
	cout << RED << player->baseAttack + player->attackMod << RESET;
	cout << "\t > DEF: ";
	cout << CYAN << player->baseDefence + player->defenceMod << RESET;
	cout << "\t > SPD: ";
	cout << YELLOW << player->baseSpeed + player->speedMod << RESET;

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
}

void Game::DrawMonster()
{
	currentMonster->Draw();
	cout << endl;
	cout << "\t\t====  " + StringModifier::Shorten(currentMonster->name, 3) + "  ====-------------------------------------- [\x1B[33mm\033[0m]";

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
	cout << RED << currentMonster->baseAttack + currentMonster->attackMod << RESET;
	cout << "\t > DEF: ";
	cout << CYAN << currentMonster->baseDefence + currentMonster->defenceMod << RESET;
	cout << "\t > SPD: ";
	cout << YELLOW << currentMonster->baseSpeed + currentMonster->speedMod << RESET;
}

void Game::DrawLoot()
{
	cout << "\t\t====  LOOT  ====-------------------------------------- [\x1B[33ml\033[0m]";
	cout << "\n\n";
	if (showLoot)
	{
		//Displaying Items
		cout << "\t\tEquipable: \n\n";
		for (int i = 0; i < currentMonster->inventory->equipableSlots.size(); i++)
		{
			Equipable* currentItem = currentMonster->inventory->equipableSlots.at(i);

			cout << "\t\t ";
			printf("%d", i);

			cout << " > " << currentItem->name << ": " << currentItem->description << endl;
		}
		cout << "\n\t\tConsumable: \n\n";
		for (int i = 0; i < currentMonster->inventory->consumableSlots.size(); i++)
		{
			Consumable* currentItem = currentMonster->inventory->consumableSlots.at(i);

			cout << "\t\t ";
			printf("%d", (int)(currentMonster->inventory->equipableSlots.size() + i));

			cout << " > " << currentItem->name << ": " << currentItem->description << endl;
		}
	}
}

void Game::DrawInventory()
{
	cout << "\t\t====  INV  ====-------------------------------------- [\x1B[33mi\033[0m]";
	cout << "\n\n";
	cout << "\t\t > Slots: " << player->inventory->getTotalSlots() << "/" << player->inventory->inventorySize;
	cout << "\n\n";
	if (showInventory)
	{
		
		//Displaying Items
		
		cout << "\t\tEquipable: \n\n";
		for (int i = 0; i < player->inventory->equipableSlots.size(); i++)
		{
			Equipable* currentItem = player->inventory->equipableSlots[i];

			if (currentItem != nullptr)
			{
				cout << "\t\t ";
				if (currentItem->active)
				{
					printf("\x1B[32m%d\033[0m", i);
				}
				else
				{
					printf("%d", i);
				}


				cout << " > " << currentItem->name << ": " << currentItem->description << endl;
			}
		}
		cout << "\n\t\tConsumable:";
		cout << "\n\n";
		for (int i = 0; i < player->inventory->consumableSlots.size(); i++)
		{
			
			
			Consumable* currentItem = player->inventory->consumableSlots[i];

			if (currentItem != nullptr)
			{
				cout << "\t\t ";
				if (currentItem->active)
				{
					printf("\x1B[32m%d\033[0m", (int)(player->inventory->equipableSlots.size() + i));
				}
				else
				{
					printf("%d", (int)(player->inventory->equipableSlots.size() + i));
				}


				cout << " > " << currentItem->name << ": " << currentItem->description << endl;
			}

			
		}

		if (player->inventory->consumableSlots.size() > 0)
		{
			cout << "\n";
		}
		
	}

	
}

void Game::DrawLog()
{
	cout << "\t\t====  LOG  ====-------------------------------------- [\x1B[33ml\033[0m]";


	if (showLog)
	{
		cout << "\n";
		for (int i = 5; i >= 0; i--)
		{
			cout << "\t\t" << Log::GetLog(i) << endl;
		}
	}
	else
	{
		cout << "\n\n";
		for (int i = 1; i >= 0; i--)
		{
			cout << "\t\t" << Log::GetLog(i) << endl;
		}
	}


}


