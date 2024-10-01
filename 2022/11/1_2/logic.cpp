#include "logic.h"
#include "monkey.h"
#include <map>

int do_game(int ROUND,vector<Recipe> recipes, vector<Relief> relieves)
{
    vector<Monkey> monkeys = get_monkeys(recipes);
    for (int round = 1; round <= ROUND; round++)
    {
        do_keep_away(monkeys, relieves);
        if(is_test_round(round))
        {
            if(!test(round, monkeys)) return 0;
        }
    }
    cout << "=========================\n";
    for (Relief reliever : relieves)
    {
        cout << "\033[1;34m" << "FOUND : " << reliever.get_op() << reliever.get_divisor() << "\033[0m\n"; 
    }
    cout << "=========================\n";
    return 1;
}

bool is_test_round(int round)
{
    return (round == 1 || round == 20 || round == 1000 || round == 2000);
}

const vector<int> answer(int round)
{
    map<int, vector<int>> ans = 
    {
        {1, {2,4,3,6}},
        {20, {99,97,8,103}},
        {1000, {5204,4792,199,5192}},
        {2000, {10419,9577,392,10391}},
    };

    return ans[round];
}

bool test(int round,const vector<Monkey>& monkeys)
{
    vector<int> result;
    for (Monkey monkey : monkeys)
    {
        result.push_back(monkey.get_score());
    }
    
    bool is_success = (result == answer(round));
    return is_success;
}

void do_keep_away(vector<Monkey>& monkeys, vector<Relief> relieves)
{
    for(int i = 0; i < monkeys.size(); i++)
    {
        Monkey& monkey = monkeys[i];
        while(monkey.count_current_item() != 0)
        {
            Item item = monkey.pick_item();
            monkey.operation(item);
            bool test_result = monkey.Test(item);
            monkey.Throw(test_result, monkeys, item);
        }
    }
}

vector<Monkey> get_monkeys(vector<Recipe> recipes)
{
    vector<Monkey> monkeys;
    for(Recipe recipe : recipes)
    {
        monkeys.push_back(Monkey(recipe));
    }
    return monkeys;
}

vector<Recipe> monkey_recipes(string file_name)
{
    const int RECIPE_LINE_COUNT = 6;
    vector<Recipe> recipes;

    ifstream ifs;
    ifs.open(file_name);

    string line;
    int line_count = 0;

    vector<string> recipe_lines;
    while(getline(ifs,line))
    {
        if(line.empty()) continue;
        line_count++;
        recipe_lines.push_back(line);

        if(line_count % RECIPE_LINE_COUNT == 0)
        {
            recipes.push_back(std::move(Recipe(recipe_lines)));
            recipe_lines.clear();
        }
    }
    return recipes;
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

void print_result(vector<Monkey> monkeys, int round)
{
    cout << "-------score-------\n";
    
    vector<int> ans = answer(round);

    for (int i = 0; i < monkeys.size(); i++)
    {
        cout << "      " << monkeys[i].get_score() << '(' << ans[i] << ')'<< '\n';
    }

    cout << "-------winner-------\n";

    pair<int, int> winners = find_highest_two(monkeys);
    cout << '\t' << winners.first << '\n';
    cout << '\t' << winners.second << '\n';

    cout << "------business------\n";
    cout << '\t' << (long int)(winners.first) * (long int)(winners.second) << '\n';
}