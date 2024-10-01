#pragma once
#include "std_lib_facilities.h"

class Value;

class List
{
public:
    List();
    List(vector<Value> vls);
    vector<Value> get_values();
    int size();

private:
    vector<Value> values;
};