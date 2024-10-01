//cd "/Users/song-yunha/aoc/2022/11/1/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/11/1/"main
#include "std_lib_facilities.h"
#include <fstream>
#include "monkey.h"
#include "logic.h"
#include "recipe.h"

const string EXAMPLE = "../example.txt";
const string INPUT = "../input.txt";

int main()
{
    const int ROUND = 20;
    vector<Recipe> recipes = monkey_recipes(EXAMPLE);
    vector<Monkey> monkeys = get_monkeys(recipes);

    for (int round = 1; round <= ROUND; round++)
    {
        do_keep_away(monkeys);
    }
    
    for (Monkey monkey : monkeys)
    {
        cout << monkey.get_score() << '\n';
    }
    
    cout << "-------result-------\n";

    pair<int, int> winners = find_highest_two(monkeys);
    cout << winners.first << '\n';
    cout << winners.second << '\n';
    cout << (long int)(winners.first) * (long int)(winners.second)<< '\n';
    return 0;
}