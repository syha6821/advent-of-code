#pragma once
#include "std_lib_facilities.h"
#include "list.h"
#include "value.h"

class Packet
{
public:
    Packet(string line);
    Packet(string line, int divider_flag);
    List get_list() { return list; };
    vector<Value> get_values() { return list.get_values(); };
    bool is_divider() { return (divider != 0); };
    int which_divider() { return divider; };

private:
    List list;
    int divider = 0;
};