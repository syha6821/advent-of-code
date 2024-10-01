//cd "/Users/song-yunha/aoc/2022/11/1_everywhere/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/11/1_everywhere/"main
#include "std_lib_facilities.h"
#include <fstream>
#include "monkey.h"
#include "logic.h"
#include "recipe.h"
#include "test.h"
#include "relief.h"

const int ROUND = 1000;
const int TRY_NUM = 10;
const int EXPR_LEN = 1;

const string EXAMPLE = "../example.txt";
const string INPUT = "../input.txt";

int main()
{
    vector<Recipe> recipes = monkey_recipes(EXAMPLE);
    vector<Monkey> sample_monkeys = get_monkeys(recipes);
    vector<Relief> relieves = make_relieves(EXPR_LEN, TRY_NUM);
    vector<vector<Relief>> relief_combination = make_relief_combination(relieves,3);

    cout << "Start calc with "  << relieves.size() << " relieves.\n";
    cout << relief_combination.size() << '\n';

    for (vector<Relief> relieves : relief_combination)
    {
        vector<Monkey> monkeys = sample_monkeys;
        for (int round = 1; round <= ROUND; round++)
        {
            for (Monkey &monkey : monkeys)
            {
                int count = 0;
                int item_count = monkey.count_current_item();
                while (count != item_count)
                {
                    count++;
                    Item item = monkey.pick_item();
                    relieves[0](item);
                    monkey.add_item(item);
                }
            }
            do_keep_away(monkeys, relieves[1]);
            for (Monkey &monkey : monkeys)
            {
                int count = 0;
                int item_count = monkey.count_current_item();
                while (count != item_count)
                {
                    count++;
                    Item item = monkey.pick_item();
                    relieves[2](item);
                    monkey.add_item(item);
                }
            }
            if(is_test_round(round))
            {
                if(!test(round, monkeys)) break;
                if(round == ROUND) // It means it succeed till the last round? If it failed before last round, It couldn't reach here.
                {
                    for(auto relief : relieves)
                    {
                        relief.print_info();
                    }
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
