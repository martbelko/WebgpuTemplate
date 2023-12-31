#pragma once

#include "Base.h"
#include "Log.h"

#include "Base/Filesystem.h"

#ifdef ENABLE_ASSERTS
	#define INTERNAL_ASSERT_IMPL(check, msg, ...) { if(!(check)) { ERROR(msg, __VA_ARGS__); DEBUGBREAK(); } }
	#define INTERNAL_ASSERT_WITH_MSG(check, ...) INTERNAL_ASSERT_IMPL(check, "Assertion failed: {0}", __VA_ARGS__)
	#define INTERNAL_ASSERT_NO_MSG(check) INTERNAL_ASSERT_IMPL(check, "Assertion '{0}' failed at {1}:{2}", STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define INTERNAL_ASSERT_GET_MACRO(...) EXPAND_MACRO( INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, INTERNAL_ASSERT_WITH_MSG, INTERNAL_ASSERT_NO_MSG) )

	#define ASSERT(...) EXPAND_MACRO( INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
	#define ASSERT(...)
#endif
