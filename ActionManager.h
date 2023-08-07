#pragma once
#include "Entity.h"
#include "Random.h"
#include "Mathf.h"
class ActionManager
{
private:
	ActionManager() {}
public:
	static void Duel(Entity* attacker, Entity* defender);
};

