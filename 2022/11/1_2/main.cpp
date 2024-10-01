//cd "/Users/song-yunha/aoc/2022/11/1_2/" && g++ -std=c++14 *.cpp -o main && "/Users/song-yunha/aoc/2022/11/1_2/"main
#include "std_lib_facilities.h"
#include <fstream>
#include "monkey.h"
#include "logic.h"
#include "recipe.h"
#include "worry.h"
#include "mix_match.h"

const string EXAMPLE = "../example.txt";
const string INPUT = "../input.txt";
const int ROUND = 1000;
const int TRY_LIMIT = 5;
bitset<Relief::RELIEF_COUNT> Relief::circuit(0);

int main()
{
    vector<Recipe> recipes = monkey_recipes(EXAMPLE);
    int success = 0;
    vector<pair<char,int>> expr_list = make_list(operators, TRY_LIMIT);
    vector<vector<Relief>> combinations = make_combinations(expr_list, Relief::RELIEF_COUNT);

    for (auto combination : combinations)
    {
        for(int i = 0; i < pow(2, Relief::circuit_size()); i++)
        {
            success += do_game(ROUND, recipes, combination);
            Relief::circuit_increment();
        }
        Relief::reset_circuit();
    }

    if (success == 0)
    {
        cout << "\033[1;31m" << "ALL FAILED" << "\033[0m\n"; 
    }
    else
    {
        cout << "\033[1;34m" << "SUCCESS" << "\033[0m\n"; 
    }

    return 0;
}