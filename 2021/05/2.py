from collections import namedtuple,defaultdict

Pos = namedtuple("Pos",["row","col"])

def str_to_pos(string):
    return Pos(*tuple(map(int,string.strip().split(','))))

def read_input(filepath):
    with open(filepath) as input:
        for line in input:
            yield tuple(map(str_to_pos,line.strip().split("->")))

def make_line(p1,p2):
    if p1.row == p2.row:
        return tuple(Pos(p1.row,col) for col in range(min(p1.col,p2.col),max(p1.col,p2.col)+1))
    if p1.col == p2.col:
        return tuple(Pos(row,p1.col) for row in range(min(p1.row,p2.row),max(p1.row,p2.row)+1))
    else:
        line = []
        for row,col in zip(range(p1.row,p2.row + (1 if p2.row > p1.row else -1),1 if p2.row > p1.row else -1),range(p1.col,p2.col + (1 if p2.col > p1.col else -1), 1 if p2.col > p1.col else -1)):
            line.append(Pos(row,col))
        return tuple(line)

def solve(filepath):
    ocean_floor = defaultdict(int)
    for p1,p2 in read_input(filepath):
        for pos in make_line(p1,p2):
            ocean_floor[pos] += 1
    return len(tuple(filter(lambda v: v >= 2,ocean_floor.values())))
