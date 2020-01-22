
#include "lit.h"

namespace
{
	// no return
	// first arg changed by reference
	void interpolate_impl(std::string& str, const std::initializer_list<const char*>& vars)
	{
		size_t i = 0;
		for (auto var : vars)
		{
			auto replacement = "{" + std::to_string(i) + "}";
			size_t loc = str.find(replacement);
			while (loc != std::string::npos)
			{
				if (loc != std::string::npos)
				{
					str.replace(str.begin() + loc, str.begin() + loc + replacement.size(), var);
				}
				loc = str.find(replacement);
			};
			i++;
		}
	}
}

void l::init(LANGUAGE language)
{
	std::unique_lock<std::mutex> l(_mtx);
	_map = new std::map<std::string, std::string>();
}

void l::close()
{
	std::unique_lock<std::mutex> l(_mtx);
	delete _map;
}

std::string l::it(const char* pStr)
{
	std::unique_lock<std::mutex> l(_mtx);
	std::string str = pStr;
	if (_map->find(pStr) != _map->end())
		str = (*_map)[str];
	return str;
}

std::string l::it(const char* pStr, std::initializer_list<const char*> vars)
{
	std::unique_lock<std::mutex> l(_mtx);
	std::string str = pStr;
	if (_map->find(pStr) != _map->end())
		str = (*_map)[pStr];
	interpolate_impl(str, vars);
	return pStr;
}

