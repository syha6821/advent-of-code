#pragma once

class Item{
public:
    Item(int v):value(v){};
    void set_value(int v) { value = v; };
    int get_value() const { return value; };

    /* Item(double v):value(v){}; */
    /* void set_value(double v) { value = v; }; */
    /* double get_value() const { return value; }; */

private:
    int value;
    /* double value; */
};