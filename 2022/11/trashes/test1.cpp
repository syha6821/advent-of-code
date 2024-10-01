#include "std_lib_facilities.h"
#include <map>

int sum_of_digit(int);

const vector<int> mul_value = {9,8,19,7,5,8};
int mod_(int divisor);
int sum_digits_of_num(int num);

int main()
{
    cout << sum_digits_of_num(123) << '\n';
}

int sum_digits_of_num(int num)
{
    int sum = 0;
    string num_str = to_string(num);
    for (char ch : num_str)
    {
        sum += ch - 48;
    }
    return sum;
}


int sum_of_digit(int i)
{
    const int ASCII = 48;
    int sum = 0;
    string str_int = to_string(i);
    for(char ch : str_int)
    {
        sum += ch - ASCII;
    }
    return sum;
}

int mod_(int divisor)
{
    int tmp_sum = mul_value[0];
    for (int i = 1; i < mul_value.size(); i++)
    {
        tmp_sum = (tmp_sum * mul_value[i]) % divisor;
    }

    return tmp_sum;
}