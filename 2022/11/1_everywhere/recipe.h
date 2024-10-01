#pragma once
#include "std_lib_facilities.h"
#include "item.h"
#include "queue"

class Recipe
{
public:
    Recipe(vector<string> input);
    queue<Item> get_items();
    int get_monkey_num();
    pair<char,int> get_operation();
    int get_test();
    pair<int,int> get_passed_monkeys_num();
private:
    string monkey_line;
    string items_line;
    string operation_line;
    string test_line;
    string true_line;
    string false_line;
};