/* ============================ FILE PURPOSE ==============================
* 
*  This file contains the implementation of the Log class. 
* 
========================================================================= */

#include "Log.hpp"

namespace ProtoEngine
{
	/// <summary>
	/// Global logger instance
	/// </summary>
	std::shared_ptr<spdlog::logger> Log::logger;

	void Log::Init()
	{
		// Set the log pattern (time, log level, message)
		spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
		logger = spdlog::stdout_color_mt("ProtoEngine");
		// Set the log level depending on the build type
		#ifdef DEBUG
		logger->set_level(spdlog::level::trace);
		#else
		logger->set_level(spdlog::level::info);
		#endif
	}
}

