//cd "/Users/song-yunha/aoc/2022/13/1/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/13/1/"main
#include "std_lib_facilities.h"
#include "input.h"
#include "packet.h"
#include "logic.h"

const string SAMPLE = "/Users/song-yunha/aoc/2022/13/sample";
const string INPUT = "/Users/song-yunha/aoc/2022/13/input.txt";

int main()
{
    vector<Packet> packets = read_packets(INPUT);
    packets = add_divider_packets(packets);
    packets = sort_packets(packets);

    /* vector<pair<Packet,Packet>> pairs = read_input(INPUT); */
    /* int count = 0; */
    /* int sum = 0; */
    /* for(pair<Packet,Packet> p : pairs) */
    /* { */
    /*     count++; */
    /*     cout << "\033[1;34m" << "== Pair " << count << "\033[0m\n"; */
    /*     if(compare_packets(p)) */
    /*     { */
    /*         cout << "\033[1;31m" <<  count << "\033[0m\n"; */
    /*         sum += count; */
    /*     } */
    /* } */
    /* cout << sum << '\n'; */
    return 0;
}