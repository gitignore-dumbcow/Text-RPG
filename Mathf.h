#pragma once
class Mathf
{
private:
	Mathf() {}
public:
	static int Clamp(int value, int min, int max);
	static float Clamp(float value, float min, float max);
};

