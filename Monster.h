#include <string>
#include "Entity.h"
#include "Mathf.h"
#include "Random.h"
#include <vector>
#pragma once


class Monster : public Entity
{
public:
	//Information
	std::string description;
	template <typename T>
	Monster(std::string _name, std::string _description, std::string _artwork, std::vector<T*> _lootTable, int _baseHP, int _baseAttack, int _baseDefence, int _baseSpeed)
	{
		artwork = _artwork;

		name = _name;
		description = _description;

		baseHP = _baseHP;
		hitpoints = baseHP;
		baseAttack = _baseAttack;
		baseDefence = _baseDefence;
		baseSpeed = _baseSpeed;

		currentHP = baseHP;

		attackMod = 0;
		defenceMod = 0;
		speedMod = 0;

		lootTable = _lootTable;

	}

	Monster(const Monster &original)
	{
		artwork = original.artwork;

		name = original.name;
		description = original.description;

		baseHP = original.baseHP;
		baseAttack = original.baseAttack;
		baseDefence = original.baseDefence;
		baseSpeed = original.baseSpeed;

		currentHP = baseHP;

		attackMod = original.attackMod;
		defenceMod = original.defenceMod;
		speedMod = original.speedMod;

		lootTable = original.lootTable;


		if (lootTable.size() > 0)
		{
			for (int i = 0; i < Random::Range(3, 6); i++)
			{
				int index = Random::Range(0, (int)(lootTable.size() - 1));

				if (lootTable.at(index)->isConsumable) 
				{
					Consumable* item = (Consumable*)lootTable.at(index);
					Consumable* newItem = new Consumable(*item);

					inventory->AddItem(newItem);

				}
				else
				{
					Equipable* item = (Equipable*)lootTable.at(index);
					Equipable* newItem = new Equipable(*item);

					inventory->AddItem(newItem);
				}
			}
		}

	}


	Inventory* inventory = new Inventory(0);
	std::vector<Item*> lootTable;

	void Update();
	void AddSkillPoint(int currentDifficulty);
	
	int skillPointsLeft = 0;
};

