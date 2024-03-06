/* ========================= PURPOSE OF FILE =========================
* 
*  This file contains the Log class, which is used to initialize the
*	 logging system and provide a logger object to the rest of the
*  application.
* 
==================================================================== */


#pragma once

// Include statements
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ProtoEngine 
{

/// <summary>
/// Class used to initialize the logging system and provide a logger object to the rest of the application.
/// </summary>
class Log
{
public:
	/// <summary>
	/// Initializer for the logging system.
	/// </summary>
	static void Init();

	/// <summary>
	/// Logger object getter.
	/// </summary>
	/// <returns>Logger object</returns>
	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return logger; }

private:
	/// <summary>
	/// Global logger object.
	/// </summary>
	static std::shared_ptr<spdlog::logger> logger;
};

}
