#pragma once
#include "std_lib_facilities.h"
#include <unordered_map>

class Expr
{
public:
    Expr(vector<string> expr):expr_(expr){};

    bool is_num() const { return expr_.size() == 1; };
    long num() const { return stol(expr_.at(0)); };
    
    bool is_human() const { return expr_.at(0) == "h"; };

    string left() const { return expr_.at(0); };
    char op() const { return expr_.at(1)[0]; };
    string right() const { return expr_.at(2); };

private:
    vector<string> expr_;
};