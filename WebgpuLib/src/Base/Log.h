#pragma once

#include "Base/Base.h"
#include "Base/Logger.h"

#include <memory>

namespace Base {

	class Log
	{
	public:
		static std::shared_ptr<Logger>& GetLogger() { return s_Logger; }
	private:
		static void Init();
	private:
		static std::shared_ptr<Logger> s_Logger;
	private:
		friend class Application;
	};

}

#define TRACE(...)         ::Base::Log::GetLogger()->Trace(__VA_ARGS__)
#define INFO(...)          ::Base::Log::GetLogger()->Info(__VA_ARGS__)
#define WARN(...)          ::Base::Log::GetLogger()->Warn(__VA_ARGS__)
#define ERROR(...)         ::Base::Log::GetLogger()->Error(__VA_ARGS__)
#define CRITICAL(...)      ::Base::Log::GetLogger()->Critical(__VA_ARGS__)
