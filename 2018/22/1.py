from collections import namedtuple

R = "."
W = "="
N = "|"

Pos = namedtuple("Pos",["row","col"])

def make_graph(depth,target):
    width = target.col + 1
    height = target.row + 1
    geo_graph = [[0] * (width+1) for _ in range(height+1)]
    for col in range(width+1):
        geo_graph[0][col] = col * 16807
    for row in range(height+1):
        geo_graph[row][0] = row * 48271
    for row in range(1,height+1):
        for col in range(1,width+1):
            geo_graph[row][col] = ((geo_graph[row-1][col] + depth) % 20183) * ((geo_graph[row][col - 1] + depth) % 20183)
    geo_graph[target.row][target.col] = 0
    graph = [["?"] * (width+1) for _ in range(height+1)]
    for row in range(height+1):
        for col in range(width+1):
            erosion = (geo_graph[row][col] + depth) % 20183
            t = erosion % 3
            if t == 0:
                graph[row][col] = R
            elif t == 1:
                graph[row][col] = W
            elif t == 2:
                graph[row][col] = N
    return graph

def risk_level(depth,target):
    risk = 0
    graph = make_graph(depth,target)
    for row in range(target.row+1):
        for col in range(target.col+1):
            t = graph[row][col]
            if t == R:
                risk += 0
            elif t == W:
                risk += 1
            elif t == N:
                risk += 2
    return risk
