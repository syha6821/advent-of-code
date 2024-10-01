#include "std_lib_facilities.h"

int find_marker(string str)
{
    constexpr int SIZE = 4;
    for_each(str.begin(), str.end() - (SIZE - 1), [](char ch){cout << "ch :" << ch << '\n';});
    return -1;
}

int main()
{
    find_marker("hello");
    /* cout << find_marker("bvwbjplbgvbhsrlpgdmjqwftvncz") << '\n'; */
    /* cout << find_marker("nppdvjthqldpwncqszvftbrmjlhg") << '\n'; */
    /* cout << find_marker("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg") << '\n'; */
    /* cout << find_marker("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw") << '\n'; */
    return 0;
}