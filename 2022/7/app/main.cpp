//cd "/Users/song-yunha/aoc/2022/7/app/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/7/app/"main
#include "logic.h"
#include "state.h"

int main()
{
    /* State state = read_lines("../input_sample.txt"); */
    State state = read_lines("../input.txt");
    cout << "\n\n\n";
    const int  TOTAL_DISK = 70000000;
    const int REQUIRED_DISK_SIZE = 30000000;
    int total_dirs_size = get_dir_size(state.out_most);
    int remained_disk_size = TOTAL_DISK - total_dirs_size;
    int needed_disk_size = REQUIRED_DISK_SIZE - remained_disk_size;
    cout << total_dirs_size << '\n';
    cout << remained_disk_size << '\n';
    cout << needed_disk_size << '\n';
    
    cout << find_lowest_to_delete(needed_disk_size,total_dirs_size) << '\n';
    return 0;
}