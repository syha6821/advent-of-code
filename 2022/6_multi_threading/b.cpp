#include "std_lib_facilities.h"
#include <thread>
#include <future>
#include <deque>

class Tt{
public:
    Tt(){ cout << this << " constructed\n"; };
    Tt(const Tt& tt) {cout << this << " copying from " << &tt << '\n';};
    ~Tt() { cout << this << " destructed\n"; };
};

int main()
{
    Tt tt;
    cout << "addr in main: " << &tt << '\n';
    vector<Tt> tts;
    tts.push_back(tt);
    /* tts.push_back(std::move(tt)); */
    /* tts.push_back(Tt()); */
    /* tts.push_back(std::move(Tt())); */
    cout << "addr in vec: " << &tts[0] << '\n';
    cout << "last line\n";

    return 0;
}

/* auto func = []{this_thread::sleep_for(chrono::seconds(2));}; */
/* vector<future<void>> workers; */
/* workers.push_back(move(async(launch::async, func))); */
/* workers.push_back(move(async(launch::async, func))); */
/* workers.push_back(move(async(launch::async, func))); */