#pragma once
#include "spdlog/spdlog.h"

#define GAMOVER_DEFAULT_LOGGER_NAME "GameoverLogger"

#if defined(GAMEOVER_PLATFORM_WINDOWS)
#define GAMEOVER_BREAK() __debugbreak()
#elif defined(GAMEOVER_PLATFORM_LINUX)
#define GAMEOVER_BREAK() __builtin_trap()
// #else
// #define GAMEOVER_BREAK() buildin_debug   trap()
#endif


#ifndef GAMOVER_CONFIG_RELEASE
#define GAMEOVER_TRACE(...)     if (spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME) != nullptr) { spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__); }
#define GAMEOVER_DEBUG(...)     if (spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME) != nullptr) { spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__); }
#define GAMEOVER_INFO(...)      if (spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME) != nullptr) { spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__); }
#define GAMEOVER_WARN(...)      if (spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME) != nullptr) { spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__); }
#define GAMEOVER_ERROR(...)     if (spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME) != nullptr) { spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__); }
#define GAMEOVER_FATAL(...)     if (spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME) != nullptr) { spdlog::get(GAMOVER_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__); }
#define GAMEOVER_ASSERT(x, msg) if ((x)) {} else{ GAMEOVER_FATAL("ASSERT {}\n\t{}\n\tin file: {}\n\ton file: {}", #x, msg, __FILE__, __LINE__); }
#else
#define GAMEOVER_TRACE(...) void(0)
#define GAMEOVER_DEBUG(...) void(0)
#define GAMEOVER_INFO(...) void(0)
#define GAMEOVER_WARN(...) void(0)
#define GAMEOVER_ERROR(...) void(0)
#define GAMEOVER_FATAL(...) void(0)
#endif