#include "Random.h"

int Random::Range(int min, int max)
{

	return rand() % (max - min + 1) + min;
}
