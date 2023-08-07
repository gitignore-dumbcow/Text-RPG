#include "Monster.h"


void Monster::Update()
{
	currentHP = Mathf::Clamp(currentHP, 0, 100000);

}
