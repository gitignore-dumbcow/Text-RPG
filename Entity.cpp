#include "Entity.h"

//Methods
void Entity::Update()
{
	attackMod = weapon->atkBoost + armor->atkBoost + accessory->atkBoost;
	defenceMod = weapon->defBoost + armor->defBoost + accessory->defBoost;
	speedMod = weapon->spdBoost + armor->spdBoost + accessory->spdBoost;

	hitpoints = baseHP + weapon->hpBoost + armor->hpBoost + accessory->hpBoost;

	currentHP = Mathf::Clamp(currentHP, 0, hitpoints);
}

std::string Entity::GetName()
{
	return name;
}

