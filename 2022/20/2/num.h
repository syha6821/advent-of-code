#pragma once
#include "std_lib_facilities.h"

class Num
{
public:
    const static long KEY;

    Num(long num):num_(num * KEY){};
    long value() const { return num_; };
    friend void MakeLink(vector<Num> &nums);
    Num* head() { return head_; };
    Num* tail() { return tail_; };
    friend void Mix(Num& num, int size);
    friend ostream &operator<<(ostream &stream, const Num &num);
    friend Num* Ahead(Num &num, int size);
    Num* NthNum(int n);
    long essence(long size) { return num_ % size; };

private:
    Num* head_;
    Num* tail_;
    long num_;
};