#pragma once
#include "std_lib_facilities.h"
#include "item.h"
#include "monkey.h"
#include <bitset>

const vector<char> operators = {'+','*','/','-','%'};

class Relief
{
public:
    static const int RELIEF_COUNT = 3;

    Relief(char o, int v, int num):op(o),divisor(v),my_num(num){};
    int get_divisor() { return divisor; };
    char get_op() { return op; };
    static void set_circuit(bitset<RELIEF_COUNT> cc) { circuit = cc; };
    /* static void reset_circuit() { circuit = 0b000000; }; */
    static void reset_circuit() { circuit = 0b0; };
    static void print_circuit() { cout << circuit << '\n'; };
    static void circuit_increment()
    {
        circuit = circuit.to_ulong() + 1;
    };
    static int circuit_size() { return circuit.size(); }

    void operator() (Item& item)
    {
        if(circuit[my_num] == 1)
        {
            item.set_worry_level(calc(op, item.get_worry_level(), divisor));
        }
    }

private:
    static bitset<RELIEF_COUNT> circuit;
    const int my_num = 0;
    int divisor = 1;
    char op;
};