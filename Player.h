#include <string>
#include "Entity.h"
#include "Equipable.h"
#include "Consumable.h"
#include "Inventory.h"

class Player : public Entity
{
public:

	Player(Equipable* _weapon, Equipable* _armor, Equipable* _accessory)
	{
		level = 0;
		hitpoints = 5;
		baseAttack = 1;
		baseDefence = 1;
		baseSpeed = 1;

		weapon = _weapon;
		armor = _armor;
		accessory = _accessory;

		currentHP = hitpoints + weapon->hpBoost + armor->hpBoost + accessory->hpBoost;

		attackMod = 0;
		defenceMod = 0;
		speedMod = 0;

	}

	Inventory* inventory = new Inventory(8);

	Equipable* weapon;
	Equipable* armor;
	Equipable* accessory;

	bool isHPmaxed = true;

	void Update();
};

