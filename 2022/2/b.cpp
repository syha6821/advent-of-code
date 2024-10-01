#include "std_lib_facilities.h"

unordered_map<char, char> to_rps = {
    {'X','R'},
    {'Y','P'},
    {'Z','S'},
    {'A','R'},
    {'B','P'},
    {'C','S'},
};

unordered_map<char,int> point_by_result = {
    {'w',6},
    {'d',3},
    {'l',0},
};

unordered_map<char,int> point_by_pick = {
    {'R',1},
    {'P',2},
    {'S',3},
};

char game_result(char my, char op)
{
    int result = point_by_pick[my] - point_by_pick[op];
    if (result == 2 || result == -1) return 'l';
    if (result == 1 || result == -2) return 'w';
    if (result == 0) return 'd';
}

unordered_map<char,char> win_pick = {
    {'R','P'},
    {'P','S'},
    {'S','R'},
};

unordered_map<char,char> lose_pick = {
    {'R','S'},
    {'P','R'},
    {'S','P'},
};

char my_pick_by_strategy(char op, char wanted_result)
{
    if (wanted_result == 'X')//Lose
        {
            return lose_pick[op];
        }
    if (wanted_result == 'Y')//Draw
        {
            return op;
        }
    if (wanted_result == 'Z')//Win
        {
            return win_pick[op];
        }
}

int main()
{
    ifstream input;
    input.open("input.txt");
    
    string game;
    char my_pick;
    char op_pick;
    int point = 0;
    while(getline(input,game))
    {
        op_pick = to_rps[game[0]];
        my_pick = my_pick_by_strategy(op_pick, game[2]);
        point += point_by_pick[my_pick] + point_by_result[game_result(my_pick,op_pick)];
    }
    input.close();
    cout << point << '\n';
    return 0;
}