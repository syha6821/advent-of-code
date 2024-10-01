#include "std_lib_facilities.h"
#include "readfile.h"
#include "snafu.h"
#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    const string FILENAME = FileName(argc, argv);

    vector<string> snafus = ReadSnafus(FILENAME);
    long sum = 0;

    for(string snafu : snafus)
    {
        sum += to_dec(snafu);
    }

    cout << sum << '\n';
    cout << to_snafu(sum) << '\n';

    return 0;
}
