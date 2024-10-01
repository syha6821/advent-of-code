#include "value.h"

Value::Value(int val) : number(val), value_type(ValueType::INT){};

Value::Value(List ls) : list(ls), value_type(ValueType::LIST){};

ValueType Value::type() { return value_type; };

List Value::get_list()
{
    if (value_type != ValueType::LIST)
        error("This value is not a List");
    return list;
};

int Value::get_num()
{
    if (value_type != ValueType::INT)
        error("This value is not a Integer");
    return number;
};