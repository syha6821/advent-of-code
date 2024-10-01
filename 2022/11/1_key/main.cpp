//cd "/Users/song-yunha/aoc/2022/11/1_key/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/11/1_key/"main
#include "std_lib_facilities.h"
#include <fstream>
#include "monkey.h"
#include "logic.h"
#include "recipe.h"

const string EXAMPLE = "../example.txt";
const string INPUT = "../input.txt";


int main()
{
    const int ROUND = 10000;
    vector<Recipe> recipes = monkey_recipes(INPUT);
    vector<Monkey> monkeys = get_monkeys(recipes);

    do_keep_away(monkeys, ROUND);
    
    /* print_score(monkeys); */
    auto winner = find_highest_two(monkeys);
    
    cout << (long)winner.first * (long)winner.second << '\n';
    
    return 0;
}
