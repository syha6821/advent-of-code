from collections import namedtuple

Pos = namedtuple("Pos",["row","col"])
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

def slope_down(pos,m):
    return Pos(pos.row + 1, (pos.col + 3) % m.width)


def solve(file):
    m = read_input(file)
    current = Pos(0,0)
    cnt = 0
    while current.row < m.height - 1:
        current = slope_down(current,m)
        if m.map[current] == TREE:
            cnt += 1
    return cnt
