#pragma once
#include "std_lib_facilities.h"
#include "list.h"

enum class ValueType{
   INT, LIST
};

class Value
{
public:
    Value(int val);
    Value(List ls);
    ValueType type();
    List get_list();
    int get_num();

private:
    ValueType value_type;
    int number;
    List list;
};