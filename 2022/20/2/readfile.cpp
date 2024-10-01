#include "readfile.h"

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

vector<Num> ReadNums(string filename)
{
    vector<Num> nums;
    ifstream ifs(filename);
    string line;
    while(getline(ifs,line))
    {
        nums.push_back(Num(stol(line)));
    }
    MakeLink(nums);
    return nums;
}