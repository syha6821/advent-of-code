#pragma once
#include "std_lib_facilities.h"

enum class Pattern
{
    Up, Down,
};

int CalcPattern(vector<Pattern> patterns);
int FindFirstCausingBase(vector<Pattern> patterns);
