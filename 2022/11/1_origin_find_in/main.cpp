//cd "/Users/song-yunha/aoc/2022/11/1_origin_find_in/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/11/1_origin_find_in/"main
#include "std_lib_facilities.h"
#include <fstream>
#include "monkey.h"
#include "logic.h"
#include "recipe.h"
#include "test.h"
#include "relief.h"

const int ROUND = 1000;
const int TRY_NUM = 50;
const int EXPR_LEN = 2;

const string EXAMPLE = "../example.txt";
const string INPUT = "../input.txt";

int main()
{
    vector<Recipe> recipes = monkey_recipes(EXAMPLE);
    vector<Monkey> sample_monkeys = get_monkeys(recipes);
    vector<Relief> relieves = make_relieves(EXPR_LEN, TRY_NUM);

    cout << "Start calc with "  << relieves.size() << " relieves.\n";

    for (Relief relieve : relieves)
    {
        vector<Monkey> monkeys = sample_monkeys;
        for (int round = 1; round <= ROUND; round++)
        {
            do_keep_away(monkeys, relieve);
            if(is_test_round(round))
            {
                if(!test(round, monkeys)) break;
                if(round == ROUND) // It means it succeed till the last round? If it failed before last round, It couldn't reach here.
                {
                    relieve.print_info();
                    for (int i = 0; i < monkeys.size(); i++)
                    {
                        cout << "Monkey[" << i << "] : " << monkeys[i].get_score() << '\n';
                    }
                }
            }
        }
    }

    return 0;
}
