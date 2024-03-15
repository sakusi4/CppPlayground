#pragma once
#include <cpp_redis/cpp_redis>
#include "../patterns/SingletonTemplate.h"

class Logger;
class Settings;
class RedisHandler : public SingletonTemplate<RedisHandler>
{
public:
    RedisHandler(/* args */);
    ~RedisHandler();

    void setValue(const std::string& key, const std::string& value);    
    bool getValue(const std::string& key, std::string& value);
    void hset(const std::string& key, const std::string& field, const std::string& value);
    bool hget(const std::string& key, const std::string& field, std::string& value, bool bPrint = true);
    void del(const std::string& key);    

private:
    cpp_redis::client client;
    Logger* logger;
    Settings *settings;
};
