#include "recipe.h"
#include <queue>
typedef unsigned long long int ull;

Recipe::Recipe(vector<string> input)
{
    monkey_line = input[0];
    items_line = input[1];
    operation_line = input[2];
    test_line = input[3];
    true_line = input[4];
    false_line = input[5];
}

string string_after_word(string str,string word)
{
    int index_of_after_word = str.find(word) + word.size();
    return str.substr(index_of_after_word);
}

int Recipe::get_monkey_num()
{
    stringstream line (string_after_word(monkey_line," "));
    int num;
    line >> num;
    return num;
}

queue<Item> Recipe::get_items()
{
    queue<Item> items;
    stringstream line (string_after_word(items_line,":"));
    ull num = 0;
    string delimeter;
    while(line >> num)
    {
        items.push(Item(num));
        line >> delimeter;
    }
    return items;
}

pair<char, int> Recipe::get_operation()
{
    stringstream line (string_after_word(operation_line,"old"));
    char op;
    line >> op;
    string num_str;
    line >> num_str;
    int num;
    line >> num;
    if(num_str == "old") num = -1;
    else num = stoi(num_str);
    return make_pair(op, num);
}

int Recipe::get_test()
{
    stringstream line (string_after_word(test_line,"by"));
    int num;
    line >> num;
    return num;
}

pair<int, int> Recipe::get_passed_monkeys_num()
{
    stringstream line (string_after_word(true_line,"monkey"));
    int true_num;
    line >> true_num;
    stringstream line2 (string_after_word(false_line,"monkey"));
    int false_num;
    line2 >> false_num;
    return make_pair(true_num, false_num);
}