#include "readfile.h"
#include <fstream>

string FileName(int argc, char** argv)
{
    const string INPUT = "../input.txt";
    const string SAMPLE = "../sample.txt";
    const string SAMPLE2 = "../sample2.txt";
    string file_name;
    
    if (argc == 1)
    {
        return SAMPLE;
    }
    else if (string(argv[1]) == "input")
    {
        return INPUT;
    }
    else if (string(argv[1]) == "sample2")
    {
        return SAMPLE2;
    }
    else
    {
        return SAMPLE;
    }
}

pair<int, int> MapSize(const string& filename)
{
    int width = 0;
    int height = 0;
    ifstream ifs(filename);
    string line;
    while(getline(ifs, line))
    {
        if(line.empty()) break;
        height++;
        if(line.size() > width) width = line.size();
    }
    return make_pair(width, height);
}

/* vector<vector<char>> EmptyMap(pair<int, int> size) */
/* { */
/*     vector<vector<char>> map; */
/*     for(int i = 0; i < size.second + 2; i++) */
/*     { */
/*         map.push_back(vector<char>(size.first + 2, (char)Material::Empty)); */
/*     } */
/*     return map; */
/* } */

vector<vector<Area>> EmptyMap(pair<int, int> size)
{
    int width = size.first;
    int height = size.second;

    vector<vector<Area>> map;
    for (int row = 0; row < height + 2; row++)
    {
        map.push_back({});
        for (int column = 0; column < width + 2; column++)
        {
            map[row].push_back(Area(Material::Empty, Position(row, column)));
        }
    }
    return map;
}

Map ReadMap(const string& filename)
{
    ifstream ifs(filename);
    string line;
    auto size = MapSize(filename);
    vector<vector<Area>> empty_map = EmptyMap(size);

    int row_num = 1;
    while(getline(ifs, line))
    {
        if(line.empty()) break;
        for(int i = 0; i < line.size(); i++)
        {
            if(not isspace(line[i]))
            {
                empty_map[row_num][i + 1].changeMaterial(get_value_of(line[i]));
            }
        }
        row_num++;
    }

    return Map(empty_map);
}

vector<pair<char,int>> ReadPattern(const string& filename)
{
    ifstream ifs(filename);
    string line;
    while(getline(ifs, line)){}
    vector<pair<char,int>> patterns;

    char direction;
    int count;
    stringstream ss(line);
    ss >> count;
    patterns.push_back(make_pair('R',count));
    while(ss)
    {
        ss >> direction;
        ss >> count;

        patterns.push_back(make_pair(direction, count));
        if(not (ss >> direction))
        {
            break;
        }
        ss.putback(direction);
    }
    return patterns;
}