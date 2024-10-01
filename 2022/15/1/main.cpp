//cd "/Users/song-yunha/aoc/2022/15/1/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/15/1/"main
#include "input.h"
#include "logic.h"
#include "range.h"
#include <set>

const string SAMPLE = "/Users/song-yunha/aoc/2022/15/sample.txt";
const string INPUT = "/Users/song-yunha/aoc/2022/15/input.txt";

int main()
{
    /* vector<Sensor> sensors = read_file(SAMPLE); */
    /* int search_height = 20; */
    /* int search_width = 20; */

    vector<Sensor> sensors = read_file(INPUT);
    int search_height = 4000000;
    int search_width = 4000000;
    
    int a = find_distress_beacon(search_width, search_height, sensors);
    cout << a << '\n';


    // Part One
    /* int target_y = 2000000; */
    /* vector<Sensor> sensors = read_file(INPUT); */

    /* int target_y = 10; */
    /* vector<Sensor> sensors = read_file(SAMPLE); */

    /* int a = count_scanned_area(sensors, target_y); */
    /* cout << a << '\n'; */

    return 0;
}