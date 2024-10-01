#include "monkey.h"
typedef unsigned long long int ull;

ull calc(char ch, ull x, ull y)
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

        /* if (num == -1) item.set_value(calc(op, item.get_value(), item.get_value())/worry_level); */
        /* else item.set_value(calc(op, item.get_value(), num)/worry_level); */
        
        //no relief after inspect
        if (num == -1) item.set_value(calc(op, item.get_value(), item.get_value()));
        else item.set_value(calc(op, item.get_value(), num));

    };
    
    divide_ = [test_num = recipe.get_test()](const Item& item)
    {
        return (item.get_value() % test_num) == 0;
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