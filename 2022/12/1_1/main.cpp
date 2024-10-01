//cd "/Users/song-yunha/aoc/2022/12/1_1/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/12/1_1/"main
#include "std_lib_facilities.h"
#include <fstream>
#include "read.h"
#include "point.h"

int main()
{
    const string sample = "/Users/song-yunha/aoc/2022/12/sample";
    vector<vector<char>> map = read_map(sample);
    print_map(map);

    return 0;
}
