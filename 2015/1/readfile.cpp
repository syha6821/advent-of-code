#include "readfile.h"
#include <fstream>

string FileName(int argc, char** argv)
{
    const string INPUT = "./input.txt";
    const string SAMPLE = "./sample.txt";
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

vector<Pattern> ReadPattern(string filename)
{
    vector<Pattern> patterns;
    ifstream ifs(filename);
    string line;
    while(getline(ifs, line))
    {
        if(line.empty()) break;
        for(char ch : line)
        {
            if(ch == '(')
            {
                patterns.push_back(Pattern::Up);
            }
            if(ch == ')')
            {
                patterns.push_back(Pattern::Down);
            }
        }
    }
    return patterns;

}
