#include "Settings.h"
#include "Logger.h"
#include "Format.h"
#include "json/json.h"

using namespace std;

Settings::Settings()
{
}

Settings::~Settings()
{
}

bool Settings::constructSettings(const std::string& path)
{
    const auto logger = Logger::getInstance();

    try
    {
        ifstream json_dir(path.c_str());
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        Json::Value root;

        JSONCPP_STRING errs;
        if (!parseFromStream(builder, json_dir, &root, &errs))
        {
            LOG_ERROR(logger, "Failed to parse json(%s)", errs.c_str());
            return false;
        }

        const auto& valueLogDirPath = root["log_dir_path"];
        if (!valueLogDirPath.isNull())
            logPath = valueLogDirPath.asString();
        else
            LOG_ERROR(logger, "Failed to get log_dir_path");

        const auto& valueProgramName = root["program_name"];
        if (!valueProgramName.isNull())
            programName = valueProgramName.asString();
        else
            LOG_ERROR(logger, "Failed to get 'program_name'");
        

        LOG_INFO(logger, "[Config] programName(%s), logPath(%s)", programName.c_str(), logPath.c_str());
        return true;
    }
    catch (const std::exception& e)
    {
        const auto& msg = Format::format("Exception => %s", e.what());
        LOG_ERROR(logger, "%s", msg.c_str());
        return false;
    }
}
