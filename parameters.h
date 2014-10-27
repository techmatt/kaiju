
struct Parameters
{
    Parameters()
    {
    }

    string getString(const string &s)
    {
        if (parameters.count(s) == 0)
        {
            cout << "parameter not found: " << s << endl;
            return "";
        }
        return parameters[s];
    }

    int getInt(const string &s)
    {
        return std::stoi(s);
    }

    map<string, string> parameters;
};