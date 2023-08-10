#pragma once
#include "Item.h"
enum EquipType 
{
	Weapon,
	Armor,
	Accessory
};

using namespace std;

class Equipable : public Item
{
public:
	Equipable(std::string _name, std::string _description, int _hpBoost, int _atkBoost, int _defBoost, int _spdBoost, EquipType _type)
	{
		name = _name;

		description = " (";
		
		if (_hpBoost != 0) description += GREEN " " + to_string(_hpBoost) + RESET;
		if (_atkBoost != 0) description += RED " " + to_string(_atkBoost) + RESET;
		if (_defBoost != 0) description += CYAN " " + to_string(_defBoost) + RESET;
		if (_spdBoost != 0) description += YELLOW " " + to_string(_spdBoost) + RESET;

		description += " ) ";
		description += _description;

		hpBoost = _hpBoost;
		atkBoost = _atkBoost;
		defBoost = _defBoost;
		spdBoost = _spdBoost;

		type = _type;
	}

	Equipable(const Equipable &original)
	{
		this->name = original.name;
		this->description = original.description;

		this->hpBoost = original.hpBoost;
		this->atkBoost = original.atkBoost;
		this->defBoost = original.defBoost;
		this->spdBoost = original.spdBoost;

		this->type = original.type;
	}

	int hpBoost = 0;
	int atkBoost = 0;
	int defBoost = 0;
	int spdBoost = 0;

	EquipType type;
};

