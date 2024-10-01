from queue import PriorityQueue
from collections import namedtuple
from functools import reduce

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row, self.col+other.col)

UNIT_POS = {"U":Pos(-1,0),"R":Pos(0,1),"D":Pos(1,0),"L":Pos(0,-1)}

def read_heightmap(filepath):
    with open(filepath) as input:
        return list(list(map(int,line.strip())) for line in input)

def is_valid_pos(pos,height,width):
    return (0 <= pos.row and pos.row < height) and (0 <= pos.col and pos.col < width)

def adjacent_pos(pos,height,width):
    return filter(lambda p : is_valid_pos(p,height,width), (pos + unit for unit in UNIT_POS.values()))

def is_lowpoint(pos,height,width,m):
    val = m[pos.row][pos.col]
    adjs = filter(lambda p : is_valid_pos(p,height,width),(unit+pos for unit in UNIT_POS.values()))
    return all(val < m[p.row][p.col] for p in adjs)

def find_lowpoint(heightmap):
    height = len(heightmap)
    width = len(heightmap[0])
    return filter(lambda pos: is_lowpoint(pos,height,width,heightmap),(Pos(row,col) for col in range(width) for row in range(height)))

def basin_size(lowpoint,heightmap,height,width):
    basin = set()
    points = set((lowpoint,))
    while points:
        next_points = set()
        for point in points:
            next_points.update(filter(lambda adj : (adj not in basin) and (heightmap[adj.row][adj.col] != 9),adjacent_pos(point,height,width)))
        basin.update(points)
        points = next_points
    return len(basin)

def solve(filepath):
    heightmap = read_heightmap(filepath)
    height = len(heightmap)
    width = len(heightmap[0])
    q = PriorityQueue(maxsize=3)
    for low in find_lowpoint(heightmap):
        basin = basin_size(low,heightmap,height,width)
        if q.full() and q.queue[0] < basin:
            q.get()
        if not q.full():
            q.put(basin)
    return reduce(lambda x,y: x*y,q.queue)
