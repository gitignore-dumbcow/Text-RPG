#include "StringModifier.h"

std::string StringModifier::ToUpper(std::string string)
{
	int i = 0;
	char c;

	while (string[i])
	{
		c = string[i];
		string[i] = toupper(c);
		i++;
	}

	return string;
}

std::string StringModifier::Shorten(std::string string, int lenght)
{
	int i = 0;
	char c = ' ';
	std::string out = "";
	
	if (string.length() > lenght)
	{
		for (int i = 0; i < lenght; i++)
		{
			out += string[i];
		}
	}
	else
	{
		for (int i = 0; i < string.length(); i++)
		{
			out += string[i];
		}
		for (int i = 0; i < lenght - string.length(); i++)
		{
			out += string[string.length() - 1];
		}
	}


	return out;
}
