#pragma once
#include "Item.h"
class Equipable : public Item
{
public:
	Equipable(std::string _name, std::string _description, int _hpBoost, int _atkBoost, int _defBoost, int _spdBoost)
	{
		name = _name;
		description = _description;

		hpBoost = _hpBoost;
		atkBoost = _atkBoost;
		defBoost = _defBoost;
		spdBoost = _spdBoost;
	}

	Equipable(const Equipable &original)
	{
		this->name = original.name;
		this->description = original.description;

		this->hpBoost = original.hpBoost;
		this->atkBoost = original.atkBoost;
		this->defBoost = original.defBoost;
		this->spdBoost = original.spdBoost;
	}

	int hpBoost = 0;
	int atkBoost = 0;
	int defBoost = 0;
	int spdBoost = 0;
};

