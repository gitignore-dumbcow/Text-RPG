#pragma once
#include <string>
class StringModifier
{
public:
	static std::string ToUpper(std::string string);
	static std::string Shorten(std::string string, int lenght);
private:
	StringModifier() {}
};

