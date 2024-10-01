from collections import namedtuple,Counter,defaultdict
from itertools import product,chain,repeat
from functools import reduce

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row, self.col+other.col)
WIDTH = 5
HEIGHT = 5
MIDPOS = Pos(WIDTH//2,HEIGHT//2)
POSITIONS = list(map(lambda p : Pos(*p),product(range(HEIGHT),range(WIDTH))))
UNIT_POS = [Pos(-1,0),Pos(0,1),Pos(1,0),Pos(0,-1)]
SIDE_POS = {"U":[pos for pos in POSITIONS if pos.row == 0],
            "R":[pos for pos in POSITIONS if pos.col == WIDTH - 1],
            "D":[pos for pos in POSITIONS if pos.row == HEIGHT - 1],
            "L":[pos for pos in POSITIONS if pos.col == 0]}
BORDER_DIRECTION = {Pos(1,2):"U",Pos(2,3):"R",Pos(3,2):"D",Pos(2,1):"L"}
BORDER_POS = {"U":Pos(1,2),"R":Pos(2,3),"D":Pos(3,2),"L":Pos(2,1)}

BUG = "#"
EMPTY = "."
CENTER = "?"

def read_input(file):
    with open(file) as input:
        lines = input.read().strip().split('\n')
        return dict(zip(POSITIONS,chain(*lines)))

def direction(p1,p2):
    p = Pos(p2.row-p1.row, p2.col-p1.col)
    if p.row == -1:
        return "U"
    if p.col == 1:
        return "R"
    if p.row == 1:
        return "D"
    if p.col == -1:
        return "L"
    else:
        return "X"

def adjacents(pos):
    adjs = []
    for adj in (pos + unit for unit in UNIT_POS):
        if adj == MIDPOS: # look -1
            adjs += list(zip(repeat(-1),SIDE_POS[BORDER_DIRECTION[pos]]))
        elif adj not in POSITIONS: # look + 1
            adjs.append((1,BORDER_POS[direction(pos,adj)]))
        else:
            adjs.append((0,adj))
    return adjs

def empty_map():
    map_ = dict(zip(POSITIONS,repeat(".")))
    map_[MIDPOS] = CENTER
    return map_

def next_of(recmap):
    next_recmap = defaultdict(lambda : empty_map())
    levels = list(recmap.keys())
    lowest_level = min(levels)
    highest_level = max(levels)
    levels.append(lowest_level - 1)
    levels.append(highest_level + 1)
    for level,map_ in zip(levels,map(lambda l : recmap[l],levels)):
        for pos,tile in map_.items():
            if pos == MIDPOS:
                continue
            adjcnt = Counter([recmap[level+lv][adj] for lv,adj in adjacents(pos)])
            if tile == BUG and not(adjcnt[BUG] == 1):
                next_recmap[level][pos] = EMPTY
            elif tile == EMPTY and (adjcnt[BUG] == 1 or adjcnt[BUG] == 2):
                next_recmap[level][pos] = BUG
            else:
                next_recmap[level][pos] = tile
    return next_recmap

def count_bugs(map_):
    return Counter(map_.values())[BUG]

def solve(file):
    map_ = read_input(file)
    map_[MIDPOS] = CENTER
    recmap = defaultdict(lambda : empty_map(),{0:map_})
    result = reduce(lambda acc,_ : next_of(acc),range(200),recmap)
    return sum(map(count_bugs,result.values()))
