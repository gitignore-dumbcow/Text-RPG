#include "Inventory.h"

void Inventory::ChangeSize(int size)
{
	inventorySize += size;
}

void Inventory::AddItem(Item item)
{
	slots.push_back(item);
}
