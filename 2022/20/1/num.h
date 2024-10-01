#pragma once
#include "std_lib_facilities.h"

class Num
{
public:
    Num(int num):num_(num){};
    int value() const { return num_; };
    friend void MakeLink(vector<Num> &nums);
    Num* head() { return head_; };
    Num* tail() { return tail_; };
    friend void Mix(Num& num);
    friend ostream &operator<<(ostream &stream, const Num &num);
    friend Num* Ahead(Num &num);
    Num* NthNum(int n);

private:
    Num* head_;
    Num* tail_;
    int num_;
};