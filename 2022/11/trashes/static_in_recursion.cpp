#include "std_lib_facilities.h"

int test();

int main()
{
    cout << test() << '\n';
    cout << test() << '\n';
    cout << test() << '\n';
    cout << test() << '\n';
    return 0;
}

int test()
{
    static int a = 1;
    a++;
    return a;
}