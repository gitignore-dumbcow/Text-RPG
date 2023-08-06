#pragma once
#include "Entity.h"
#include "Random.h"
class ActionManager
{
private:
	ActionManager() {}
public:
	static void Duel(Entity* attacker, Entity* defender);
};

