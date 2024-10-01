#pragma once
#include "expr.h"
#include <unordered_map>

class Monkey
{
public:
    Monkey(string name, const Expr& expr):name_(name),expr_(expr){};
    long long yell(const unordered_map<string, Monkey> &monkeys) const;
    string name() const { return name_; };
    const Expr& expr() const { return expr_; };
    string expression(const unordered_map<string, Monkey>& monkeys) const;

private:
    const string name_;
    const Expr expr_;
};