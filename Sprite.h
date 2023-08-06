#include "Object.h"
#include <string>
class Sprite : public Object
{
public:
	Sprite(std::string _artwork)
	{
		artwork = _artwork;
	}
};

