#include "std_lib_facilities.h"
#include <set>

int find_marker(const string& str)
{
    string tmp = str.substr(0,4);
    set<char> s;
    for (char ch : tmp) s.insert(ch);
    if(s.size() == 4) return 4;

    for(int i = 4; i < str.size(); i++)
    {
        tmp.erase(tmp.begin());
        tmp.push_back(str[i]);
        set<char> s;
        for (char ch : tmp) s.insert(ch);
        if(s.size() == 4) return i + 1;
    }
    return -1;
}

int find_marker(const string& str)
{
    const int SIZE = 4;
    int count = 0;
    for(auto it = str.begin(); it != str.end() - (SIZE - 1); it++)
    {
        set<char> s;
        for_each(it, it + 4, [&s](char ch) { s.insert(ch); });
        if(s.size() == 4) return count + 4;
        count++;
    }
    return 0;
}

int main()
{
    //5 6 10 11
    cout << find_marker("bvwbjplbgvbhsrlpgdmjqwftvncz") << '\n';
    cout << find_marker("nppdvjthqldpwncqszvftbrmjlhg") << '\n';
    cout << find_marker("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg") << '\n';
    cout << find_marker("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw") << '\n';
    
    /* string a = "hello world"; */
    /* cout << a << '\n'; */
    /* for(auto it = a.begin(); it != a.end() - 3; it++) */
    /* { */
    /*     for_each(it, it + 4,[](char ch){cout << ch;}); */
    /*     cout << '\n'; */
    /* } */

    return 0;
}