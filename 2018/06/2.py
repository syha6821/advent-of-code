from collections import namedtuple,deque
from itertools import count
from pprint import pprint

dx = [0,0,1,-1]
dy = [1,-1,0,0]

Coord = namedtuple("Coords",["x","y"])

def read_input(file):
    with open(file) as input:
        return [Coord(*map(int,line.split(","))) for line in input.readlines()]

def center_of(coords):
    return Coord(sum(x for x,_ in coords)//len(coords),sum(y for _,y in coords)//len(coords))

def manhattan(c1,c2):
    return abs(c1.x - c2.x) + abs(c1.y - c2.y)

def is_safe(coord,coords,dist):
    s = 0
    for c in coords:
        d = manhattan(coord,c)
        s += d
        if not s < dist:
            return False
    return s < dist

def solve(file):
    D = 10000
    coords = read_input(file)
    center = center_of(coords)
    safes = set()
    def bfs(q):
        for _ in range(len(q)):
            x,y = q.popleft()
            for i in range(4):
                xx = x + dx[i]
                yy = y + dy[i]
                c = Coord(xx,yy)
                if (c not in safes) and is_safe(c,coords,D):
                    safes.add(c)
                    q.append(c)
        if q:
            bfs(q)

    bfs(deque([center]))

    return len(safes)
