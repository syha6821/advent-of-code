#include "rock.h"
#include "chamber.h"

int has_full_line(Chamber::WINDOW window)
{
    for(int i = 0; i < window.size(); i++)
    {
        if(window[i].count() == Chamber::WIDTH)
        {
            return i;
        }
    }
    return false;
}

void drop_rock(vector<Rock> rocks, vector<Jet> jet_pattern, Chamber& chamber, long Round)
{
    int height = 0;
    long rock_count = 0;
    long jet_count = 0;
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

            if(rock_num == 0 && jet_num == 0)
            {
                cout << "reset : " << rock_count << '\n';
            }

            Chamber::WINDOW before_fall = chamber.window(chamber.height() - fall_count, rock.height());
            jet_count++;
            rock.Move(jet, before_fall);
            fall_count++;
            Chamber::WINDOW after_fall = chamber.window(chamber.height() - fall_count, rock.height());

            if (! rock.Fall(after_fall)) // If fail stop and goto next round.
            {
                Chamber::WINDOW replacement = rock.overlapped(before_fall);

                int full_line_index = has_full_line(replacement);
                if(rock_count == Round - 1)
                {
                    height += chamber.height() - 3;
                    break;
                }
                if(full_line_index && (rock_count != Round - 1))
                {
                    height += chamber.height() - 3;
                    chamber.ClearStack();
                    chamber.AddWindow(replacement);
                    chamber.cleanAir();
                    chamber.AddAirAboveStack(3);
                    /* cout << "It has black line\n"; */
                    break;
                }

                chamber.replace(chamber.height() - fall_count + 1, rock.height(), replacement);
                chamber.cleanAir();
                chamber.AddAirAboveStack(3);
                break;
            }
        }

        rock_count++;
        /* cout << chamber << '\n'; */
        /* string enter; */
        /* getline(cin, enter); */
        if (rock_count % 100000 == 0) cout << rock_count << '\n';
    }
    /* cout << chamber << '\n'; */
    /* cout << chamber.height() - 3 - 1 << '\n'; */
    cout << height << '\n';
}
