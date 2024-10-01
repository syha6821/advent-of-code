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

def renovate(tiles,lines):
    for line in lines:
        pos = identify(line)
        tiles[pos] = not(tiles[pos])
    return tiles

def inspect(pos,tiles):
    counter = defaultdict(int)
    for unit in UNIT_POS.values():
        adj = unit+pos
        if adj not in tiles:
            counter[WHITE] += 1
        else:
            counter[tiles[adj]] += 1
    return counter

def fill(tiles):
    new_tiles = dict()
    for pos,state in tiles.items():
        if state == BLACK:
            for unit in UNIT_POS.values():
                adj = pos + unit
                if adj not in tiles:
                    new_tiles[adj] = WHITE
        new_tiles[pos] = state
    return new_tiles

def flip(tiles):
    new_tiles = dict()
    for pos,state in fill(tiles).items():
        inspected = inspect(pos,tiles)
        if state == BLACK and (inspected[BLACK] == 0 or inspected[BLACK] > 2):
            new_tiles[pos] = WHITE
        elif state == WHITE and inspected[BLACK] == 2:
            new_tiles[pos] = BLACK
        else:
            new_tiles[pos] = state
    return new_tiles

def solve(file):
    tiles = renovate(defaultdict(bool),read_input(file))
    for _ in range(100):
        tiles = flip(tiles)
    return Counter(tiles.values())[BLACK]
