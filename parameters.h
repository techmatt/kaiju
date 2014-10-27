
struct Parameters
{
    Parameters(const string &filename)
    {
        for (const string &line : getFileLines(filename, 3))
        {
            if (line[0] != '#')
            {
                auto parts = split(line, '=');
                parameters[parts[0]] = parts[1];
            }
        }
    }

    string getString(const string &s) const
    {
        if (parameters.count(s) == 0)
        {
            cout << "parameter not found: " << s << endl;
            return "";
        }
        return parameters.find(s)->second;
    }

    int getInt(const string &s) const
    {
        return std::stoi(getString(s));
    }

    void setInt(const string &s, int value)
    {
        parameters[s] = to_string(value);
    }

    map<string, string> parameters;
};
