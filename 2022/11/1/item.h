#pragma once

class Item{
public:
    Item(vector<int> v):mul_value(v){};
    
    void mul_set_value (int val, int index) { mul_value[index] = val; };
    void mul_add_value(int v)
    {
        mul_value.push_back(v);
    };
    vector<int> get_mul_value_list() const { return mul_value; } ;
    void plus_add_value(int v) { plus_value += v; };
    int get_plus_value() const { return plus_value; } ;
    
    int mod_(int divisor) const
    {
        int tmp_sum = mul_value[0];
        for(int i = 1; i < mul_value.size(); i++)
        {
            tmp_sum = (tmp_sum * mul_value[i]) % divisor;
            if (tmp_sum == 0) return 0;
        }
        
        return tmp_sum;
    }

    void append_vector_to_mul(const vector<int>& v)
    {
        for(const int& val : v)
        {
            mul_value.push_back(val);
        }
    }

private:
    vector<int> mul_value;
    int plus_value = 0;
};