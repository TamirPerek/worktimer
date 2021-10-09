#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/sink.h"
#include "spdlog/common.h"

#include <vector>
#include <memory>

class Logger
{
private:
    std::shared_ptr<spdlog::logger> logger;

    Logger()
    {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>("log/WorkTimer_Logfile.log", 23, 59));
        logger = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
        spdlog::flush_on(spdlog::level::info);
        spdlog::register_logger(logger);
    }
    Logger(const Logger &) = delete;
    Logger(Logger &&) = delete;

    Logger &operator=(const Logger &) = delete;
    Logger &operator=(Logger &&) = delete;

public:
    ~Logger() = default;
    static Logger &getInstance()
    {
        static Logger Instance;
        return Instance;
    }

    const std::shared_ptr<spdlog::logger> &getLogger() const
    {
        return logger;
    }
};
