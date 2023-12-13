#pragma once

#include <cstdint>
#include <memory>

#if defined(PLATFORM_WEB)
	#define KEEP_IN_MODULE extern "C" __attribute__((used, visibility("default")))
#endif

#ifdef CONFIG_DEBUG
	#if defined(PLATFORM_WEB)
		#define DEBUGBREAK()
	#elif defined(PLATFORM_WINDOWS)
		#define DEBUGBREAK() __debugbreak()
	#elif defined(PLATFORM_LINUX)
		#include <signal.h>
		#define DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define ENABLE_ASSERTS
#else
	#define DEBUGBREAK()
#endif

#define EXPAND_MACRO(x) x
#define STRINGIFY_MACRO(x) #x

#include "Base/Assert.h"
#include "Base/Log.h"
