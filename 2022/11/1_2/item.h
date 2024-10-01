#pragma once

class Item{
public:
    Item(int v) : worry_level(v){};
    int get_worry_level() const { return worry_level; };
    void set_worry_level(int v) { worry_level = v; };

private:
    int worry_level = 0;
};