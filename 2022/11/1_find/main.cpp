//cd "/Users/song-yunha/aoc/2022/11/1_find/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/11/1_find/"main
#include "std_lib_facilities.h"
#include <fstream>
#include "monkey.h"
#include "logic.h"
#include "recipe.h"
#include "worry.h"
#include "answer.h"

const int ROUND = 1000;

const string EXAMPLE = "../example.txt";
const string INPUT = "../input.txt";

int main()
{
    vector<Recipe> recipes = monkey_recipes(EXAMPLE);

    vector<Monkey> monkeys = get_monkeys(recipes);
    vector<vector<pair<char, int>>> combs = mix_and_match(worry_ops, 100, 6);
    find_comb(ROUND, monkeys, combs);
    
    return 0;
}

vector<function<void(Item& item)>> make_relievers(vector<pair<char, int>> combs)
{
    vector<function<void(Item& item)>> relievers;
    for(pair<char, int> comb : combs)
    {
        relievers.push_back([comb = comb](Item& item){
                item.set_value(calc(comb.first, item.get_value(), comb.second));
        });
    }
    return relievers;
}

vector<vector<pair<char, int>>> mix_and_match(vector<char> try_ops, int try_numbers, int pair_count)
{
    vector<vector<pair<char, int>>> combinations;
    

    return combinations;
}

void find_comb(int round, vector<Monkey> monkeys, vector<vector<pair<char, int>>> relieves)
{
    for (int round = 1; round <= ROUND; round++)
    {
        vector<int> result = do_keep_away(monkeys);
        if(round == round_to_compare.front())
        {
            if (check(result , answer, round))
            {
                round_to_compare.pop();
            }
            else
            {
                return;
            }
        }
    }
    
    // If passed above rules;
    cout << "New rules" << '\n';
    for(pair<char,int> relief : relieves)
    {
        cout << relief.first << relief.second << '\n';
    }
}