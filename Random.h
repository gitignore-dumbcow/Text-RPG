#pragma once
#include <random>
class Random
{

private:


	Random()
	{
	}
public:
	static int Range(int min, int max);

	static void Update();
};

