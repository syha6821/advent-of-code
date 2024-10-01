#include "std_lib_facilities.h"
#include <queue>

const int OLD = -1;

function<int(int)> calc(char ch,int right)
{
    if(right == OLD)
    {
    switch (ch)
    {
    case '+': 
        return [](int old) { return old + old; };
    case '-': 
        return [](int old) { return old - old; };
    case '*': 
        return [](int old) { return old * old; };
    case '/': 
        return [](int old) { return old / old; };
    }
    }
    switch (ch)
    {
    case '+':
        return [right](int old){return old + right;};
    case '-':
        return [right](int old){return old - right;};
    case '*':
        return [right](int old){return old * right;};
    case '/':
        return [right](int old){return old / right;};
    }
}

class Monkey{
public:
    Monkey(queue<int> its,char op, int right):items(its){
        a = calc(op, right);
    };
    int operate()
    {
        int item = items.front();
        items.pop();
        return a(item);
    };

private:
    function<int(int)> a;
    queue<int> items;
};

int main()
{
    queue<int> items;
    items.push(79);
    items.push(60);
    items.push(97);
    Monkey m1(items, '*', OLD);
    int result = m1.operate();
    cout << result << '\n';
    result = m1.operate();
    cout << result << '\n';
    result = m1.operate();
    cout << result << '\n';
    return 0;
}