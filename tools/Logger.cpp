#include "Logger.h"

#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdarg.h>
#include <sstream>
#include <iostream>
#include <limits.h>
#include <ctime>
#include <iostream>

#include "Settings.h"

using namespace std;

Logger::Logger() : settings(Settings::getInstance())
{
}

Logger::~Logger(void)
{
	unique_lock<mutex> lock(mx);

	if (logFile.is_open()){
		logFile.flush();
		logFile.close();
	}

    if(logFile_sys.is_open())
    {
        logFile_sys.flush();
        logFile_sys.close();
    }

	lock.unlock();
}

void Logger::out(const eLogLevel& logLevel, const thread::id& thread_id, const char* file, const int& line, const char* func, const char* msg, ...)
{
    if (msg == NULL)
        return;

	try
	{
		va_list arg_ptr;
		va_start(arg_ptr, msg);

        char strBuf[SHRT_MAX];
        memset(strBuf, 0, sizeof(strBuf));
		vsnprintf( strBuf, sizeof(strBuf), msg, arg_ptr);
		va_end(arg_ptr);

		va_end(arg_ptr);

		string logLevelHeader = "";
		switch (logLevel)
		{
		case LogLevel_Info:
			logLevelHeader = "[INFO]";
			break;
		case LogLevel_Debug:
			logLevelHeader = "[DEBUG]";
			break;
		case LogLevel_Warning:
			logLevelHeader = "[WARN]";
			break;
		case LogLevel_Error:
			logLevelHeader = "[ERROR]";
			break;
		case LogLevel_Check:
			logLevelHeader = "[CHECK]";
			break;
        case LogLevel_Data:
            logLevelHeader = "[DATA]";
            break;
        default:
            break;
		}

        const int64_t& microStamp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        const int& micro = microStamp % 1000000;
        const time_t& timeSec = microStamp / 1000000;
        struct tm* st = localtime(&timeSec);

		stringstream ss;
		ss << thread_id;
		string strThread(ss.str().c_str());
		strThread = strThread.substr(strThread.size() - 6, 50);
		
		string className(file);
		className = className.substr(0, className.rfind('.'));

		char strOutBuf[SHRT_MAX];
		sprintf(strOutBuf, "%s\t%04d.%02d.%02d %02d:%02d:%02d.%06d  [%s]%s::%s()[%d] %s",
				  logLevelHeader.c_str(), st->tm_year + 1900, st->tm_mon + 1, st->tm_mday, st->tm_hour, st->tm_min, st->tm_sec, micro, strThread.c_str(), className.c_str(), func, line, strBuf);

        char currentDate[12];
        memset(currentDate, 0, sizeof(currentDate));
		sprintf(currentDate, "%04d%02d%02d", st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);

		lock_guard<mutex> lock(mx);

        if ( logLevel == LogLevel_Data )
        {
            if (fileDate != currentDate)
            {
                fileDate = currentDate;

                if (logFile.is_open())
                    logFile.close();

                char tmp[1024];
                memset(tmp, 0, sizeof(tmp));
                snprintf(tmp, sizeof(tmp) - 1, "%s/%s.%04d%02d%02d.log",
                            settings->logPath.c_str(), settings->programName.c_str(),
                            st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);

                logFile.open(tmp, std::ofstream::out | std::ofstream::app);
            }

            if (logFile.is_open())
            {
                logFile << strOutBuf << endl;
                logFile.flush();
            }
        }
        else
        {
            if (fileDate_sys != currentDate)
            {
                fileDate_sys = currentDate;

                if (logFile_sys.is_open())
                    logFile_sys.close();

                char tmp[1024];
                memset(tmp, 0, sizeof(tmp));
                snprintf(tmp, sizeof(tmp) - 1, "%s/system.%s.%04d%02d%02d.log",
                            settings->logPath.c_str(), settings->programName.c_str(),
                            st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);

                logFile_sys.open(tmp, std::ofstream::out | std::ofstream::app);
            }

            if (logFile_sys.is_open())
            {
                logFile_sys << strOutBuf << endl;
                logFile_sys.flush();
            }
        }		
	}
	catch (exception &e)
	{
		cerr << "CLogger::out()" << e.what() << endl;
	}
}