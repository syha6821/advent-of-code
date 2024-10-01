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

unordered_set<Elf> ReadElves(const string& filename)
{
    unordered_set<Elf> elves;
    ifstream ifs(filename);
    string line;
    int elf_num = 0;
    int row_num = 0;
    while(getline(ifs,line))
    {
        if(line.empty()) break;
        for(int column_num = 0; column_num < line.size(); column_num++)
        {
            if(line[column_num] == '#')
            {
                elves.insert(Elf(Position(row_num, column_num), elf_num));
                elf_num++;
            }
        }
        row_num++;
    }
    return elves;
}