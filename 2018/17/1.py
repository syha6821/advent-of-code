from collections import namedtuple,deque
import sys

sys.setrecursionlimit(10**9)

Pos = namedtuple("Pos",["row","col"])

SAND = "."
CLAY = "#"
FLOW = "|"
REST = "~"

def parse_range(line):
    r = line.split("=")[-1]
    r = list(map(int,r.split("..")))
    return range(r[0],r[-1]+1)

def parse_line(line):
    if line[0] == "x":
        return parse_line(",".join(reversed(line.split(","))))
    return list(map(parse_range,line.split(",")))

def read_input(file):
    with open(file) as input:
        return [parse_line(line) for line in input.readlines()]

def make_graph(veins):
    width = 0
    height = 0
    minrow = 10000
    for rows,cols in veins:
        width = max(width,cols.stop)
        height = max(height,rows.stop)
        minrow = min(minrow,rows.start)
    graph = [[SAND] * width for _ in range(height)]
    for rows,cols in veins:
        for row in rows:
            for col in cols:
                graph[row][col] = CLAY
    return graph,minrow

def print_graph(graph):
    for line in graph:
        print(*line,sep="")

def up(pos):
    return Pos(pos.row-1,pos.col)
def down(pos):
    return Pos(pos.row+1,pos.col)
def left(pos):
    return Pos(pos.row,pos.col-1)
def right(pos):
    return Pos(pos.row,pos.col+1)
def at(pos,graph):
    if not(0 <= pos.row < len(graph) and 0 <= pos.col < len(graph[0])):
        print(pos)
    return graph[pos.row][pos.col]

def simulate(graph):
    width = len(graph[0])
    height = len(graph)
    # print(width,height)

    def spread(pos):
        layer = deque([pos])
        l = left(pos)
        while True:
            # if not(0 <= l.row < height and 0 < l.col < width):
            #     break
            layer.appendleft(l)
            if at(l,graph) == CLAY or at(down(l),graph) == SAND:
                break
            l = left(l)
        r = right(pos)
        while True:
            # if not(0 <= r.row < height and 0 < r.col < width):
            #     break
            layer.append(r)
            if at(r,graph) == CLAY or at(down(r),graph) == SAND:
                break
            r = right(r)
        if at(layer[0],graph) == CLAY and at(layer[-1],graph) == CLAY:
            for i in range(1,len(layer)-1):
                row,col = layer[i]
                graph[row][col] = REST
        else:
            lf = False
            rf = False
            if at(layer[0],graph) == SAND:
                row,col = layer[0]
                graph[row][col] = FLOW
                lf = True
            if at(layer[-1],graph) == SAND:
                row,col = layer[-1]
                graph[row][col] = FLOW
                rf = True
            for i in range(1,len(layer)-1):
                row,col = layer[i]
                graph[row][col] = FLOW
            if lf:
                fall(layer[0])
            if rf:
                fall(layer[-1])

    def fall(pos):
        if pos.row < height - 1:
            d = down(pos)
            if at(d,graph) == SAND:
                graph[d.row][d.col] = FLOW
                fall(d)
                if at(d,graph) == REST:
                    spread(pos)
            elif at(d,graph) in [REST,CLAY]:
                spread(pos)

    fall(Pos(0,500))

def solve(file):
    veins = read_input(file)
    graph,minrow = make_graph(veins)
    simulate(graph)
    cnt = 0
    for line in graph[minrow:]:
        for tile in line:
            if tile in [FLOW,REST]:
                cnt += 1
    # print_graph(graph)

    return cnt
