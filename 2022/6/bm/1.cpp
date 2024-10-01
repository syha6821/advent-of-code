#include "1.h"

int find_marker1(const string& str)
{
    for(int i = 0; i < str.size(); i++)
    {
        set<char> s;
        for(int j = 0; j < 4; j++)
        {
            s.insert(str[i+j]);
        }
        if (s.size() == 4) return i+4;
    }
    return -1;
}

int find_marker1_14(const string& str)
{
    for(int i = 0; i < str.size(); i++)
    {
        set<char> s;
        for(int j = 0; j < 14; j++)
        {
            s.insert(str[i+j]);
        }
        if (s.size() == 14) return i+14;
    }
    return -1;
}

int find_marker1_u(const string& str)
{
    for(int i = 0; i < str.size(); i++)
    {
        unordered_set<char> s;
        for(int j = 0; j < 4; j++)
        {
            s.insert(str[i+j]);
        }
        if (s.size() == 4) return i+4;
    }
    return -1;
}

int find_marker1_u_14(const string& str)
{
    for(int i = 0; i < str.size(); i++)
    {
        unordered_set<char> s;
        for(int j = 0; j < 14; j++)
        {
            s.insert(str[i+j]);
        }
        if (s.size() == 14) return i+14;
    }
    return -1;
}

int find_marker11(const string& str)
{
    string tmp = str.substr(0,4);
    set<char> s;
    for (char ch : tmp) s.insert(ch);
    if(s.size() == 4) return 4;

    for(int i = 4; i < str.size(); i++)
    {
        tmp.erase(tmp.begin());
        tmp.push_back(str[i]);
        set<char> s;
        for (char ch : tmp) s.insert(ch);
        if(s.size() == 4) return i + 1;
    }
    return -1;
}

int find_marker11_2(const string& str)
{
    const int SIZE = 4;
    int count = 0;
    for(auto it = str.begin(); it != str.end() - (SIZE - 1); it++)
    {
        set<char> s;
        for_each(it, it + 4, [&s](char ch) { s.insert(ch); });
        if(s.size() == 4) return count + 4;
        count++;
    }
    return 0;
}

int find_marker2(const string& str)
{
    char back;
    for(int i = 4; i < str.size(); i++)
    {
        if (back == str[i])
        {
            i += 2;
            continue;
        }
        set<char> s;
        for(int j = i-4; j < i; j++)
        {
            s.insert(str[j]);
            back = str[i-1];
        }
        if (s.size() == 4) return i;
    }
    return -1;
}

int find_marker3(const string& str)
{
    char back;
    for(int i = 4; i < str.size(); i++)
    {
        if (back == str[i])
        {
            i += 2;
            continue;
        }
        if (str[i-2] == str[i])
        {
            i += 1;
            continue;
        }
        set<char> s;
        for(int j = i-4; j < i; j++)
        {
            s.insert(str[j]);
            back = str[i-1];
        }
        if (s.size() == 4) return i;
    }
    return -1;
}

int find_marker4(const string& str)
{
    char back;
    for(int i = 4; i < str.size(); i++)
    {
        if (back == str[i])
        {
            i += 2;
            continue;
        }
        if (str[i-2] == str[i])
        {
            i += 1;
            continue;
        }

        if (str[i-3]==str[i])
            continue;

        set<char> s;
        for(int j = i-4; j < i; j++)
        {
            s.insert(str[j]);
            back = str[i-1];
        }
        if (s.size() == 4) return i;
    }
    return -1;
}

int find_marker4_2(const string& str)
{
    constexpr int SIZE = 4;
    for(int i = 0; i < str.size() - SIZE + 1; i++)
    {
        const string word = str.substr(i,SIZE);
        for (int j = 0; j < word.size() - 1; j++)
        {
            char comparee = word[j];
            for (int k = j + 1; k < word.size(); k++)
            {
                if (comparee == word[k])
                {
                    i += j;
                    j = word.size();
                    k = word.size();
                    continue;
                }
            }
            if (j == word.size() - 2)
            {
                return i + SIZE;
            }
        }
    }
    return -1;
}

int find_marker4_2_14(const string& str)
{
    constexpr int SIZE = 14;
    for(int i = 0; i < str.size() - SIZE + 1; i++)
    {
        const string word = str.substr(i,SIZE);
        for (int j = 0; j < word.size() - 1; j++)
        {
            char comparee = word[j];
            for (int k = j + 1; k < word.size(); k++)
            {
                if (comparee == word[k])
                {
                    i += j;
                    j = word.size();
                    k = word.size();
                    continue;
                }
            }
            if (j == word.size() - 2)
            {
                return i + SIZE;
            }
        }
    }
    return -1;
}

int find_marker4_21(const string& str)
{
    constexpr int SIZE = 4;
    for(int i = 0; i < str.size() - SIZE + 1; i++)
    {
        const int compare_start = i + 1;
        for (int j = i; j < i + SIZE - 1; j++) //It represents word (except last char)
        {
            char comparee = str[j];
            for (int k = j + 1; k < compare_start + SIZE - 1; k++) // chars after comparees
            {
                if (comparee == str[k])
                {
                    i = j;
                    j = i + SIZE - 1;
                    k = compare_start + SIZE - 1;
                }
            }
            if (j == i + SIZE - 2)
            {
                return i + SIZE;
            }
        }
    }
    return -1;
}

int find_marker4_21_14(const string& str)
{
    constexpr int SIZE = 14;
    for(int i = 0; i < str.size() - SIZE + 1; i++)
    {
        const int compare_start = i + 1;
        for (int j = i; j < i + SIZE - 1; j++) //It represents word (except last char)
        {
            char comparee = str[j];
            for (int k = j + 1; k < compare_start + SIZE - 1; k++) // chars after comparees
            {
                if (comparee == str[k])
                {
                    i = j;
                    j = i + SIZE - 1;
                    k = compare_start + SIZE - 1;
                }
            }
            if (j == i + SIZE - 2)
            {
                return i + SIZE;
            }
        }
    }
    return -1;
}
int find_marker4_3(const string& str)
{
    constexpr int SIZE = 4;
    for(int i = 0; i < str.size() - SIZE + 1; i++)
    {
        const string word = str.substr(i,SIZE);
        int dup = 0;
        for (int j = 0; j < word.size() - 1; j++)
        {
            dup += word.find(word[j],j+1);
            if(dup == -(SIZE-1)) return i+SIZE;
        }
    }
    return -1;
}

int find_marker4_3_14(const string& str)
{
    constexpr int SIZE = 14;
    for(int i = 0; i < str.size() - SIZE + 1; i++)
    {
        const string word = str.substr(i,SIZE);
        int dup = 0;
        for (int j = 0; j < word.size() - 1; j++)
        {
            dup += word.find(word[j],j+1);
            if(dup == -(SIZE-1)) return i+SIZE;
        }
    }
    return -1;
}

int find_marker4_4(const string& str)
{
    constexpr int size = 4;
    for(int i = 0; i < str.size() - size + 1; i++)
    {
        const string word = str.substr(i,size);
        for (int j = 0; j < word.size() - 1; j++)
        {
            int dup = word.find(word[j],j+1);
            if(dup != -1) break;;
            if(j == size - 2) return i + size;
        }
    }
    return -1;
}

int find_marker4_4_14(const string& str)
{
    constexpr int size = 14;
    for(int i = 0; i < str.size() - size + 1; i++)
    {
        const string word = str.substr(i,size);
        for (int j = 0; j < word.size() - 1; j++)
        {
            int dup = word.find(word[j],j+1);
            if(dup != -1) break;;
            if(j == size - 2) return i + size;
        }
    }
    return -1;
}

int find_marker5(const string& str)
{
    for(int i = 3; i < str.size(); i++)
    {
        if (str[i-1] == str[i])
        {
            i += 2;
            continue;
        }
        if (str[i-1] == str[i-2])
        {
            i += 1;
            continue;
        }
        if (str[i-1] == str[i-3])
        {
            i += 1;
            continue;
        }
        if (str[i-2] == str[i])
        {
            i += 1;
            continue;
        }
        if (str[i-2] == str[i-3])
        {
            i += 2;
            continue;
        }
        if (str[i-3]==str[i])
            continue;
        return i + 1;
    }
    return -1;
}

int find_marker6(const string& str)
{
    for(int i = 3; i < str.size(); i++)
    {
        char first = str[i-3];
        char second = str[i-2];
        char third = str[i-1];
        char last = str[i];

        if (third == last)
        {
            i += 2;
            continue;
        }
        if (second == third)
        {
            i += 1;
            continue;
        }
        if (second == last)
        {
            i += 1;
            continue;
        }
        if (first == second)
        {
            continue;
        }
        if (first == third)
        {
            continue;
        }
        if (first == last)
        {
            continue;
        }

        return i + 1;
    }
    return -1;
}

int find_marker6_2(const string& str)
{
    for(int i = 3; i < str.size(); i++)
    {
        char first = str[i-3];
        char second = str[i-2];
        char third = str[i-1];
        char last = str[i];

        if (first == second)
        {
            continue;
        }
        if (first == third)
        {
            continue;
        }
        if (first == last)
        {
            continue;
        }
        if (second == third)
        {
            i += 1;
            continue;
        }
        if (second == last)
        {
            i += 1;
            continue;
        }
        if (third == last)
        {
            i += 2;
            continue;
        }

        return i + 1;
    }
    return -1;
}

int find_marker7(const string& str)
{
    for(int i = 3; i < str.size(); i++)
    {
        int sum = 0;
        int or_ = 0;
        for(int j = i - 3; j < i + 1; j++)
        {
            int num = 1<<(str[j] % 32); 
            sum += (num);
            or_ |= (num);
        }

        if (sum == or_) return i + 1;
    }
}

int find_marker7_2(const string& str)
{
    for(int i = 3; i < str.size(); i++)
    {
        int sum = 0;
        int or_ = 0;
        for(int j = i - 3; j < i + 1; j++)
        {
            int num = 1<<(str[j] % 32); 
            sum += (num);
            or_ |= (num);
            if(sum != or_) break;
        }
        if (sum == or_) return i + 1;
    }
    return -1;
}

int find_marker7_3(const string& str)
{
    for(int i = 3; i < str.size(); i++)
    {
        int sum = 0;
        int or_ = 0;
        int count = 3;
        for(int j = i; j > i - 4; j--)
        {
            int num = 1<<(str[j] % 32); 
            sum += num;
            or_ |= num;
            if(sum != or_)
            {
                i += count;
            }
            count--;
        }
        if (sum == or_) return i + 1;
    }
    return -1;
}

int find_marker7_4(const string& str)
{
    int SIZE = 4;
    for(int i = SIZE - 1; i < str.size(); i++)
    {
        int sum = 0;
        int or_ = 0;
        int count = SIZE - 1;
        int num = 0;
        for(int j = i; j > i - SIZE; j--)
        {
            num = 1<<(str[j] % 32); 
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

int find_marker7_4_14(const string& str)
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


int find_marker8(const string str)
{
    for(int i = 3; i < str.size(); i++)
    {
        int xor_ = 0;
        for(int j = i - 3; j < i + 1; j++)
        {
            xor_ ^= (1<<(str[j] % 32));
        }
        bitset<32> bits = xor_;
        if (bits.count() == 4) return i+1;
    }
    return -1;
}

int find_marker9(const string str)
{
    const int NUM = 4;
    int filter = 0;
    for (int i = 0; i < NUM - 1; i++)
    {
        filter ^= (1 << (str[i] % 32));
    }
    bitset<32> bits = filter;

    for(int i = 0; i < str.size(); i++)
    {
        int first = str[i];
        int last = str[i + (NUM-1)];
        filter ^= (1 << (last % 32));
        bits = filter;
        if (bits.count() == NUM) return i+NUM;
        filter ^= (1 << (first % 32));
    }
    return -1;
}

int find_marker9_14(const string str)
{
    const int NUM = 14;
    int filter = 0;
    for (int i = 0; i < NUM - 1; i++)
    {
        filter ^= (1 << (str[i] % 32));
    }
    bitset<32> bits = filter;

    for(int i = 0; i < str.size(); i++)
    {
        int first = str[i];
        int last = str[i + (NUM-1)];
        filter ^= (1 << (last % 32));
        bits = filter;
        if (bits.count() == NUM) return i+NUM;
        filter ^= (1 << (first % 32));
    }
    return -1;
}