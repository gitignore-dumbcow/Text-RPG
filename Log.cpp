#include "Log.h"

std::string Log::log[];

void Log::AddLog(std::string _log)
{
	for (int i = 4; i >= 0; i--)
	{
		if (i == 0)
		{
			log[i] = _log;
			break;
		}
		log[i] = log[i - 1];


		//log[i] = _log;
	}
}

std::string Log::GetLog(int index)
{
	return log[index].c_str();
}
