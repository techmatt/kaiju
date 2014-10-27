
#include "main.h"

vector<string> getFileLines(ifstream &file, size_t minLineLength)
{
    std::vector<std::string> result;
    std::string line;
    while (!file.fail())
    {
        getline(file, line);
        if (!file.fail() && line.length() >= minLineLength) result.push_back(line.c_str());
    }
    return result;
}
