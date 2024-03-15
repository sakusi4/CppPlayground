#pragma once

#include <string.h>
#include <fstream>
#include <mutex>
#include <memory>
#include <thread>
#include "../patterns/SingletonTemplate.h"


enum eLogLevel
{
    LogLevel_Debug,
    LogLevel_Info,
    LogLevel_Warning,
    LogLevel_Error,
    LogLevel_Check,
    LogLevel_Data
};

class Settings;
class Logger : public SingletonTemplate<Logger>
{

public:
    Logger();
    ~Logger();

    void out(const eLogLevel& logLevel, const std::thread::id& thread_id, const char* file, const int& line, const char* func, const char* msg, ...);

private:
    std::mutex mx;
    std::once_flag redisInitFlag;

    std::string fileDate;
    std::string fileDate_sys;    

    std::ofstream logFile;
    std::ofstream logFile_sys;

    Settings* settings;
};

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_DATA(logger, msg, ...) logger->out(eLogLevel::LogLevel_Data, std::this_thread::get_id(), __FILENAME__, __LINE__, __FUNCTION__, msg,  ##__VA_ARGS__)
#define LOG_CHECK(logger, msg, ...) logger->out(eLogLevel::LogLevel_Check, std::this_thread::get_id(), __FILENAME__, __LINE__, __FUNCTION__, msg,  ##__VA_ARGS__)
#define LOG_ERROR(logger, msg, ...) logger->out(eLogLevel::LogLevel_Error, std::this_thread::get_id(), __FILENAME__, __LINE__, __FUNCTION__, msg,  ##__VA_ARGS__)
#define LOG_DEBUG(logger, msg, ...) logger->out(eLogLevel::LogLevel_Debug, std::this_thread::get_id(), __FILENAME__, __LINE__, __FUNCTION__, msg,  ##__VA_ARGS__)
#define LOG_WARN(logger, msg, ...) logger->out(eLogLevel::LogLevel_Warning, std::this_thread::get_id(), __FILENAME__, __LINE__, __FUNCTION__, msg,  ##__VA_ARGS__)
#define LOG_INFO(logger, msg, ...) logger->out(eLogLevel::LogLevel_Info, std::this_thread::get_id(), __FILENAME__, __LINE__, __FUNCTION__, msg,  ##__VA_ARGS__)