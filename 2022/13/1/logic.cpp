#include "logic.h"

bool compare_packets(Packet left_packet, Packet right_packet)
{
    List left = left_packet.get_list();
    List right = right_packet.get_list();

    bool result  = compare_lists(left, right);
    return result;
}

bool compare_packets(pair<Packet, Packet> packet_pair)
{
    List left = packet_pair.first.get_list();
    List right = packet_pair.second.get_list();

    bool result  = compare_lists(left, right);
    return result;
}

char compare_lists(List left, List right)
{
    try
    {
        int size = (left.size() > right.size()) ? left.size() : right.size();
        char result;
        for (int i = 0; i < size; i++)
        {
            /* cout << "comparing " << i << "th value...\n"; */
            result = compare_values(left.get_values()[i], right.get_values()[i]);
            /* cout << "compare result : " << result << '\n'; */
            if (result == 'd') continue;
            /* if(result == true) cout << "right order!\n"; */
            /* else cout << "not right order\n"; */
            return result;
        }
        return result;
    }
    catch(const std::out_of_range& e)
    {
        /* cout << "out of range!\n"; */
        return (left.size() < right.size());
    }
    
}

char compare_values(Value left, Value right)
{
    if (are_types_same(left, right))
    {
        /* cout << "same type\n"; */
        if (left.type() == ValueType::INT)
        {
            /* cout << "Compare " << left.get_num() << " vs " << right.get_num() << '\n'; */
            if(left.get_num() == right.get_num()) return 'd';
            return left.get_num() < right.get_num();
        }
        
        if (left.type() == ValueType::LIST)
        {
            /* cout << "comparing lists...\n"; */
            return compare_lists(left.get_list(), right.get_list());
        }
    }
    else
    {
        /* cout << "different type!\n"; */
        if (left.type() == ValueType::INT)
        {
            /* cout << "different type(left int,right list) : " << left.get_num() << '\n'; */
            return compare_lists(List({left}),right.get_list());
        }
        if (right.type() == ValueType::INT)
        {
            /* cout << "different type(left list,right int) : " << right.get_num() << '\n'; */
            return compare_lists(left.get_list(), List({right}));
        }
    }
}

bool are_types_same(Value left, Value right)
{
    bool is_same = (left.type() == right.type());
    if(is_same)
    {
        /* cout << "same type\n"; */
    }
    else
    {
        /* cout << "different type\n"; */
    }
    return left.type() == right.type();
}

vector<Packet> sort_packets(vector<Packet> packets)
{
    int count = 0;
    int divider_first = 0;
    int divider_second = 0;
    while(true)
    {
        divider_first = 0;
        divider_second = 0;
        count = 0;
        for (int i = 1; i < packets.size(); i++)
        {
            if (not compare_packets(packets[i - 1], packets[i]))
            {
                swap(packets[i-1], packets[i]);
                count++;
            }
            if (packets[i - 1].is_divider())
            {
                if (packets[i - 1].which_divider() == 1) divider_first = i;
                if (packets[i - 1].which_divider() == 2) divider_second = i;
            }
        }
        if(count == 0)
        {
            cout << "decoder key : " << divider_first * divider_second << '\n';
            break;
        }
    }
    return packets;
}