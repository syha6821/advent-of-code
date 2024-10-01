#include "std_lib_facilities.h"
#include <set>

int find_marker(string str)
{
    for(int i = 0; i < str.size(); i++)
    {
        set<char> s;
        for(int j = 0; j < 4; j++)
        {
            s.insert(str[i+j]);
        }
        if (s.size() == 4) return i+4;
    }
    return -1;
}

int main()
{

    ifstream input;
    input.open("input.txt");
    string str;
    input >> str;
    cout << find_marker(str) << '\n';
    return 0;
}