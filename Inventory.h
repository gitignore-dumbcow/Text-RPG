#pragma once
#include "Equipable.h"
#include "Consumable.h"
#include <vector>
class Inventory
{
public:
	Inventory(int size) {}

	int inventorySize = 0;

	std::vector<Item> slots = {};

	void ChangeSize(int size);
	void AddItem(Item item);
};

