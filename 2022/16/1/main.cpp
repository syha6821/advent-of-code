//cd "/Users/song-yunha/aoc/2022/16/1/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/16/1/"main
#include "std_lib_facilities.h"
#include "read.h"
#include "valve.h"
#include "branch.h"
#include "logic.h"

const string SAMPLE = "/Users/song-yunha/aoc/2022/16/sample.txt";
vector<Valve> valve_list = read_file(SAMPLE);

/* const string INPUT = "/Users/song-yunha/aoc/2022/16/input.txt"; */
/* vector<Valve> valve_list = read_file(INPUT); */

const unordered_map<string,Valve> Branch::default_valve_map = make_valve_map(valve_list);
const vector<Valve> Branch::usable_valves = get_usable_valves(valve_list);

int main()
{
    /* unordered_set<Branch> last_branches = grow_till_the_end({Branch()},{}); */
    /* int score = get_high_score(last_branches); */
    /* cout << score << '\n'; */
    
    int score = grow_till_the_end_({Branch()});
    cout << score << '\n';
    return 0;
}