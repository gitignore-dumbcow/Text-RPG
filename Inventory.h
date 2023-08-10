#pragma once
#include "Equipable.h"
#include "Consumable.h"
#include <vector>


class Inventory
{
public:
	Inventory(int size) 
	{
		inventorySize = size;
	}

	std::vector<Consumable*> consumableSlots = {};
	std::vector<Equipable*> equipableSlots= {};

	int inventorySize = 0;

	void ChangeSize(int size);
	void AddItem(Consumable* item);
	void AddItem(Equipable* item);
	void RemoveEquipable(int index);
	void RemoveConsumable(int index);
	
	int getTotalSlots();

};

