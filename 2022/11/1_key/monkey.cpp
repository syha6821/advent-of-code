#include "monkey.h"

int Monkey::KEY_NUM = 1;
const int OLD = -1;

int calc_key(char ch, long x, long y)
{
    long result = 0;
    if (ch == '+') { result =  x + y; }
    else if (ch == '-') { result = x - y; }
    else if (ch == '*') { result =  x * y; }
    else if (ch == '/') { result = x / y; }
    else
    {
        cout << ch << '\n';
        cout << result << '\n';
        error("Illegal value for calculation found in Operation values in calc_key");
        return -1;
    }
    
    if (result >= Monkey::get_key_num())
    {
        return result % Monkey::get_key_num();
    }
    else return result;
}

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
        int r_num = op_pair.second;
        if(r_num == OLD) r_num = item.get_value();
        item.set_value(calc_key(op, item.get_value(), r_num));
    };

    divide_ = [test_num = recipe.get_test()](const Item &item)
    {
        bool test_result = item.get_value() % test_num == 0;
        return test_result;
    };

    pair<int,int> target_monkeys = recipe.get_passed_monkeys_num();
    throw_item_ = [target_monkeys = target_monkeys, op_pair = recipe.get_operation()](bool test_result, vector<Monkey>& monkeys, Item item)
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