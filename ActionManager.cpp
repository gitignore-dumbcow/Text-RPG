#include "ActionManager.h"

void ActionManager::Duel(Entity* attacker, Entity* defender)
{
	int attackerSpeed = attacker->baseSpeed + attacker->speedMod;
	int defenderSpeed = defender->baseSpeed + defender->speedMod;
	
	int hitChance = Random::Range(0, 100);

	int speedDif = attackerSpeed - defenderSpeed;
	speedDif = Mathf::Clamp(speedDif, 1, 5);

	bool hitConfirmed = false;

	if (defenderSpeed == attackerSpeed)
	{
		if (hitChance - attacker->hitChanceBooster * attacker->hitChanceBooster <= 50)
		{
			hitConfirmed = true;
		}
	}
	if (defenderSpeed < attackerSpeed)
	{
		if (hitChance - attacker->hitChanceBooster * attacker->hitChanceBooster <= 50 + 5 * speedDif)
		{
			hitConfirmed = true;
		}
	}
	if (defenderSpeed > attackerSpeed)
	{
		if (hitChance - attacker->hitChanceBooster * attacker->hitChanceBooster <= 50 - 5 * (5 - speedDif))
		{
			hitConfirmed = true;
		}
	}


	if (hitConfirmed)
	{
		attacker->hitChanceBooster = 1;

		int damage = attacker->baseAttack + attacker->attackMod;
		int defence = defender->baseDefence + defender->defenceMod;

		int realDamage = damage - defence;

		if (realDamage > 0)
		{
			defender->currentHP = defender->currentHP - realDamage;
		}
		else
		{
			if (realDamage == 0)
			{
				if (Random::Range(0, 100) >= 50)
				{
					defender->currentHP -= 1;
				}
			}
			if (realDamage < 0)
			{

			}
		}
	}
	else
	{
		attacker->hitChanceBooster *= 1 + speedDif;
	}

}
