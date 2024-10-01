#pragma once
#include "std_lib_facilities.h"
#include "monkey.h"
#include "item.h"
#include "recipe.h"

vector<Monkey> get_monkeys(vector<Recipe> recipes);
vector<Recipe> monkey_recipes(string file_name);
/* void do_keep_away(vector<Monkey>& monkeys); */
vector<int> do_keep_away(vector<Monkey>& monkeys);
pair<int, int> find_highest_two(const vector<Monkey>& monkeys);