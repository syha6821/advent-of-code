#pragma once
#include "std_lib_facilities.h"
#include <fstream>
#include "packet.h"

vector<pair<Packet,Packet>> read_input(string filename)
{
    vector<pair<Packet,Packet>> pairs;
    string first;
    string second;
    ifstream ifs(filename);
    while (getline(ifs, first))
    {
        if (first.empty()) continue;
        getline(ifs, second);
        pairs.push_back(make_pair(Packet(first), Packet(second)));
    }
    return pairs;
}

vector<Packet> read_packets(string filename)
{
    vector<Packet> packets;
    string line;
    ifstream ifs(filename);
    while (getline(ifs, line))
    {
        if (line.empty()) continue;
        packets.push_back(Packet(line));
    }
    return packets;
}

vector<Packet> add_divider_packets(vector<Packet> packets)
{
    packets.push_back(Packet("[[2]]",1));
    packets.push_back(Packet("[[6]]",2));
    return packets;
}