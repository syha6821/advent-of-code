#include "read.h"

vector<vector<char>> read_map(string filename)
{
    vector<vector<char>> map;
    ifstream ifs(filename);
    string line;
    while (getline(ifs, line))
    {
        vector<char> line_ch;
        for(char ch : line) line_ch.push_back(ch);
        map.push_back(line_ch);
    }
    return map;
}

void print_map(vector<vector<char>> map)
{
    for (auto row : map)
    {
        for (auto area : row)
        {
            cout << area << ' ';
        }
        cout << '\n';
    }
}