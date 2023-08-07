#pragma once
#include "Object.h"
#include "Inventory.h"
#include <string>
#include <vector>
class Entity : public Object
{
public:
	std::string name;

	int level;
	int hitpoints;

	int baseAttack;
	int baseDefence;
	int baseSpeed;

	int currentHP;

	int attackMod;
	int defenceMod;
	int speedMod;

	int hitChanceBooster = 1;

	//Method
	void Update();

	Inventory* inventory = new Inventory(0);
};

