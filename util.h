
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

//
// vector utilities
//
template<class T>
int findFirstIndex(const vector<T> &collection, const T &value)
{
    int index = 0;
    for (const auto &element : collection)
    {
        if (element == value)
            return index;
        index++;
    }
    return -1;
}

template<class T>
void removeSwap(std::vector<T> &collection, size_t index)
{
    std::swap(collection[index], collection.back());
    collection.pop_back();
}