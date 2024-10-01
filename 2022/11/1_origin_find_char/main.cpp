//cd "/Users/song-yunha/aoc/2022/11/1_origin_find_char/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/11/1_origin_find_char/"main
#include "std_lib_facilities.h"
#include <fstream>
#include "monkey.h"
#include "logic.h"
#include "recipe.h"
#include "test.h"

const int ROUND = 20;

const string EXAMPLE = "../example.txt";
const string INPUT = "../input.txt";

int main()
{
    vector<Recipe> recipes = monkey_recipes(EXAMPLE);
    vector<Monkey> sample_monkeys = get_monkeys(recipes);

        vector<Monkey> monkeys = sample_monkeys;
        for (int round = 1; round <= ROUND; round++)
        {
            do_keep_away(monkeys);
            if(is_test_round(round))
            {
                if(!test(round, monkeys)) break;
                if(round == ROUND) // It means it succeed till the last round? If it failed before last round, It couldn't reach here.
                {
                    for (int i = 0; i < monkeys.size(); i++)
                    {
                        cout << "Monkey[" << i << "] : " << monkeys[i].get_score() << '\n';
                    }
                }
            }
        }

    return 0;
}
