#pragma once

#ifdef VOS_PLATFORM_WINDOWS
	#ifdef VOS_BUILD_DLL
		#define VOS_API __declspec(dllexport)
	#else 
		#define VOS_API __declspec(dllimport)
	#endif // VOS_BUILD_DLL
#endif // VOS_PLATFORM_WINDOWS

#define BIT(x) (1 << x) //shift 1 by x places
