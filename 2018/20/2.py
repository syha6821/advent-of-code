from collections import defaultdict,namedtuple
from pprint import pprint
from itertools import repeat
from math import inf
from heapq import *

Pos = namedtuple("Pos",["row","col"])

dx = [0,0,-1,1]
dy = [-1,1,0,0]

def split_by_bar(pattern):
    result = [[]]
    level = 0
    for p in pattern:
        if p == ")":
            level -= 1
        elif p == "(":
            level += 1

        if p == "|" and level == 0:
            result.append([])
        else:
            result[-1].append(p)
    return list(map(lambda l : "".join(l),result))

def split_by_parens(pattern):
    result = [[]]
    level = 0
    for p in pattern:
        if p == ")":
            level -= 1
        elif p == "(":
            level += 1

        if p == ")" and level == 0:
            result.append([])
        elif p == "(" and level == 1:
            result.append([])
        else:
            result[-1].append(p)

    return list(map(lambda l : "".join(l),result))

def read_input(file):
    with open(file) as input:
        return input.readline().strip()[1:-1]

def index_of(s,item):
    for i,c in enumerate(s):
        if c == item:
            return i
    return -1

def max_door(regex):
    if not regex:
        return 0
    elif regex[-1] == "|":
        return 0
    else:
        bars = split_by_bar(regex)
        if len(bars) > 1:
            return max([max_door(pattern) for pattern in bars])
        else:
            parens = split_by_parens(regex)
            if len(parens) == 1:
                return len(parens[0])
            else:
                return sum([max_door(pattern) for pattern in split_by_parens(regex)])

def at(pos,direction):
    match direction:
        case "N":
            return Pos(pos.row - 1, pos.col)
        case "E":
            return Pos(pos.row, pos.col + 1)
        case "S":
            return Pos(pos.row + 1, pos.col)
        case "W":
            return Pos(pos.row, pos.col - 1)

def make_graph(regex):
    graph = defaultdict(list)
    pos = Pos(0,0)
    def aux(regex):
        nonlocal pos
        if regex:
            bars = split_by_bar(regex)
            if len(bars) > 1:
                for pattern in bars:
                    prev = pos
                    aux(pattern)
                    pos = prev
            else:
                parens = split_by_parens(regex)
                if len(parens) == 1:
                    for d in parens[0]:
                        room = at(pos,d)
                        graph[pos].append(room)
                        graph[room].append(pos)
                        pos = room
                else:
                    for pattern in parens:
                        aux(pattern)
    aux(regex)
    return graph

def dijkstra(graph):
    h = [(0,Pos(0,0))]
    distances = dict(zip(graph.keys(),repeat(inf)))
    distances[Pos(0,0)] = 0
    while h:
        d,pos = heappop(h)
        distances[pos] = d
        for p in graph[pos]:
            if distances[p] > d:
                distances[p] = d
                heappush(h,(d+1,p))
    return distances

def solve(file):
    pattern = read_input(file)
    graph = make_graph(pattern)
    distances = dijkstra(graph)
    return len([d for d in distances.values() if d >= 1000])
