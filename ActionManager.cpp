#include "ActionManager.h"



void ActionManager::Duel(Entity* attacker, Entity* defender)
{

	int attackerSpeed = attacker->baseSpeed + attacker->speedMod;
	int defenderSpeed = defender->baseSpeed + defender->speedMod;
	
	int hitChance = Random::Range(0, 100);

	int speedDif = attackerSpeed - defenderSpeed;
	speedDif = Mathf::Clamp(speedDif, 1, 5);

	bool hitConfirmed = false;
	std::string hitChanceString = "50";

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

	hitChanceString = std::to_string(Mathf::Clamp(100 - (hitChance - attacker->hitChanceBooster * attacker->hitChanceBooster),0,100));
	hitChanceString = CYAN + hitChanceString + RESET;

	std::string log = "";
	std::string attackerName = YELLOW + attacker->GetName() + RESET;
	std::string defenderName = YELLOW + defender->GetName() + RESET;

	if (hitConfirmed)
	{
		int damage = attacker->baseAttack + attacker->attackMod;
		int defence = defender->baseDefence + defender->defenceMod;

		int realDamage = damage - defence;

		std::string damageString = RED + std::to_string(realDamage) + RESET;

		if (realDamage > 0)
		{
			log = attackerName + " attacked! " + defenderName + " recieved " + damageString + " damage! (" + hitChanceString + "% hit chance)";
			attacker->hitChanceBooster = 1;
			defender->currentHP = defender->currentHP - realDamage;
		}
		else
		{
			damageString = RED + std::to_string(Mathf::Clamp((int)floor((damage / 2 - defence / 3)), 1, 10000)) + RESET;
			
			if (realDamage == 0)
			{
				std::string blockChanceString = CYAN + std::to_string((int)(75 - attacker->hitChanceBooster * 0.5f)) + RESET;

				if (Random::Range(0, 100) >= 75 - attacker->hitChanceBooster * 0.5f)
				{
					log = attackerName + " tried to hit sneakily! " + defenderName + " failed to block and recieved " + damageString + " damage! (" + hitChanceString + "% hit chance, " + blockChanceString + "% block chance)";
					attacker->hitChanceBooster = 1;
					defender->currentHP -= Mathf::Clamp((int)floor((damage / 2 - defence / 3)), 1, 10000);
				}
				else
				{
					log = attackerName + " tried to hit but clashed! " + defenderName + " fenced it off completely! (" + hitChanceString + "% hit chance, " + blockChanceString + "% block chance)";
					attacker->hitChanceBooster *= 1 + speedDif;
				}
			}
			if (realDamage < 0)
			{
				std::string blockChanceString = CYAN + std::to_string((int)(75 - realDamage - attacker->hitChanceBooster * 0.5f)) + RESET;

				if (Random::Range(0, 100) >= 75 - realDamage - attacker->hitChanceBooster * 0.5f)
				{
					log = defenderName + " tried to block " + attackerName + "'s attack! But " + attackerName + " found the weak point! " + defenderName + " recieved " + damageString + " damage! (" + hitChanceString + "% hit chance, " + blockChanceString + "% block chance)";
					attacker->hitChanceBooster = 1;
					defender->currentHP -= Mathf::Clamp((int)floor((damage / 2 - defence / 3)), 1, 10000);
				}
				else
				{
					log = attackerName + " tried to deal some damage. But it was too weak! " + defenderName + " felt nothing. (" + hitChanceString + "% hit chance, " + blockChanceString + "% block chance)";

					attacker->hitChanceBooster *= 1 + speedDif;
				}

			}
		}
	}
	else
	{
		if (attackerSpeed < defenderSpeed)
		{
			log = attackerName + " attacked! But " + defenderName + " dodged it effortlessly. (" + hitChanceString + "% hit chance)";

		}
		else
		{
			log = attackerName + " striked! But missed (" + hitChanceString + "% hit chance)";

		}
		attacker->hitChanceBooster *= 1 + speedDif;
	}


	Log::AddLog(log);
}
