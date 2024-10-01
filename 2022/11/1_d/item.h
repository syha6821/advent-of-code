#pragma once

typedef unsigned long long int ull;

class Item{
public:
    /* Item(int v):value(v){}; */
    /* void set_value(int v) { value = v; }; */
    /* int get_value() const { return value; }; */

    Item(ull v):value(v){};
    void set_value(ull v) { value = v; };
    ull get_value() const { return value; };

private:
    /* int value; */
    ull value;
};