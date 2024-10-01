from collections import namedtuple,defaultdict,Counter
from functools import reduce

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row + other.row, self.col + other.col)

UNIT_POS = {"e":Pos(0,1),"se":Pos(1,0.5),"sw":Pos(1,-0.5),"w":Pos(0,-1),"nw":Pos(-1,-0.5),"ne":Pos(-1,0.5)}
WHITE = False
BLACK = True

def read_line(line):
    if line == "":
        return []
    else:
        if line[:2] in UNIT_POS:
            return [line[:2]] + read_line(line[2:])
        else:
            return [line[0]] + read_line(line[1:])

def read_input(file):
    with open(file) as input:
        return list(map(read_line,input.read().strip().split('\n')))

def identify(directions):
    return reduce(lambda acc,direction : acc + UNIT_POS[direction],directions,Pos(0.0,0.0))

def solve(file):
    lines = read_input(file)
    d = defaultdict(bool)
    for line in lines:
        pos = identify(line)
        d[pos] = not(d[pos])
    return Counter(d.values())[BLACK]
