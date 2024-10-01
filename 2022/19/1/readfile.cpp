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

vector<int> extract_nums(string str)
{
    vector<int> nums;
    stringstream ss(str);
    string temp;
    int found;
    while(!ss.eof())
    {
        ss >> temp;
        if (stringstream(temp) >> found)
        {
            nums.push_back(found);
        }
    }
    return nums;
}

vector<BluePrint> ReadBluePrint(string filename)
{
    vector<BluePrint> blueprints;
    ifstream ifs(filename);
    string line;
    while(getline(ifs, line))
    {
        vector<int> nums = extract_nums(line);
        vector<Recipe> recipes;
        int id = nums[0];
        recipes.push_back(Recipe(MaterialType::Ore, nums[1],0,0));
        recipes.push_back(Recipe(MaterialType::Clay, nums[2],0,0));
        recipes.push_back(Recipe(MaterialType::Obsidian, nums[3],nums[4],0));
        recipes.push_back(Recipe(MaterialType::Geode, nums[5],0,nums[6]));
        
        blueprints.push_back(BluePrint(id, recipes));
    }
    return blueprints;
}