#pragma once
#include "std_lib_facilities.h"
#include "monkey.h"
#include "item.h"
#include "recipe.h"
#include "worry.h"

int do_game(int ROUND,vector<Recipe> recipes, vector<Relief> relieves);
bool is_test_round(int round);
const vector<int> answer(int round);
bool test(int round,const vector<Monkey>& monkeys);
vector<Monkey> get_monkeys(vector<Recipe> recipes);
vector<Recipe> monkey_recipes(string file_name);
void do_keep_away(vector<Monkey>& monkeys, vector<Relief> relieves);
pair<int, int> find_highest_two(const vector<Monkey>& monkeys);
void print_result(vector<Monkey> monkeys, int round);