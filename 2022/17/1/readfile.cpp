#include "readfile.h"

string FileName(int argc, char** argv)
{
    const string INPUT = "../input.txt";
    const string SAMPLE = "../sample.txt";
    string file_name;
    
    if (argc == 1)
    {
        return SAMPLE;
    }
    else if (string(argv[1]) == "input")
    {
        return INPUT;
    }
    else
    {
        return SAMPLE;
    }
}

Rock::SLICE to_slice(string line)
{
    Rock::SLICE slice;
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == '#')
        {
            int left_most = Chamber::WIDTH - 1 - Rock::LEFT_PAD;
            slice[left_most - i] = true;
        }
    }
    return slice;
}

Rock::SPRITE to_sprite(vector<string> lines)
{
    Rock::SPRITE sprite;
    for (int i = lines.size() - 1; i >= 0; i--)
    {
        sprite.push_back(to_slice(lines[i]));
    }
    return sprite;
}

vector<Rock> to_rocks(string rock_file_name)
{
    ifstream ifs(rock_file_name);
    vector<Rock> rocks;
    vector<string> lines;
    string line;
    while (getline(ifs, line))
    {
        if (line.empty())
        {
            rocks.push_back(Rock(to_sprite(lines)));
            lines.clear();
        }
        else
        {
            lines.push_back(line);
        }
    }
    rocks.push_back(Rock(to_sprite(lines)));
    return rocks;
}

vector<Jet> to_jet_pattern(string file_name)
{
    vector<Jet> jet_pattern;
    ifstream ifs(file_name);
    string line;
    while(getline(ifs,line))
    {
        for (char ch  : line)
        {
            if (ch == '<') jet_pattern.push_back(Jet::LEFT);
            if (ch == '>') jet_pattern.push_back(Jet::RIGHT);
        }
    }
    return jet_pattern;
}