#pragma once
#include "Object.h"
#include <string>
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

	//Method
	void Update();
};

