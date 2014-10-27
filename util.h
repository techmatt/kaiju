
inline void Assert(bool statement, const string &description)
{
    if (!statement)
    {
        std::cout << "assert failed: " << description << endl;
    }
}

//
// file utilities
//
vector<string> getFileLines(ifstream &file, int minLineLength);
vector<string> getFileLines(const string &filename, size_t minLineLength);

//
// string utilities
//
vector<string> split(const string &str, const string &separator);
vector<string> split(const string &str, const char separator);