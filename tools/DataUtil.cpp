#include "DataUtil.h"

#include <random>
#include <string>
#include <sstream>

using namespace std;

int DataUtil::getRandomValue(const int& min, const int& max)
{
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(engine);
}

double DataUtil::getRandomValue(const double& min, const double& max)
{
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> dis(min, max);

    return dis(engine);
}

vector<std::string> DataUtil::split(const std::string& str, char delim)
{
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim))
    {
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;    
}
