from collections import namedtuple

Pos = namedtuple("Pos",["row","col"])
Move = namedtuple("Move",["direction","count"])

UNIT_POS = {"U":Pos(-1,0),"R":Pos(0,1),"D":Pos(1,0),"L":Pos(0,-1)}
Pos.__add__ = lambda self,other : Pos(self.row+other.row,self.col+other.col)

def read_move(s):
    return Move(s[0],int(s[1:]))

def read_path(line):
    return list(map(read_move,line.split(',')))

def read_input(file):
    with open(file) as input:
        return tuple(map(read_path,input.read().strip().split('\n')))

def make_wire(path):
    wire = dict()
    pos = Pos(0,0)
    steps = 0
    for move in path:
        for _ in range(move.count):
            steps += 1
            pos += UNIT_POS[move.direction]
            wire[pos] = steps
    return wire

def inter(w1,w2):
    return set(w1.keys()).intersection(set(w2.keys()))

def solve(file):
    w1,w2 = list(map(make_wire,read_input(file)))
    crosses = inter(w1,w2)
    pos = min(crosses,key = lambda p : w1[p] + w2[p])
    return w1[pos] + w2[pos]
