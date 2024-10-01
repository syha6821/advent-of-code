#include "range.h"

vector<Range> Range::subtract(Range sub)
{
    if((sub.get_right() < left) || (sub.get_left() > right)) // Not included at all
    {
        return {Range(left, right)};
    }
    if(sub.get_left() > left && sub.get_right() < right) // Included in original
    {
        return {Range(left, sub.get_left() - 1), Range(sub.get_right() + 1, right)};
    }
    if(sub.get_left() <= left && sub.get_right() >= right) // sub is larger than original
    {
        return {};
    }
    if((sub.get_left() > left && sub.get_left() <= right) && sub.get_right() >= right) // over right
    {
        return {Range(left, sub.get_left() - 1)};
    }
    if(sub.get_left() <= left && (sub.get_right() < right && sub.get_right() >= left)) // over left
    {
        return {Range(sub.get_right() + 1, right)};
    }
    
    cout << "problem at this : " << this->get_left() << ',' << this->get_right() << " and sub : " << sub.get_left() << ',' << sub.get_right() << '\n';
}

ostream &operator<<(ostream &os, const Range &range)
{
    os << '(' << range.get_left() << " ~ " << range.get_right() << ')';
    return os;
}

vector<Range> subtract_ranges(const vector<Range>& ranges, Range sub)
{
    vector<Range> subbed_ranges;
    for(Range range : ranges)
    {
        for(Range subbed_range : range.subtract(sub))
        {
            subbed_ranges.push_back(subbed_range);
        }
    }
    return subbed_ranges;
}