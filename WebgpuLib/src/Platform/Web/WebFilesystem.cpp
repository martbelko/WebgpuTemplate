#if !defined(PLATFORM_WEB)
	#error This file should only be compiled for web/emscripten build
#endif

#include "Base/Filesystem.h"

namespace Base {

	void Filesystem::Init()
	{
		s_AssetsPath = "assets";
	}

}
