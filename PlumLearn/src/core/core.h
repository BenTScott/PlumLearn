#pragma once

#ifdef PL_PLATFORM_WINDOWS
	#define DEBUG_BREAK __debugbreak()
#else
	#define DEBUG_BREAK
#endif

#ifdef PL_DEBUG
	#define PL_ENABLE_ASSERTS
#endif

#ifdef PL_ENABLE_ASSERTS
	#define PL_CORE_ASSERT(x, ...) { if(!(x)) { PL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUG_BREAK; } }
#else
	#define PL_CORE_ASSERT(x, ...)
#endif

#ifdef PL_INTERNAL
	#include "log.h"
#else
	#define PL_CORE_TRACE(...) 
	#define PL_CORE_INFO(...)  
	#define PL_CORE_WARN(...)  
	#define PL_CORE_ERROR(...) 
	#define PL_CORE_FATAL(...) 
#endif