//cd "/Users/song-yunha/aoc/2022/9/1/" && g++ -std=c++14 *.cpp -o a && "/Users/song-yunha/aoc/2022/9/1/"a
#include "pos.h"
#include <set>

const string SAMPLE = "../test_sample.txt";
const string INPUT = "../input.txt";

int do_recipe(const string& recipe)
{
    set<string> history;
    Pos H;
    vector<Pos> tails(9);
    Pos T;
    history.insert(H.hash());
    ifstream ifs;
    ifs.open(recipe);
    char cmd;
    int num;
    while(ifs>>cmd)
    {
        ifs >> num;
        for(int i = 0; i < num; i++)
        {
            H.do_command(cmd);
            T.follow(H);
            history.insert(std::move(T.hash()));
        }
    }
    return history.size();
}

int main()
{
    /* cout << do_recipe(SAMPLE) << '\n'; */
    cout << do_recipe(INPUT) << '\n';
    return 0;
}