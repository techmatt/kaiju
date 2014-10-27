
#include "main.h"

vector<string> getFileLines(ifstream &file, size_t minLineLength)
{
    vector<string> result;
    string line;
    while (!file.fail())
    {
        getline(file, line);
        if (!file.fail() && line.length() >= minLineLength) result.push_back(line.c_str());
    }
    return result;
}

vector<string> getFileLines(const string &filename, size_t minLineLength)
{
    ifstream file(filename);
    Assert(!file.fail(), string("failed to open ") + filename);
    return getFileLines(file, minLineLength);
}

vector<string> split(const string &str, const string &separator)
{
    Assert(separator.length() >= 1, "empty seperator");
    vector<string> result;

    if (str.size() == 0)
    {
        result.push_back("");
        return result;
    }

    string entry;
    for (size_t i = 0; i < str.length(); i++)
    {
        bool isSeperator = true;
        for (size_t testIndex = 0; testIndex < separator.length() && i + testIndex < str.length() && isSeperator; testIndex++)
        {
            if (str[i + testIndex] != separator[testIndex])
            {
                isSeperator = false;
            }
        }
        if (isSeperator)
        {
            if (entry.length() > 0)
            {
                result.push_back(entry);
                entry.clear();
            }
            i += separator.size() - 1;
        }
        else
        {
            entry.push_back(str[i]);
        }
    }
    if (entry.length() > 0)
        result.push_back(entry);
    return result;
}

vector<string> split(const string& str, const char separator)
{
    return split(str, string(1, separator));
}