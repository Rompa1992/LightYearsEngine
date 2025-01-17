#pragma once 
#include <string>

std::string GetResourceDir()																								// CodeExplanations->config.h: `GetResourceDir()`
{
#ifdef NDEBUG //release build
	return "assets/";
#else 
	return "C:/Users/narom/Documents/AllProjects/LearnCppGameEngine/LightYears/LightYearsGame/assets/";
#endif 

}
