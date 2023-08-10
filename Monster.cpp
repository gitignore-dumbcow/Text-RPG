#include "Monster.h"


void Monster::Update()
{
	hitpoints = baseHP;
	currentHP = Mathf::Clamp(currentHP, 0, hitpoints);
}

void Monster::AddSkillPoint(int currentDifficulty)
{
	level = Mathf::Clamp(Random::Range(currentDifficulty - 1, currentDifficulty + 1),0,currentDifficulty+1);
	skillPointsLeft = level;

	while (skillPointsLeft - 1 > 0)
	{

		int value;

		if (skillPointsLeft % 10 == 0)
		{
			value = 10;
		}
		else if (skillPointsLeft % 5 == 0)
		{
			value = 5;
		}
		else if (skillPointsLeft % 2 == 0)
		{
			value = 2;
		}
		else
		{
			value = 1;
		}


		switch (Random::Range(0, 3))
		{
		case 0:
			baseHP += value;
			break;
		case 1:
			baseAttack += value;
			break;
		case 2:
			baseDefence += value;
			break;
		case 3:
			baseSpeed += value;
			break;
		}


		skillPointsLeft -= value;
	}
}

