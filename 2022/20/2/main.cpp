#include "std_lib_facilities.h"
#include "readfile.h"
#include "num.h"

const long Num::KEY = 811589153;

int main(int argc, char** argv)
{
    string filename = FileName(argc, argv);
    vector<Num> nums = ReadNums(filename);

    for(int i = 0; i < 10; i++)
    {
        for (Num &num : nums)
        {
            Mix(num, nums.size() - 1);
        }
    }

    /* for(Num& num : nums) */
    /* { */
    /*     cout << num << '\n'; */
    /* } */
    
    long sum = 0;

    for(Num& num : nums)
    {
        if(num.value() == 0)
        {
            /* cout << *num.NthNum(1000) << '\n'; */
            /* cout << *num.NthNum(2000) << '\n'; */
            /* cout << *num.NthNum(3000) << '\n'; */

            sum += num.NthNum(1000)->value();
            sum += num.NthNum(2000)->value();
            sum += num.NthNum(3000)->value();
            break;
        }
    }
    cout << "result : " << sum << '\n';

    cout << "end\n";

    return 0;
}