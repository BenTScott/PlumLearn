#include "plpch.h"

#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace PlumLearn {
	Log::Log()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("PLUM");
		s_CoreLogger->set_level(spdlog::level::trace);
	}
}