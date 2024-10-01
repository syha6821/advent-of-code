#include "std_lib_facilities.h"
#include <bitset>

int main()
{
    bitset<6> a(8);
    a = 0b110101;
    cout << a << '\n';
    return 0;
}