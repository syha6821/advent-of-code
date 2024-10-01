#include "std_lib_facilities.h"

void test();

int main()
{
    test();
    return 0;
}

void test()
{
    for (int i = 1; i <= 10; i++)
    {
        if (i % 2 == 0)
        {
            cout << i-1 << ' ';
        }
        else
        {
            cout << i+1 << ' ';
        }
    }
    cout << '\n';
}