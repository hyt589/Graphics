#include "global.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace HYT
{
    class Logger
    {
    public:
        static void init();
        inline static std::shared_ptr<spdlog::logger> &get() { return s_logger; };

    protected:
        static std::shared_ptr<spdlog::logger> s_logger;
    };
} // namespace HYT

#define LOG_TRACE(...) ::HYT::Logger::get()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) ::HYT::Logger::get()->debug(__VA_ARGS__)
#define LOG_INFO(...) ::HYT::Logger::get()->info(__VA_ARGS__)
#define LOG_WARN(...) ::HYT::Logger::get()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::HYT::Logger::get()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::HYT::Logger::get()->critical(__VA_ARGS__)
