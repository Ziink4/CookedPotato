#pragma once

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#ifndef NDEBUG
#define LOG_STRINGIZE_(x) #x
#define LOG_STRINGIZE(x) LOG_STRINGIZE_(x)
#define LOG_TRACE(logger, ...) \
    logger->info("[ " __FILE__ ":" LOG_STRINGIZE(__LINE__) " ] " __VA_ARGS__)
#else
#define LOG_TRACE(logger, ...) (void)0
#endif
//if (!logger->should_log(spdlog::level::trace)) logger->set_level(spdlog::level::trace);

namespace engine
{

struct Logger
{
    inline static auto console = spdlog::stdout_color_mt("console");
};


}
