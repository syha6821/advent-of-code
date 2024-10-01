#include "std_lib_facilities.h"
#include "readfile.h"
#include "num.h"

int main(int argc, char** argv)
{
    string filename = FileName(argc, argv);
    vector<Num> nums = ReadNums(filename);

    Num& start_zero = nums[0];

    for(Num& num : nums)
    {
        Mix(num);
    }
    
    /* for(Num& num : nums) */
    /* { */
    /*     cout << num << '\n'; */
    /* } */

    for(Num& num : nums)
    {
        if(num.value() == 0)
        {
            cout << *num.NthNum(1000) << '\n';
            cout << *num.NthNum(2000) << '\n';
            cout << *num.NthNum(3000) << '\n';
            break;
        }
    }

    cout << "end\n";

    return 0;
}