#include "functions.h"
#include <future>

int find_marker(const string& str)
{
    int SIZE = 14;
    for(int i = SIZE - 1; i < str.size(); i++)
    {
        int sum = 0;
        int or_ = 0;
        int count = SIZE - 1;
        for(int j = i; j > i - SIZE; j--)
        {
            int num = 1<<(str[j] % 32); 
            sum += num;
            or_ |= num;
            if(sum != or_)
            {
                i += count;
                break;
            }
            count--;
        }
        if (sum == or_) return i + 1;
    }
    return -1;
}

vector<pair<int, int>> get_intervals(int size, int count)
{
    vector<pair<int,int>> pairs;
    int interval = size/count;
    int start = 1;
    
    for (int i = 0; i < count - 1; i++)
    {
        pairs.push_back(make_pair(start,start + interval - 1));
        start += interval;
    }
    
    //last with remains
    pairs.push_back(make_pair(start, size));
    
    return pairs;
}

int find_marker_using_threads(const string& str, int threads_count)
{
    int SIZE = 14;
    vector<future<int>> workers;
    auto intervals = get_intervals(str.size(), threads_count);
    for(int i = 0; i < threads_count; i++)
    {
        string str_portion = str.substr(intervals[i].first, intervals[i].second - intervals[i].first + 1);
        //Use move or not?
        workers.push_back(move(async(launch::async,find_marker,str_portion)));
    }
    
    for(int i = 0; i < threads_count; i++)
    {
        int result = workers[i].get();
        if(result != -1) {
            return (intervals[i].first + result);
        }
    }
}