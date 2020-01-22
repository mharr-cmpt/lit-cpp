#pragma once

#include <string>
#include <map>
#include <mutex>

#define LANGUAGE int
#define en 0x100

class l
{
public:

	// initialize the translation map
	// if uninitialized, interpolations rely on input string
	static void init(LANGUAGE language);

	// clean up
	static void close();
	
	// calls translate and interpolate the input string
	// as per initialized strings
	static std::string it(const char* pStr);
	static std::string it(const char* pStr, std::initializer_list<const char*> args);
	
private:
	l() {}
	virtual ~l() {}

	static std::mutex _mtx;
	static std::map<std::string, std::string>* _map = nullptr;
};
