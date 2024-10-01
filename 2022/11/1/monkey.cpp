#include "monkey.h"

int Monkey::KEY_NUM = 1;

int calc(char ch, int x, int y)
{
    if (ch == '+') return x + y;
    if (ch == '-') return x - y;
    if (ch == '*') return x * y;
    if (ch == '/') return x / y;
    if (ch == '%') return x % y;
    else
    {
        error("Illegal value for calculation found in Operation values");
        return -1;
    }
}

Item Monkey::pick_item()
{
    Item item = items.front();
    if (!items.empty()) items.pop();
    return item;
}

Monkey::Monkey(Recipe recipe)
{
    items = std::move(recipe.get_items());
    pair<char,int> op_pair = recipe.get_operation();

    operate_ = [op_pair = recipe.get_operation()](Item& item)
    {
        char op = op_pair.first;
        int num = op_pair.second;
        int result;

        if (op == '*')
        {
            if (num == OLD)
            {
                vector<int> old_values = item.get_mul_value_list();
                item.append_vector_to_mul(old_values);
            }
            else
            {
                item.mul_add_value(num);
            }
        }
        if (op == '+')
        {
            item.plus_add_value(num);
        }
    };

    divide_ = [test_num = recipe.get_test()](const Item& item) -> bool
    {
        int m = item.mod_(test_num);
        if ((m + item.get_plus_value()) % test_num == 0) return true;
        return false;
    };

    pair<int,int> target_monkeys = recipe.get_passed_monkeys_num();
    throw_item_ = [target_monkeys = target_monkeys](bool test_result, vector<Monkey>& monkeys, Item item)
    {
        if(test_result)
        {
            monkeys[target_monkeys.first].add_item(item);
        }
        else
        {
            monkeys[target_monkeys.second].add_item(item);
        }
    };
}

void Monkey::add_item(Item item)
{
    items.push(item);
}