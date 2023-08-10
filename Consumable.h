#pragma once
#include "Item.h"

using namespace std;


class Consumable : public Item
{
public:
	Consumable(std::string _name, std::string _description, int _hpRegain) 
	{
		name = _name;

		description = " ( \033[1m\033[32m+" + to_string(_hpRegain) + "\033[0m ) ";
		description += _description;

		hpRegain = _hpRegain;

		isConsumable = true;
	}

	Consumable(const Consumable& original)
	{
		this->name = original.name;
		this->description = original.description;
		this->hpRegain = original.hpRegain;
		this->isConsumable = true;
	}
	int hpRegain = 0;
};

