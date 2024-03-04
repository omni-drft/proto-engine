#pragma once

#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ProtoEngine 
{

class Log
{
public:
	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return logger; }

private:
	static std::shared_ptr<spdlog::logger> logger;
};

}
