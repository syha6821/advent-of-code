#include "pattern.h"

int CalcPattern(vector<Pattern> patterns)
{
    int result = 0;
    for(Pattern pattern : patterns)
    {
        if(pattern == Pattern::Up)
        {
            result += 1;
        }
        else if(pattern == Pattern::Down)
        {
            result -= 1;
        }
    }
    return result;
}

int FindFirstCausingBase(vector<Pattern> patterns)
{
    int count = 0;
    int result = 0;
    for(Pattern pattern : patterns)
    {
        count++;
        if(pattern == Pattern::Up)
        {
            result += 1;
        }
        else if(pattern == Pattern::Down)
        {
            result -= 1;
        }
        if(result < 0)
        {
            return count;
        }
    }

}
