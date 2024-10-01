from collections import namedtuple
from itertools import starmap,chain

Pos = namedtuple("Pos",["x","y","z","w"])

def distance(a,b):
    return abs(a-b)

def manhattan(p1,p2):
    return sum(starmap(distance,zip(p1,p2)))

def is_close(p1,p2):
    return manhattan(p1,p2) <= 3

def can_be_part_of(pos,constella):
    return any(map(lambda p : is_close(p,pos),constella))

def parse_line(line):
    return Pos(*map(int,line.split(",")))

def read_input(file):
    with open(file) as input:
        return list(map(parse_line,input.readlines()))

def solve(file):
    positions = read_input(file)
    constella = dict()
    id = 1
    for pos in positions:
        if not constella:
            constella[id] = [pos]
            id += 1
        else:
            near = []
            for i,cons in constella.items():
                if can_be_part_of(pos,cons):
                    near.append(i)
            new = chain([pos])
            for i in near:
                new = chain(new,constella[i])
                constella.pop(i)
            constella[id] = list(new)
            id += 1
    return len(constella)
