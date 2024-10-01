from functools import reduce
from collections import namedtuple

Packet = namedtuple("Packet",["version","type","contents","size"],defaults = (0,-1,0,0))
LITERAL = 4

def hex_to_bin(hex):
    return reduce(lambda result,h: result + bin(int(h,16))[2:].zfill(4),hex,"")

def decode(binary):
    def decode_bin(binary,index):
        if len(binary) - index < 11:
            return Packet(0,-1,0,len(binary)-index)
        version = int(binary[index:index+3],2)
        type = int(binary[index+3:index+6],2)
        if type == LITERAL:
            literal_bin = read_literal(binary[index+6:])
            return Packet(version,type,int(literal_bin,2),6+(len(literal_bin)//4) * 5)
        else:
            sub_packets = read_operator(binary[index+6:])
            return Packet(version,type,sub_packets,7 + (15 if binary[index+6] == '0' else 11) + sum(packet.size for packet in sub_packets))
    return decode_bin(binary,0)

def read_literal(rest):
    if rest[0] == '1':
        return rest[1:5] + read_literal(rest[5:])
    else:
        return rest[1:5]

def read_operator(rest):
    length_id = rest[0]
    index = 16 if length_id == '0' else 12
    length = int(rest[1:index],2)
    sub_packets = []
    while length != 0:
        packet = decode(rest[index:])
        sub_packets.append(packet)
        length -= packet.size if length_id == '0' else 1
        index += packet.size
    return sub_packets

def version_sum(packet):
    if packet.type == LITERAL:
        return packet.version
    elif packet.type != -1:
        return packet.version + sum(version_sum(p) for p in packet.contents)
    else:
        return 0

def solve(filepath):
    with open(filepath) as input:
        return version_sum(decode(hex_to_bin(input.read().strip())))
