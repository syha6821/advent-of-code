#include "rock.h"
#include "chamber.h"
#include <set>
#include <map>
#include <unordered_set>

bool has_full_line(Chamber::WINDOW window)
{
    for(Chamber::SLICE slice : window)
    {
        if(slice.count() == Chamber::WIDTH) return true;
    }
    return false;
}

string HashWindow(Chamber::WINDOW window)
{
    string hashed_window;
    for(int i = 0; i < window.size(); i++)
    {
        hashed_window += to_string(window[i].to_ulong());
    }
    return hashed_window;
}

void drop_rock(vector<Rock> rocks, vector<Jet> jet_pattern, Chamber& chamber, long Round)
{
    long height_before_repeat = 0;
    long rock_count_before_repeat = 0;
    long chunk_height = 0;
    long chunk_count = 0;
    long chunk_rock_count = 0;

    long total_chunks_height = 0;
    long rock_count = 0;
    long jet_count = 0;
    /* set<string> hashed_infos; */
    map<string, pair<int, int>> hashed_infos;
    while(rock_count != Round)
    {
        int rock_num = rock_count % rocks.size();
        Rock rock = rocks[rock_num];
        /* cout << rock << '\n'; */
        chamber.AddAirAboveStack(rock.height());

        //This part is should be repeated. Until rock rests
        long fall_count = 0;
        while(true)
        {
            int jet_num = jet_count % jet_pattern.size();
            Jet jet = jet_pattern[jet_num];

            Chamber::WINDOW before_fall = chamber.window(chamber.height() - fall_count, rock.height());
            jet_count++;
            rock.Move(jet, before_fall);
            fall_count++;
            Chamber::WINDOW after_fall = chamber.window(chamber.height() - fall_count, rock.height());

            if (!rock.Fall(after_fall))
            {
                Chamber::WINDOW replacement = rock.overlapped(before_fall);
                //! In sample, Why this is 51 and different from under ?
                string hashed_info = to_string(rock_num) + ',' + to_string(jet_num) + ',' + HashWindow(replacement) + HashWindow(after_fall);

                pair<string,pair<int,int>> info = make_pair(hashed_info, make_pair(rock_count, chamber.height() - 3 - rock.height()));

                if(not hashed_infos.insert(info).second)
                {
                    cout << "The rock starts repeat : \n" << rocks[rock_count % rocks.size()] << '\n';
                    cout << "The jet starts repeat : \n" << (char)jet_pattern[jet_count % jet_pattern.size()] << '\n';

                    // Height of Chamber excluding paddings If it ends now //*not including this falling rock
                    // ! Should I consider ground height? No
                    int current_height = chamber.height() - 3 - rock.height();
                    // rock count of now falling rock
                    long current_rock_count = rock_count;

                    // Height of Chamber right before the falling pattern starts //! Excluded paddings
                    height_before_repeat = hashed_infos[hashed_info].second;

                    // Rock count before repeat start //? This is not used for calculation
                    rock_count_before_repeat = hashed_infos[hashed_info].first - 1;

                    // How much height would a chunk make 
                    // ! Should I consider ground height? No
                    chunk_height = current_height - height_before_repeat;
                    // number of rocks in a chunk
                    chunk_rock_count = current_rock_count - hashed_infos[hashed_info].first;
                    // How many chunks would be in a whole round
                    chunk_count = (Round - rock_count) / chunk_rock_count;
                    // Remains after whole pattern is finished //? This is not used for calculation
                    long chuck_count_remain = Round - rock_count - chunk_count * chunk_rock_count;

                    total_chunks_height = chunk_height * chunk_count;

                    // Why does minus one make result right at sample?
                    // Why even does minus two make result right at sample?
                    // ! Rock count is problem
                    // Rock count after add all chunks

                    // I think minus one is matters because if these breaks while then if rock_count++ and can't go back to it was
                    // To go back to a as it was
                    /* rock_count = current_rock_count + (chunk_count * chunk_rock_count) - 1; */
                    rock_count = current_rock_count + (chunk_count * chunk_rock_count);
                    /* jet_count--; */
                    
                    cout << "Before : " << current_rock_count % rocks.size() << '\n';
                    cout << "After : " << rock_count % rocks.size() << '\n';
                    
                    cout << "current height : " << current_height << '\n';
                    cout << "current rock count : " << current_rock_count << '\n';
                    cout << "height before repeat : " << height_before_repeat << '\n';
                    cout << "rock count before repeat : " << rock_count_before_repeat << '\n';
                    cout << "chunk height : " << chunk_height << '\n';
                    cout << "chunk rock count : " << chunk_rock_count << '\n';
                    cout << "chunk count : " << chunk_count << '\n';
                    cout << "chunk count remain : " << chuck_count_remain << '\n';
                    cout << "rock count : " << rock_count << '\n';
                    cout << "height : " << total_chunks_height << '\n';

                    hashed_infos.clear();

                    chamber.replace(chamber.height() - fall_count + 1, rock.height(), replacement);
                    chamber.cleanAir();
                    chamber.AddAirAboveStack(3);
                    
                    string str;
                    getline(cin,str);
                    break;
                }

                chamber.replace(chamber.height() - fall_count + 1, rock.height(), replacement);
                chamber.cleanAir();
                chamber.AddAirAboveStack(3);
                break;
            }
        }

        rock_count++;
    }

    cout << "total rock count : " << rock_count << '\n';
    cout << chamber.bottom() << '\n';
    cout << chamber.top() << '\n';
    chamber.cleanAir();
    cout << chamber.SliceAt(chamber.height() - 1) << '\n';
    cout << chamber.height() + total_chunks_height - 1 << '\n';
}