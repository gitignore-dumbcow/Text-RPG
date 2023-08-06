#include <string>
#include "Entity.h"

class Player : public Entity
{
public:
	Player()
	{
		level = 1;
		hitpoints = 10;
		baseAttack = 1;
		baseDefence = 0;
		baseSpeed = 1;

		_weapon = "Fist";
		_armor = "T-shirt";
		_accessory = "Ring of Haste";

		currentHP = hitpoints;

		attackMod = 0;
		defenceMod = 0;
		speedMod = 1;
	}

	//Getters

	std::string GetWeapon();
	std::string GetArmor();
	std::string GetAccessory();

	//Setters

	void SetWeapon(std::string weapon);
	void SetArmor(std::string armor);
	void SetAccessory(std::string accessory);



private:
	std::string _weapon;
	std::string _armor;
	std::string _accessory;
};

