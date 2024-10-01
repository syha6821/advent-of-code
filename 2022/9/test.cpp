#include "std_lib_facilities.h"
#include <set>

class A{

};

int main()
{
    A a;
    A b;
    cout << (&a==&b) << '\n';
    return 0;
}