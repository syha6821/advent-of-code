//cd "/Users/song-yunha/aoc/2022/14/1/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/14/1/"main
#include "std_lib_facilities.h"
#include "scan.h"
#include "map.h"
#include "sand.h"

const string SAMPLE = "/Users/song-yunha/aoc/2022/14/sample";
const string INPUT = "/Users/song-yunha/aoc/2022/14/input.txt";

int main()
{
    Map map(scan_file(INPUT));
    map.print_keys();
    cout << "deepest : " << map.get_deepest() << '\n';
    char state = 'S';
    int count = 0;
    while (state != 'F')
    {
        Sand sand = Sand();
        state = 'S';
        count++;
        while(state == 'S')
        {
            state = sand.fall(map);
        }
    }
    cout << count << '\n';
    return 0;
}