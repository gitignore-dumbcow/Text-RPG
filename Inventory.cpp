#include "Inventory.h"

void Inventory::ChangeSize(int size)
{
	inventorySize += size;
}

void Inventory::AddItem(Consumable* item)
{
	consumableSlots.push_back(item);
	
}

void Inventory::AddItem(Equipable* item)
{
	equipableSlots.push_back(item);
}

void Inventory::RemoveEquipable(int index)
{
	equipableSlots.erase(equipableSlots.begin() + index);
}

void Inventory::RemoveConsumable(int index)
{
	consumableSlots.erase(consumableSlots.begin() + index);
}

int Inventory::getTotalSlots()
{
	return (int)(consumableSlots.size() + equipableSlots.size());
}
