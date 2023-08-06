#include <string>
#include "Entity.h"

class Monster : public Entity
{
public:
	//Information
	std::string description;

	Monster(std::string _name, std::string _description, std::string _artwork, int _hitpoints, int _baseAttack, int _baseDefence, int _baseSpeed)
	{
		artwork = _artwork;

		name = _name;
		description = _description;

		hitpoints = _hitpoints;
		baseAttack = _baseAttack;
		baseDefence = _baseDefence;
		baseSpeed = _baseSpeed;

		currentHP = hitpoints;

		attackMod = 0;
		defenceMod = 0;
		speedMod = 0;
	}

	Monster(const Monster &original)
	{
		artwork = original.artwork;

		name = original.name;
		description = original.description;

		hitpoints = original.hitpoints;
		baseAttack = original.baseAttack;
		baseDefence = original.baseDefence;
		baseSpeed = original.baseSpeed;

		currentHP = hitpoints;

		attackMod = original.attackMod;
		defenceMod = original.defenceMod;
		speedMod = original.speedMod;
	}


	
};

