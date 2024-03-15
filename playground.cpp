#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <set>
#include <memory.h>
#include "tools/Settings.h"

using namespace std;

int main(int argc, char* argv[])
{
    if( argc != 2 ) 
	{
		ostringstream ss;
		ss << "[ERROR](" << __FILE__ << ", " << __LINE__ <<") " << "Usage: " << argv[0] << " <conf file path>" << endl;
		cerr << ss.str() << endl;
		return 0;
	}

    const auto settings = Settings::getInstance();
    settings->constructSettings(argv[1]);

    return 0;
}