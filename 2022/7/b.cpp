#include "std_lib_facilities.h"
#include <map>
// /Users/song-yunha/aoc/2022/7/

int main()
{
    map<string, int> mp;
    mp.insert(make_pair("song",22));
    mp.insert(make_pair("song",23));
    /* cout << mp["song"] << '\n'; */
    for(auto i : mp)
    {
        cout << i.first << '\n';
    }
    /* string path = "/Users/song-yunha/aoc/2022/7/"; */
    /* cout << path << '\n'; */
    /* auto index = find(path.rbegin()+1, path.rend(), '/'); */
    /* path.erase(index.base(), path.rbegin().base()); */
    /* cout << path << '\n'; */
    return 0;
}