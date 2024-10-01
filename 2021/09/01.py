from collections import namedtuple

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row, self.col+other.col)

UNIT_POS = {"U":Pos(-1,0),"R":Pos(0,1),"D":Pos(1,0),"L":Pos(0,-1)}

def read_heightmap(filepath):
    with open(filepath) as input:
        return list(list(map(int,line.strip())) for line in input)

def is_lowpoint(pos,height,width,m):
    val = m[pos.row][pos.col]
    adjs = filter(lambda p : (0 <= p.row and p.row < height) and (0 <= p.col and p.col < width),(unit+pos for unit in UNIT_POS.values()))
    return all(val < m[p.row][p.col] for p in adjs)

def solve(filepath):
    heightmap = read_heightmap(filepath)
    height = len(heightmap)
    width = len(heightmap[0])
    return sum(heightmap[pos.row][pos.col] + 1 for pos in filter(lambda pos: is_lowpoint(pos,height,width,heightmap),(Pos(row,col) for col in range(width) for row in range(height))))
