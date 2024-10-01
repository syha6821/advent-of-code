#include "std_lib_facilities.h"

unordered_map<char, char> to_rps = {
    {'X','R'},
    {'Y','P'},
    {'Z','S'},
    {'A','R'},
    {'B','P'},
    {'C','S'},
};

int point_by_result(char result)
{
    switch (result)
    {
    case 'w':
        return 6;
    case 'd':
        return 3;
    case 'l':
        return 0;
    }
}

int point_by_pick(char pick)
{
    switch (pick)
    {
    case 'R':
        return 1;
    case 'P':
        return 2;
    case 'S':
        return 3;
    default:
        error("That is not R P S.");
    }
}

char game_result(char my, char op)
{
    int result = point_by_pick(my) - point_by_pick(op);
    if (result == 2 || result == -1) return 'l';
    if (result == 1 || result == -2) return 'w';
    if (result == 0) return 'd';
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
        my_pick = to_rps[game[2]];
        point += point_by_pick(my_pick) + point_by_result(game_result(my_pick,op_pick));
    }
    input.close();
    cout << point << '\n';
    return 0;
}