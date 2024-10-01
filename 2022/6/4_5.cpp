#include "std_lib_facilities.h"
#include <set>

//mgwwjddqzqdqsstctjjsdjsdsrsfsmfsfwwltwlwhwnhhlffzddgffwlffbsfshfs
int find_marker4_4(const string& str)
{
    constexpr int size = 4;
    for(int i = 0; i < str.size() - size + 1; i++)
    {
        const string word = str.substr(i,size);
        for (int j = 0; j < word.size() - 1; j++)
        {
            int dup = word.find(word[j],j+1);
            if(dup != -1) break;
            if(j == size - 2) return i + size;
        }
    }
    return -1;
}


int find_marker(const string& str)
{
    constexpr int SIZE = 4;
    int count = 0;
    for(auto it = str.begin(); it != str.end(); it++)
    {
        for (auto j = it; j != it + SIZE - 1; j++)
        {
            auto a = find(j+1, it + SIZE - 1, *j);
            if(!(*a)) break;
            if(j == it + SIZE - 2) return count + SIZE;
        }
        count++;
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