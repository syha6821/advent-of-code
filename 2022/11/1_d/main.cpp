//cd "/Users/song-yunha/aoc/2022/11/1_d/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/11/1_d/"main
#include "std_lib_facilities.h"
#include <fstream>
#include "monkey.h"
#include "logic.h"
#include "recipe.h"
typedef unsigned long long int ull;

const int ROUND = 15;

const string EXAMPLE = "../example.txt";
const string INPUT = "../input.txt";

pair<ull, ull> find_highest_two(const vector<Monkey>& monkeys);

int main()
{
    vector<Recipe> recipes = monkey_recipes(EXAMPLE);
    
    // Original way
    vector<Monkey> monkeys = get_monkeys(recipes);

    for (int round = 1; round <= ROUND; round++)
    {
        do_keep_away(monkeys);
        if(round % 1000 == 0 || round == 1 || round == 20 || round == 19 || round == 21 || round == 30 || round == 10)
        {
            cout << "ROUND : " << round << '\n';
            for (int i = 0; i < monkeys.size(); i++)
            {
                cout << "Monkey[" << i << "] : " << monkeys[i].get_score() << '\n';
            }
            cout << '\n';
        }
    }


    return 0;
}

pair<ull, ull> find_highest_two(const vector<Monkey>& monkeys)
{
    pair<ull, ull> winners;
    for (Monkey monkey: monkeys)
    {
        if(monkey.get_score() > winners.second)
        {
            if(monkey.get_score() > winners.first)
            {
                winners.second = winners.first;
                winners.first = monkey.get_score();
                continue;
            }
            winners.second = monkey.get_score();
        }
    }
    return winners;
}
