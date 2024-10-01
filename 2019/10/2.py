from math import atan2,degrees
from collections import namedtuple,defaultdict,deque

Pos = namedtuple("Pos",["x","y"])

ASTEROID = '#'

def read_input(file):
    with open(file) as input:
        m = []
        for row,line in enumerate(input.read().strip().split('\n')):
            for col,elm in enumerate(line):
                if elm == ASTEROID:
                    m.append(Pos(col,-row))
        return m

def sight(pos,m):
    s = defaultdict(list)
    asts = [Pos(p.x-pos.x,p.y-pos.y) for p in m if p != pos]
    for a in asts:
        s[degrees(atan2(a.x,-a.y))].append(a)
    return {deg:list(map(lambda p: Pos(p.x+pos.x,p.y+pos.y),positions)) for deg,positions in s.items()}

def best_location(m):
    return max(m,key = lambda p: len(sight(p,m)))

def distance(p1,p2):
    return abs(p2.x - p1.x) + abs(p2.y - p1.y)

def sight_sorted(pos,m):
    s = sight(pos,m)
    s = {deg:sorted(positions, key = lambda p : distance(p,pos)) for deg,positions in s.items()}
    return sorted(s.items(), key = lambda kv: -kv[0])

def solve(file):
    m = read_input(file)
    s = sight_sorted(best_location(m),m)
    s = [deque(positions) for _,positions in s]
    cnt = 0
    index = 0
    last = None
    while cnt != 200:
        index = index % len(s)
        if not s[index]:
            index += 1
            continue
        last = s[index].popleft()
        index += 1
        cnt += 1
    return last.x * 100 - last.y
