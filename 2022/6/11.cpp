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

int main()
{

    /* ifstream input; */
    /* input.open("input.txt"); */
    /* string str; */
    /* input >> str; */
    /* cout << find_marker(str) << '\n'; */

    /* cout << find_marker("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw") << '\n'; */
    cout << find_marker("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg") << '\n';
    /* cout << find_marker("bvwbjplbgvbhsrlpgdmjqwftvncz") << '\n'; */
    /* cout << "bvwbjplbgvbhsrlpgdmjqwftvncz" << '\n'; */
    /* cout << find_marker("bvwbjplbgvbhsrlpgdmjqwftvncz") << '\n'; */
    return 0;
}