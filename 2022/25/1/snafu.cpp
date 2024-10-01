#include "snafu.h"

char digit_to_snafu(int digit)
{
    switch (digit)
    {
    case 2:
        return '2';
    case 1:
        return '1';
    case 0:
        return '0';
    case -1:
        return '-';
    case -2:
        return '=';
    default:
        error("Invalid digit for digit to snafu");
        return '0';
    }
}

int snafu_digit_value(char digit)
{
    switch (digit)
    {
    case '-':
        return -1;
    case '=':
        return -2;
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    default:
        error("Invalid digit -> " + to_string(digit));
        return 0;
    }
}

long to_dec(string num)
{
    long snafu = 0;
    int count = 0;
    for(int i = num.size() - 1; i >= 0; i--)
    {
        snafu += snafu_digit_value(num[i]) * pow(5, count);
        count++;
    }
    return snafu;
}

long five_round(long num)
{
    int remain = num % 5; 
    int to_add = 5 - remain;
    if(remain >= (5/2) + 1)
    {
        return num + to_add;
    }
    else
    {
        return num - remain;
    }
}

string to_snafu(long num, vector<string> result)
{
    
    long rounded = five_round(num);
    if(num == 0 | num == 1)
    {
        result.push_back(to_string(num));
        string snafu;
        for(int i = result.size() - 1; i >= 0; i--)
        {
            if(i == result.size() - 1 && stoi(result[i]) == 0) continue;
            snafu += digit_to_snafu(stoi(result[i]));
        }
        return snafu;
    }

    result.push_back(to_string(num - rounded));
    long next_num = rounded / 5;

    return to_snafu(next_num, result);
}