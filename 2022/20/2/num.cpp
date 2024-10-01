#include "num.h"

void MakeLink(vector<Num>& nums)
{
    nums[0].head_ = &(nums[1]);
    nums[0].tail_ = &(nums.back());

    nums.back().head_ = &(nums[0]);
    nums.back().tail_ = &(nums[nums.size() - 2]);

    for(int i = 1; i < nums.size() - 1; i++)
    {
        nums[i].head_ = &nums[i + 1];
        nums[i].tail_ = &nums[i - 1];
    }
}

Num* Ahead(Num& num, int size)
{
    Num* next_num = &num;
    if(num.value() > 0)
    {
        for(long i = 0;  i <= num.essence(size); i++)
        {
            next_num = next_num->head_;
        }
    }
    else if(num.value() < 0)
    {
        for(long i = 0;  i >= num.essence(size); i--)
        {
            next_num = next_num->tail_;
        }
    }
    return next_num;
}

Num* Num::NthNum(int n)
{
    Num* next_num = this;
    for (long i = 0; i < n; i++)
    {
        next_num = next_num->head_;
    }
    return next_num;
}

void Mix(Num& num, int size)
{
    if(num.value() == 0) return;

    num.head_->tail_ = num.tail_;
    num.tail_->head_ = num.head_;

    Num* ahead = Ahead(num, size);

    if(num.value() > 0)
    {
        ahead->tail_->head_ = &num;
        num.head_ = ahead;
        num.tail_ = ahead->tail_;
        ahead->tail_ = &num;
    }

    if(num.value() < 0)
    {
        ahead->head_->tail_ = &num;
        num.tail_ = ahead;
        num.head_ = ahead->head_;
        ahead->head_ = &num;
    }

}

ostream &operator<<(ostream &stream, const Num &num)
{
    stream << num.tail_->value() << " -> " << num.value() << " -> " << num.head_->value();
    return stream;
}