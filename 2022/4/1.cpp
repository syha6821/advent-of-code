#include "std_lib_facilities.h"


pair<string,string> pair_by_split(string str, char delimeter)
{
    string first = str.substr(0,str.find(delimeter));
    string second = str.substr(str.find(delimeter) + 1,str.size() - 1);
    return make_pair(first,second);
}

pair<pair<int,int>,pair<int,int>> get_pairs(string input)
{
    pair<string,string> elves = pair_by_split(input, ',');
    pair<string,string> first_elf = pair_by_split(elves.first, '-');
    pair<string,string> second_elf = pair_by_split(elves.second, '-');
    
    return make_pair(make_pair(stoi(first_elf.first),stoi(first_elf.second)),make_pair(stoi(second_elf.first),stoi(second_elf.second)));
}

bool fully_contained(pair<int,int> first, pair<int,int> second)
{
    // 1
    /* if(first.first >= second.first && first.second <= second.second) */
    /* { */
    /*     return true; */
    /* } */
    /* if(second.first >= first.first && second.second <= first.second) */
    /* { */
    /*     return true; */
    /* } */

    //2
    if(first.second >= second.first && first.second <= second.second)
    {
        return true;
    }
    if(second.second >= first.first && second.second <= first.second)
    {
        return true;
    }
    return false;
}

int main()
{
    ifstream input;
    input.open("input.txt");
    string elves;
    int count = 0;
    while(getline(input,elves))
    {
        auto elves_pair = get_pairs(elves);
        auto first_elf = elves_pair.first;
        auto second_elf = elves_pair.second;
        if (fully_contained(first_elf, second_elf)) count++;
    }
    cout << count << '\n';
    return 0;
}