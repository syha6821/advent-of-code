#include "logic.h"
#include "monkey.h"

void do_keep_away(vector<Monkey>& monkeys)
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
    int key_num = 1;
    for(Recipe recipe : recipes)
    {
        key_num *= recipe.get_test();
        cout << "get_test : " << recipe.get_test() << '\n';
        monkeys.push_back(Monkey(recipe));
    }
    Monkey::set_key_num(key_num);
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
