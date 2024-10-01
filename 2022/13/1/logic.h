#include "std_lib_facilities.h"
#include "packet.h"

vector<Packet> sort_packets(vector<Packet> packets);
bool compare_packets(pair<Packet, Packet> packet_pair);
char compare_lists(List left, List right);
char compare_values(Value left, Value right);
bool are_types_same(Value left, Value right);