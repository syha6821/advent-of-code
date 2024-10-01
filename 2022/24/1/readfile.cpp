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

Map ReadMap(const string& filename)
{
    ifstream ifs(filename);
    string line;
    getline(ifs,line);
    int width = line.size() - 2;
    int height = 1;
    while(getline(ifs,line))
    {
        height++;
    }
    height -= 2;
    return Map(width, height);
}

bool is_blizzard(char ch)
{
    return (ch == '<') || (ch == '>') || (ch == '^') || (ch == 'v');
}

vector<Blizzard> ReadBlizzard(const string& filename, const Map& map)
{
    vector<Blizzard> blizzards;
    ifstream ifs(filename);
    string line;
    int row = 0;
    while(getline(ifs,line))
    {
        if(line.empty()) break;
        for(int column = 0; column < line.size(); column++)
        {
            if(is_blizzard(line[column]))
            {
                blizzards.push_back(Blizzard(Position(row, column, map.width(), map.height()), char_to_direction(line[column])));
            }
        }
        row++;
    }
    return blizzards;
}