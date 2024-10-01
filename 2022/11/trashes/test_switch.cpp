#include "std_lib_facilities.h"
#include <bitset>

class Relief
{
public:
    Relief(int num,bitset<6>* cc):circuit(cc),my_num(num){};
    
    void operator() () const
    {
        if((*circuit)[my_num] == 1)
        {
            cout << my_num << "th function!\n";
        }
    };

private:
    bitset<6>* circuit;
    const int my_num = 0;
};

void increment(bitset<6>& b)
{
    b = b.to_ulong() + 1;
}

int main()
{
    bitset<6> circuit(0);
    vector<Relief> relieves;
    for(int i = 0; i < circuit.size(); i++)
    {
        relieves.push_back(Relief(i,&circuit));
    }
    
    circuit = 0b100001;
    
    for(const auto& reliever : relieves)
    {
        reliever();
    }

    return 0;
}