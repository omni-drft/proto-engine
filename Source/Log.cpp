#include "Log.hpp"

namespace ProtoEngine
{
	std::shared_ptr<spdlog::logger> Log::logger;

	void Log::Init()
	{
		spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
		logger = spdlog::stdout_color_mt("ProtoEngine");
		#ifdef DEBUG
		logger->set_level(spdlog::level::trace);
		#else
		logger->set_level(spdlog::level::info);
		#endif
	}
}

