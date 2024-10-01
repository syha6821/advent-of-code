#pragma once
#include "std_lib_facilities.h"

class Range
{
public:
    Range(int l, int r):left(l),right(r){};
    int get_left() const { return left; };
    int get_right() const { return right; };
    vector<Range> subtract(Range);
    
private:
    int left;
    int right;
};

ostream &operator<<(ostream &os, const Range &range);

vector<Range> subtract_ranges(const vector<Range>& ranges, Range sub);