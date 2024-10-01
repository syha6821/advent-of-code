from collections import namedtuple,defaultdict
from heapq import *
from math import inf

R = 0
W = 1
N = 2
TORCH = 0
CLIMB = 1
NEITHER = 2

Pos = namedtuple("Pos",["row","col"])

def geo_of(pos,geo_graph,depth,target):
    try:
        return geo_graph[pos]
    except:
        row,col = pos
        if pos == Pos(0,0):
            geo_graph[pos] = 0
        elif pos == target:
            geo_graph[pos] = 0
        elif row == 0:
            geo_graph[pos] = col * 16807
        elif col == 0:
            geo_graph[pos] = row * 48271
        else:
            geo_graph[pos] = ((geo_of(Pos(row-1,col),geo_graph,depth,target) + depth) % 20183) * ((geo_of(Pos(row,col-1),geo_graph,depth,target) + depth) % 20183)
        return geo_graph[pos]

def type_at(pos,geo_graph,depth,target):
    erosion = (geo_of(pos,geo_graph,depth,target) + depth) % 20183
    return erosion % 3

def risk_level(depth,target):
    risk = 0
    geo_graph = dict()
    for row in range(target.row+1):
        for col in range(target.col+1):
            t = type_at(Pos(row,col),geo_graph,depth,target)
            if t == R:
                risk += 0
            elif t == W:
                risk += 1
            elif t == N:
                risk += 2
    return risk

def print_graph(graph,width,height,depth,target):
    for row in range(height):
        for col in range(width):
            t = type_at(Pos(row,col),graph,depth,target)
            if t == R:
                print(".",end="")
            elif t == W:
                print("=",end="")
            elif t == N:
                print("|",end="")
        print()

def dijkstra(depth,target):
    dx = [0,0,-1,1]
    dy = [-1,1,0,0]
    h = [(0,Pos(0,0),TORCH)]
    tools = [TORCH,CLIMB,NEITHER]
    allowed = {R:[CLIMB,TORCH],W:[CLIMB,NEITHER],N:[TORCH,NEITHER]}
    distance = defaultdict(lambda : defaultdict(lambda : inf))
    graph = dict()
    distance[Pos(0,0)][TORCH] = 0
    while True:
        time,(row,col),tool = heappop(h)
        if (row,col) == target and tool == TORCH:
            return time
        current_type = type_at(Pos(row,col),graph,depth,target)
        for changed in tools:
            if changed != tool and changed in allowed[current_type] and time + 7 < distance[Pos(row,col)][changed]:
                distance[Pos(row,col)][changed] = time + 7
                heappush(h,(time+7,Pos(row,col),changed))
        for i in range(4):
            rr = row + dx[i]
            cc = col + dy[i]
            if 0 <= rr and 0 <= cc:
                next_type = type_at(Pos(rr,cc),graph,depth,target)
                if tool in allowed[next_type] and time + 1 < distance[Pos(rr,cc)][tool]:
                    distance[Pos(rr,cc)][tool] = time + 1
                    heappush(h,(time+1,Pos(rr,cc),tool))

def read_input(file):
    with open(file) as input:
        depth = int(input.readline().split(":")[1])
        x,y = map(int,input.readline().split(":")[1].split(","))
        target = Pos(y,x)
        return depth,target

def solve(file):
    depth,target = read_input(file)
    return dijkstra(depth,target)
