#include "std_lib_facilities.h"
#include <set>

constexpr int LOWER = -96;
constexpr int UPPER = -38;

int get_item_value(char c)
{
    if (isupper(c)) return c + UPPER;
    if (islower(c)) return c + LOWER;
}

pair<string,string> get_pair(string str)
{
    return make_pair(str.substr(0,str.size()/2),str.substr(str.size()/2,str.size()-1));
}

char find_duplicate(string str1, string str2)
{
    set<char> first (str1.begin(), str1.end());
    set<char> second (str2.begin(), str2.end());
    
    for (char ch1 : first)
    {
        for (char ch2 : second)
        {
            if (ch1 == ch2) return ch2;
        }
    }
}

int main()
{
    ifstream input;
    input.open("input.txt");
    
    string rucksack;
    int sum = 0;
    while(getline(input, rucksack))
    {
        pair<string,string> compartments = get_pair(rucksack);
        char duplicate = find_duplicate(compartments.first, compartments.second);
        sum += get_item_value(duplicate);
    }
    cout << sum << '\n';
    return 0;
}