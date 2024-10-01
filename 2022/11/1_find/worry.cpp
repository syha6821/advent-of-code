#include "worry.h"

void relief_worry(Item& item, char op, int operands)
{
    item.set_value(calc(op, item.get_value(), operands));
}