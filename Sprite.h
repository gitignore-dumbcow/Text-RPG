#include "Object.h"
#include <string>
#pragma once

class Sprite : public Object
{
public:
	Sprite(std::string _artwork)
	{
		artwork = _artwork;
	}
};

