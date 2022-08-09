#pragma once

#ifdef VOS_PLATFORM_WINDOWS
	#ifdef VOS_BUILD_DLL
		#define VOS_API __declspec(dllexport)
	#else 
		#define VOS_API __declspec(dllimport)
	#endif // VOS_BUILD_DLL
#endif // VOS_PLATFORM_WINDOWS

#ifdef VOS_ENABLE_ASSERTS
	#define VOS_ASSERT(x, ...) {if(!(x)) { VOS_ERROR("Asserion Failed: {0}", __VA_ARGS__); __debugbreak()};}
	#define VOS_CORE_ASSERT(x, ...) {if(!(x)) { VOS_CORE_ERROR("Asserion Failed: {0}", __VA_ARGS__); __debugbreak()};}
#else
	#define VOS_ASSERT(x, ...)
	#define VOS_CORE_ASSERT(x, ...)
#endif // VOS_ENABLE_ASSERTS


#define BIT(x) (1 << x) //shift 1 by x places
