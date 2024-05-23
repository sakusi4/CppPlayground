#pragma once

#include <vector>
#include "../patterns/SingletonTemplate.h"

class DataUtil : public SingletonTemplate<DataUtil>
{
public:
    DataUtil() = default;
    ~DataUtil() = default;

    int getRandomValue(const int& min, const int& max);
    double getRandomValue(const double& min, const double& max);
    std::vector<std::string> split(const std::string& str, char delim);
};

