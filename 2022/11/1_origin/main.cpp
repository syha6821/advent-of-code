//cd "/Users/song-yunha/aoc/2022/11/1_origin/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/11/1_origin/"main
#include "std_lib_facilities.h"
#include <fstream>
#include "monkey.h"
#include "logic.h"
#include "recipe.h"

const int ROUND = 1000;

const string EXAMPLE = "../example.txt";
const string INPUT = "../input.txt";

pair<int, int> find_highest_two(const vector<Monkey>& monkeys);

int main()
{
    cout << "here\n";
    vector<Recipe> recipes = monkey_recipes(EXAMPLE);

    // Original way

    for(int n = 99; n < 1000; n++)
    {
        vector<Monkey> monkeys = get_monkeys(recipes);
        for (int round = 1; round <= ROUND; round++)
        {
            do_keep_away(monkeys);
            for (Monkey &monkey : monkeys)
            {
                int count = 0;
                int item_count = monkey.count_current_item();
                while (count != item_count)
                {
                    count++;
                    Item item = monkey.pick_item();
                    item.set_value(item.get_value() % n);
                    monkey.add_item(item);
                }
            }
            /* if(round % 1000 == 0 || round == 1 ||round == 20) */
            if (round % 1000 == 0 || round == 20)
            /* if (round % 1000 == 0) */
            /* if (round == 20) */
            {
                /* if (round == 1) */
                /* { */
                /*     if (monkeys[0].get_score() != 2) */
                /*         break; */
                /*     if (monkeys[1].get_score() != 4) */
                /*         break; */
                /*     if (monkeys[2].get_score() != 3) */
                /*         break; */
                /*     if (monkeys[3].get_score() != 6) */
                /*         break; */
                /* } */
                if (round == 20)
                {
                    if (monkeys[0].get_score() != 99)
                        break;
                    if (monkeys[1].get_score() != 97)
                        break;
                    if (monkeys[2].get_score() != 8)
                        break;
                    if (monkeys[3].get_score() != 103)
                        break;
                }
                if (round == 1000)
                {
                    if (monkeys[0].get_score() != 5204)
                        break;
                    if (monkeys[1].get_score() != 4792)
                        break;
                    if (monkeys[2].get_score() != 199)
                        break;
                    if (monkeys[3].get_score() != 5192)
                        break;
                }
                cout << "n : " << n << '\n';
                cout << "ROUND : " << round << '\n';
                for (int i = 0; i < monkeys.size(); i++)
                {
                    cout << "Monkey[" << i << "] : " << monkeys[i].get_score() << '\n';
                }
                cout << '\n';
            }
        }
    }

    /* vector<Monkey> monkeys = get_monkeys(recipes); */
    /* for (int round = 1; round <= ROUND; round++) */
    /* { */
    /*     do_keep_away(monkeys); */
    /*     for(Monkey& monkey : monkeys) */
    /*     { */
    /*         int count = 0; */
    /*         int item_count = monkey.count_current_item(); */
    /*         while (count != item_count) */
    /*         { */
    /*             count++; */
    /*             Item item = monkey.pick_item(); */
    /*             item.set_value(item.get_value() % 99); */
    /*             monkey.add_item(item); */
    /*         } */
    /*     } */
    /*     if(round % 1000 == 0 || round == 1 ||round == 20) */
    /*     { */
    /*         cout << "ROUND : " << round << '\n'; */
    /*         for (int i = 0; i < monkeys.size(); i++) */
    /*         { */
    /*             cout << "Monkey[" << i << "] : " << monkeys[i].get_score() << '\n'; */
    /*         } */
    /*         cout << '\n'; */
    /*     } */
    /* } */

    return 0;
}

pair<int, int> find_highest_two(const vector<Monkey>& monkeys)
{
    pair<int, int> winners;
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
