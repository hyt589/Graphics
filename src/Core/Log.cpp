#include "Log.hpp"

namespace HYT
{
    std::shared_ptr<spdlog::logger> Logger::s_logger;

    void Logger::init()
    {
        spdlog::set_pattern("%^[%c] [%n] [%l]: %v%$");
		s_logger = spdlog::stdout_color_mt("HYT");
		s_logger->set_level(spdlog::level::trace);
    }
} // namespace HYT
