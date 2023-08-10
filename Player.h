#include <string>
#include "Entity.h"
#include "Equipable.h"
#include "Consumable.h"
#include "Inventory.h"
#pragma once


class Player : public Entity
{
public:

	Player(Equipable* _weapon, Equipable* _armor, Equipable* _accessory)
	{
		level = 1;
		baseHP = 10;
		baseAttack = 1;
		baseDefence = 1;
		baseSpeed = 1;

		weapon = _weapon;
		armor = _armor;
		accessory = _accessory;

		currentHP = baseHP + weapon->hpBoost + armor->hpBoost + accessory->hpBoost;

		attackMod = 0;
		defenceMod = 0;
		speedMod = 0;

		inventory = new Inventory(8);
	}

	Inventory* inventory;

	void Admin();
};

