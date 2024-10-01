//cd "/Users/song-yunha/aoc/2022/12/1/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/12/1/"main
#include "std_lib_facilities.h"
#include "device.h"
#include "unit.h"
#include "logic.h"

const string SAMPLE = "/Users/song-yunha/aoc/2022/12/sample";
const string INPUT = "/Users/song-yunha/aoc/2022/12/input.txt";

int main()
{
    Map map = read_reverse_map(INPUT);
    cout << map.get_end().get_point().x << ',' << map.get_end().get_point().y << '\n';
    int step = find_nearest_a_from_end(map, {Unit(map.get_end())});
    cout << step << '\n';

    return 0;
}