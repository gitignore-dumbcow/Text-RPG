#include "Random.h"

int Random::Range(int min, int max)
{

	if (max - min + 1 == 0) return min;
	return rand() % (max - min + 1) + min;
}

void Random::Update()
{
	time_t t;
	srand((unsigned)time(&t));
}



