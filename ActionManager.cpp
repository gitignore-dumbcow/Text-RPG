#include "ActionManager.h"

void ActionManager::Duel(Entity* attacker, Entity* defender)
{
	int attackerSpeed = attacker->baseSpeed + attacker->speedMod;
	int defenderSpeed = defender->baseSpeed + defender->speedMod;
	
	int hitChance = Random::Range(0, 100);

	float hitRatio = (float)(attackerSpeed / defenderSpeed);

	bool hitConfirmed = false;

	if (hitRatio == 1)
	{
		if (hitChance <= 50)
		{
			hitConfirmed = true;
		}
	}
	if (hitRatio > 1)
	{
		if (hitChance <= 50 + hitRatio * hitRatio)
		{
			hitConfirmed = true;
		}
	}
	if (hitRatio < 1)
	{
		if (hitChance <= 50 - hitRatio * hitRatio)
		{
			hitConfirmed = true;
		}
	}

	if (hitConfirmed)
	{
		int damage = attacker->baseAttack + attacker->attackMod;
		int defence = defender->baseDefence + defender->defenceMod;

		int realDamage = damage - defence;

		if (realDamage > 0)
		{
			defender->currentHP = defender->currentHP - realDamage;
		}
	}

}
