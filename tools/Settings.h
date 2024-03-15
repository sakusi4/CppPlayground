#pragma once
#include "../patterns/SingletonTemplate.h"

class Settings : public SingletonTemplate<Settings>
{
public:	
    Settings();
	~Settings();

    bool constructSettings(const std::string& path);    

public:
    std::string logPath;
	std::string programName;
};