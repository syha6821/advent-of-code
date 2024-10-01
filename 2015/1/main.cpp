#include "std_lib_facilities.h"
#include "readfile.h"
#include "pattern.h"
#include <iostream>

int main(int argc, char** argv)
{
    const string FILENAME = FileName(argc, argv);
    const vector<Pattern> patterns = ReadPattern(FILENAME);
    const int result = CalcPattern(patterns);

    cout << FILENAME << '\n';
    cout << "Result : " << result << '\n';
    cout << "Part2 : " << FindFirstCausingBase(patterns) << '\n';

    return 0;
}
