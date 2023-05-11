#pragma once

#ifdef ORBIT_BUILD_DLL
	#define ORBIT_API __declspec(dllexport)
#else
	#define ORBIT_API __declspec(dllimport)
#endif