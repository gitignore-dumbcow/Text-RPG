#pragma once
#include "Item.h"
class Consumable : public Item
{
public:
	Consumable(std::string _name, std::string _description, int _hpRegain) 
	{
		name = _name;
		description = _description;

		hpRegain = _hpRegain;
	}

	Consumable(const Consumable& original)
	{
		this->name = original.name;
		this->description = original.description;
		this->hpRegain = original.hpRegain;
	}
	int hpRegain = 0;
};

