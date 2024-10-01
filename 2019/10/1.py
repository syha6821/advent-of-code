from collections import namedtuple
from math import inf

EMPTY = '.'
ASTEROID = '#'

Pos = namedtuple("Pos",["row","col"])

def read_input(file):
    with open(file) as input:
        m = []
        for row,line in enumerate(input.read().strip().split('\n')):
            for col,elm in enumerate(line):
                if elm == ASTEROID:
                    m.append(Pos(row,col))
        return m

def sign(n):
    return 0 if n == 0 else 1 if n > 0 else -1

def sight(pos,m):
    s = set()
    relative_positions = [Pos(p.row-pos.row, p.col-pos.col) for p in m if p != pos]
    for p in relative_positions:
        if p.col == 0:
            s.add(((sign(p.row),sign(p.col)),inf))
        else:
            s.add(((sign(p.row),sign(p.col)),p.row/p.col))
    return len(s)

def solve(file):
    m = read_input(file)
    return max(sight(pos,m) for pos in m)
