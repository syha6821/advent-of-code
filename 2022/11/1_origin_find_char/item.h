#pragma once

class Item{
public:
    Item(int v):value(v){};
    void set_value(int v) { value = v; };
    int get_value() const { return value; };

private:
    int value;
};