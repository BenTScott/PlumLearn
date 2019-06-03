#pragma once

#include <memory>
#include "utils/singleton.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace PlumLearn {

	class Log : public Singleton<Log>
	{
	public:
		friend class Singleton<Log>;

		inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		//inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		Log();
		std::shared_ptr<spdlog::logger> s_CoreLogger;
	};

}

// Log macros
#define PL_CORE_TRACE(...)    ::PlumLearn::Log::GetInstance().GetCoreLogger()->trace(__VA_ARGS__)
#define PL_CORE_INFO(...)     ::PlumLearn::Log::GetInstance().GetCoreLogger()->info(__VA_ARGS__)
#define PL_CORE_WARN(...)     ::PlumLearn::Log::GetInstance().GetCoreLogger()->warn(__VA_ARGS__)
#define PL_CORE_ERROR(...)    ::PlumLearn::Log::GetInstance().GetCoreLogger()->error(__VA_ARGS__)
#define PL_CORE_FATAL(...)    ::PlumLearn::Log::GetInstance().GetCoreLogger()->fatal(__VA_ARGS__)