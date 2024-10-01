#include "logic.h"
#include "monkey.h"
#include "worry.h"

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

vector<int> do_keep_away(vector<Monkey>& monkeys, vector<function<void(Item& item)>> relievers)
{
    vector<int> result;

    for(int i = 0; i < monkeys.size(); i++)
    {
        Monkey& monkey = monkeys[i];
        while(monkey.count_current_item() != 0)
        {
            Item item = monkey.pick_item();
            relievers[0](item);
            relievers[1](item);
            monkey.operation(item);
            bool test_result = monkey.Test(item);
            relievers[2](item);
            relievers[3](item);
            item.set_value(item.get_value());
            relievers[4](item);
            relievers[5](item);
            monkey.Throw(test_result, monkeys, item);
        }
    }

    for(int i = 0; i < monkeys.size(); i ++)
    {
        result.push_back(monkeys[i].get_score());
    }
    return result;
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
