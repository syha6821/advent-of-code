#pragma once
#include "std_lib_facilities.h"
#include <queue>
#include "item.h"
#include "recipe.h"

int calc(char ch, int x, int y);

class Monkey{
public:
    Monkey(Recipe recipe);
    void add_item(Item item);
    Item pick_item();
    int get_score() const { return score; };
    int count_current_item(){ return items.size(); };
    void operation(Item& item)
    {
        operate_(item);
        score++;
    };
    bool Test(const Item& item) { return divide_(item); };
    void Throw(bool test_result, vector<Monkey>& monkeys,Item item)
    {
        throw_item_(test_result,monkeys,item);
    };
    static int get_key_num() { return KEY_NUM; }
    static void set_key_num(int num) { KEY_NUM = num; }

private:
    static int KEY_NUM;
    queue<Item> items;
    int score = 0;
    function<void(Item&)> operate_;
    function<bool(const Item&)> divide_;
    function<void(bool,vector<Monkey>&,Item)> throw_item_;

};
