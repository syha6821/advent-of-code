#include "std_lib_facilities.h"
#include <bitset>

int find_marker(string str)
{
    const int NUM = 4;
    int filter = 0;
    for (int i = 0; i < NUM - 1; i++)
    {
        filter ^= (1 << (str[i] % 32));
    }
    bitset<32> bits = filter;

    for(int i = 0; i < str.size(); i++)
    {
        int first = str[i];
        int last = str[i + (NUM-1)];
        filter ^= (1 << (last % 32));
        bits = filter;
        if (bits.count() == NUM) return i+NUM;
        filter ^= (1 << (first % 32));
    }
    return -1;
}

int main()
{
    cout << find_marker("bvwbjplbgvbhsrlpgdmjqwftvncz") << '\n';
    cout << find_marker("nppdvjthqldpwncqszvftbrmjlhg") << '\n';
    cout << find_marker("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg") << '\n';
    cout << find_marker("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw") << '\n';
    
    return 0;
}