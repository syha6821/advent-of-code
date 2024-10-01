//cd "/Users/song-yunha/aoc/2022/9/1/" && g++ -std=c++14 *.cpp -o a && "/Users/song-yunha/aoc/2022/9/1/"a
#include "pos.h"
#include <set>

const string SAMPLE = "../test_sample.txt";
const string SAMPLE2 = "../test_sample_2.txt";
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
            if(i == 0) cout << cmd << ':' << num << '\n';
            H.do_command(cmd);

            cout << "H : " << H << '\n';
            
            tails[0].follow(H);
            cout << 'T' << '[' << '0' << ']' << tails[0] << '\n';
            for(int j = 1; j < tails.size(); j++)
            {
                /* tails[j].follow(tails[j-1]); */
                tails[j].follow(tails[j-1]);
                cout << 'T' << '[' << j << ']' << tails[j] << '\n';
                if(j == tails.size() - 1) history.insert(std::move(tails[j].hash()));
            }
            cout << '\n';
        }
    }
    return history.size();
}

int main()
{
    /* cout << do_recipe(SAMPLE) << '\n'; */
    /* cout << do_recipe(SAMPLE2) << '\n'; */
    cout << do_recipe(INPUT) << '\n';
    return 0;
}

//! after U8 the last one should remain at start
/* H : (5,8) */
/* T[0](5,7) */
/* T[1](5,6) */
/* T[2](5,5) */
/* T[3](5,4) */
/* T[4](5,3) */ //!
/* T[5](5,2) */ //!
/* T[6](5,1) */ //!
/* T[7](4,0) */
/* T[8](3,0) */
