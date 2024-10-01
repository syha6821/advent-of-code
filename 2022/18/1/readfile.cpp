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

unordered_set<Cube> read_cubes(string filename)
{
    unordered_set<Cube> cubes;
    ifstream ifs(filename);
    string line;
    while(getline(ifs,line))
    {
        int x, y, z;
        stringstream ss(line);
        string num;
        getline(ss, num, ',');
        x = stoi(num);
        getline(ss, num, ',');
        y = stoi(num);
        getline(ss, num, ',');
        z = stoi(num);
        
        cubes.insert(Cube(x,y,z));
    }
    return cubes;
}