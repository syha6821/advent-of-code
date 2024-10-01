from collections import namedtuple
from math import prod

Pos = namedtuple("Pos",["row","col"])
Slope = namedtuple("Slope",["right","down"])
Map = namedtuple("Map",["map","width","height"])
TREE = "#"

def read_input(file):
    m = dict()
    with open(file) as input:
        lines = list(map(lambda l : l.strip(),input.readlines()))
        width = len(lines[0])
        height = len(lines)
        for row,line in enumerate(lines):
            for col,elm in enumerate(line):
                m[Pos(row,col)] = elm
    return Map(m,width,height)

def slope_down(slope,pos,m):
    return Pos(pos.row + slope.down, (pos.col + slope.right) % m.width)

slopes = [Slope(1,1),Slope(3,1),Slope(5,1),Slope(7,1),Slope(1,2)]

def check_slope(m,slope):
    current = Pos(0,0)
    cnt = 0
    while current.row < m.height - 1:
        current = slope_down(slope,current,m)
        if m.map[current] == TREE:
            cnt += 1
    return cnt

def solve(file):
    m = read_input(file)
    return prod([check_slope(m,slope) for slope in slopes])
