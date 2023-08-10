#pragma once
#include "Object.h"
#include "Inventory.h"
#include <string>
#include <vector>
#include "Mathf.h"
class Entity : public Object
{
public:
	std::string name;

	int level;
	int hitpoints;

	int baseHP;
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
	std::string GetName();

	Equipable* weapon;
	Equipable* armor;
	Equipable* accessory;
};

