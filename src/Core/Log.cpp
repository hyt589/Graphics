#include "Log.hpp"

namespace HYT
{
    Shared<spdlog::logger> Logger::s_logger;

    void Logger::init()
    {
        spdlog::set_pattern("%^[%c] [%n] [%l]: %v%$");
		s_logger = spdlog::stdout_color_mt("HYT");
		s_logger->set_level(spdlog::level::trace);
    }
    
} // namespace HYT
