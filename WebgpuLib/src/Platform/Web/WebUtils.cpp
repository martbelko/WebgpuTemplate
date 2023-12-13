#if !defined(PLATFORM_WEB)
	#error This file should only be compiled for web/emscripten build
#endif

#include "Base/Utils.h"

#include <emscripten/emscripten.h>

namespace Base {

	void Utils::Sleep(uint32_t miliseconds)
	{
		emscripten_sleep(miliseconds);
	}

}
