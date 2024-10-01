#include "std_lib_facilities.h"

vector<int> factor(int a);
int sum_digits(int num);
long test_long(long num);
int test_int(int num);

int main()
{
    /* long num = 65040L * 65040L; */
    /* long k = 96577; */
    /* long divisor = num / k; */
    /* long q = num % k; */
    /* cout << k * divisor + q << '\n'; */

    /* int a = 9000000; */
    int max = INT32_MAX;
    cout << max << '\n';
    cout << test_int(max) << '\n';
    cout << test_long(max) << '\n';
    return 0;
}

int test_int(int num)
{
    return num + 1;
}

long test_long(long num)
{
    return num + 1;
}

int sum_digits(int num)
{
    const int ASCII = 48;
    int sum = 0;
    string str_int = to_string(num);
    for(char digit : str_int)
    {
        sum += digit - ASCII;
    }
    return sum;

}

vector<int> factor(int a)
{
    vector<int> factors;
    for (int i = 0; i < a; i++)
    {
        if (a % i == 0) factors.push_back(i);
    }
    return factors;
}