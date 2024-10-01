from collections import namedtuple,Counter
from itertools import product,chain

Pos = namedtuple("Pos",["row","col"])
UNIT_POS = [Pos(-1,0),Pos(0,1),Pos(1,0),Pos(0,-1)]
Pos.__add__ = lambda self,other : Pos(self.row+other.row, self.col+other.col)

BUG = "#"
EMPTY = "."

def read_input(file):
    with open(file) as input:
        lines = input.read().strip().split('\n')
        height = len(lines)
        width = len(lines[0])
        return dict(zip(map(lambda p : Pos(*p),product(range(height),range(width))),chain(*lines))),width,height

def adjacents(pos,map_):
    return list(p for p in map(lambda unit : pos + unit,UNIT_POS) if p in map_)

def next_of(map_):
    next_map = dict()
    for pos,state in map_.items():
        adjs = Counter(map(lambda p : map_[p] ,adjacents(pos,map_)))
        if state == BUG and not(adjs[BUG] == 1):
            next_map[pos] = EMPTY
        elif state == EMPTY and (adjs[BUG] == 1 or adjs[BUG] == 2):
            next_map[pos] = BUG
        else:
            next_map[pos] = state
    return next_map

def order_of(pos,width):
    return pos.row * width + pos.col

def find_repeat(init):
    map_ = init
    history = set()
    while True:
        bugs = tuple(pos for pos,state in map_.items() if state == BUG)
        if bugs in history:
            return bugs
        else:
            history.add(bugs)
            map_ = next_of(map_)

def solve(file):
    map_,width,_ = read_input(file)
    # return find_repeat(map_)
    return sum(map(lambda p : pow(2,order_of(p,width)),find_repeat(map_)))
