#pragma once
#include <random>
class Random
{

private:
	static time_t t;

	Random()
	{
		srand((unsigned)time(&t));
	}
public:
	static int Range(int min, int max);

	
};

