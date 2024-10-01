from collections import Counter
from copy import deepcopy

OPEN = "."
TREE = "|"
YARD = "#"

dx = [0,0,1,-1,1,-1,1,-1]
dy = [1,-1,0,0,1,-1,-1,1]

def simulate(m,graph):
    width = len(graph[0])
    height = len(graph)
    before = graph
    for _ in range(m):
        after = deepcopy(before)
        for row in range(height):
            for col in range(width):
                cnt = Counter()
                for i in range(8):
                    r = row + dx[i]
                    c = col + dy[i]
                    if 0 <= r < height and 0 <= c < width:
                        cnt[before[r][c]] += 1
                acre = before[row][col]
                if acre == OPEN:
                    if cnt[TREE] >= 3:
                        after[row][col] = TREE
                elif acre == TREE:
                    if cnt[YARD] >= 3:
                        after[row][col] = YARD
                elif acre == YARD:
                    if cnt[YARD] >= 1 and cnt[TREE] >= 1:
                        pass
                    else:
                        after[row][col] = OPEN
        before = after
    return before

def print_graph(graph):
    for line in graph:
        print(*line,sep="")

def read_input(file):
    with open(file) as input:
        return [list(line.strip()) for line in input.readlines()]


def solve(file):
    graph = read_input(file)
    graph = simulate(10,graph)
    cnt = Counter()
    for line in graph:
        for acre in line:
            cnt[acre] += 1

    return cnt[TREE] * cnt[YARD]
