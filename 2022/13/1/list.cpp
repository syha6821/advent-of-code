#include "list.h"
#include "value.h"

List::List(){};
List::List(vector<Value> vls) : values(vls){};
vector<Value> List::get_values() { return values; };
int List::size() { return values.size(); };