#include "rock.h"

ostream &operator<<(ostream &stream, const Rock &rock)
{
    /* for(auto slice : rock.sprite_) */
    for(int i = rock.sprite_.size() - 1; i >= 0; i--)
    {
        Rock::SLICE slice = rock.sprite_[i];
        for (int j = slice.size() ; j >= 0; j--)
        {
            if (slice[j] == 1)
            {
                stream << "⬛ ";
            }
            else if (slice[j] == 0)
            {
                stream << "⬜ ";
            }
        }
        stream << '\n';
    }
    /* stream << slice << '\n'; */
    return stream;
}

Rock::SLICE MovedSlice(Rock::SLICE slice, Jet jet)
{
    if (jet == Jet::LEFT)
    {
        slice <<= 1;
    }
    else if (jet == Jet::RIGHT)
    {
        slice >>= 1;
    }
    return slice;
}

Rock::SPRITE Rock::MovedSprite(Jet jet)
{
    SPRITE before = sprite_;
    SPRITE after;
    for(SLICE slice : sprite_)
    {
        SLICE moved_slice = MovedSlice(slice,jet);
        if (slice.count() != moved_slice.count())
        {
            return before;
        }
        else
        {
            after.push_back(moved_slice);
        }
    }
    return after;
}

Chamber::WINDOW overlap(const Rock::SPRITE& sprite, const Chamber::WINDOW& window)
{
    Chamber::WINDOW overlapped;
    if(sprite.size() != window.size()) error("To do overlap, Size of sprite and window must be same");
    for(int i = 0; i < window.size(); i++)
    {
        overlapped.push_back(sprite[i] | window[i]);
    }
    return overlapped;
}

Chamber::WINDOW intersect(const Rock::SPRITE& sprite, const Chamber::WINDOW& window)
{
    Chamber::WINDOW overlapped;
    if(sprite.size() != window.size()) error("To do overlap, size of sprite and window must be same");
    for(int i = 0; i < window.size(); i++)
    {
        overlapped.push_back(sprite[i] ^ window[i]);
    }
    return overlapped;
}

// Not really move, just always compare and move only Rock (not in the window)
void Rock::Move(Jet jet, const Chamber::WINDOW& window)
{
    SPRITE after = MovedSprite(jet);
    if(overlap(after, window) == intersect(after, window))
    {
        sprite_ = after;
    }
}

bool Rock::Fall(const Chamber::WINDOW& target)
{
    if(overlap(sprite_, target) != intersect(sprite_, target))
    {
        return false;
    }
    return true;
}

Chamber::WINDOW Rock::overlapped(const Chamber::WINDOW &window)
{
    /* cout << "before overlapped\n"; */
    /* cout << "sprite\n"; */
    /* for(int i = window.size() - 1; i >= 0 ; i--) */
    /* { */
    /*     cout << sprite_[i] << '\n'; */
    /* } */
    /* cout << "window\n"; */
    /* for(int i = window.size() - 1; i >= 0 ; i--) */
    /* { */
    /*     cout << window[i] << '\n'; */
    /* } */

    Chamber::WINDOW overlapped;
    if(sprite_.size() != window.size()) error("To do overlap, Size of sprite and window must be same");
    for(int i = 0; i < window.size(); i++)
    {
        overlapped.push_back(sprite_[i] | window[i]);
    }
    return overlapped;
}