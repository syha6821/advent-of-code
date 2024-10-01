#include "std_lib_facilities.h"

unordered_map<char, int> my = {
    {'X',1},
    {'Y',2},
    {'Z',3},
};

int game_result(char my, char op)
{
    if(my - op == 23)
    {
        return 3;
    }
    switch (my)
    {
    case 'X': //Rock
        if (op == 'B') return 0; // Paper
        if (op == 'C') return 6; // Scissor
        break;

    case 'Y': // Paper
        if (op == 'A') return 6; // Rock
        if (op == 'C') return 0; // Scissor
        break;

    case 'Z': // Scissor
        if (op == 'A') return 0; // Rock
        if (op == 'B') return 6; // Paper
        break;
    
    default:
        break;
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
    int count = 0;
    while(getline(input,game))
    {
        count ++;
        op_pick = game[0];
        my_pick = game[2];
        point += my[my_pick] + game_result(my_pick,op_pick);
        cout << op_pick << ' ' << my_pick << ':' << my[my_pick] + game_result(my_pick,op_pick) << '\n';
    }
    input.close();
    cout << point << '\n';
    cout << count << '\n';
    return 0;
}