#include "std_lib_facilities.h"

int main()
{
    ifstream input_file;
    input_file.open("input.txt");
    
    string each;
    int most = 0;
    int current = 0;
    int tops[3];
    while(getline(input_file, each))
    {
        if (each == "")
        {
            if (current > tops[0])
            {
                tops[0] = (current > tops[0]) ? current : most;
                sort(begin(tops), end(tops));
            }
            current = 0;
        }
        else current += stoi(each);
    }
    
    int sum = 0;
    for (int top : tops)
    {
        sum += top;
    }
    cout << sum << '\n';
}