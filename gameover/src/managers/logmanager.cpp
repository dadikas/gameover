#include "managers/logmanager.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include "log.h"
#include <memory>
namespace gameover::managers
{
    void LogManager::Initialize()
    {
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] %v%$");

        std::vector<spdlog::sink_ptr> sinks{consoleSink};

        auto logger = std::make_shared<spdlog::logger>(GAMOVER_DEFAULT_LOGGER_NAME, begin(sinks), end(sinks));
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
        spdlog::register_logger(logger);
    }
    void LogManager::Shutdown()
    {
        spdlog::shutdown();
    }
}