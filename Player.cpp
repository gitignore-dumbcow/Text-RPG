#include "Player.h"

void Player::Update()
{
	attackMod = weapon->atkBoost + armor->atkBoost + accessory->atkBoost;
	defenceMod = weapon->defBoost + armor->defBoost + accessory->defBoost;
	speedMod = weapon->spdBoost + armor->spdBoost + accessory->spdBoost;

	hitpoints = 5 + weapon->hpBoost + armor->hpBoost + accessory->hpBoost;

}

