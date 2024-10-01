from collections import namedtuple,Counter,defaultdict
from operator import add
from itertools import starmap
from math import inf
from queue import PriorityQueue

import sys
sys.setrecursionlimit(10**9)

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(*list(starmap(add,zip(self,other))))
UNIT_POS = [Pos(-1,0),Pos(0,1),Pos(1,0),Pos(0,-1)]

Portal = namedtuple("Portal",["name","inner"])

def ispath(tile):
    return tile == "."

def is_outer(pos,width,height):
    outer_col = pos.col == 2 or pos.col == width - 3
    outer_row = pos.row == 2 or pos.row == height - 3
    return outer_col or outer_row

def is_inner(pos,width,height):
    return not is_outer(pos,width,height)

def adjacents(pos):
    return [pos + unit for unit in UNIT_POS]

def match_alphas(alphas):
    matched = []
    used = set()
    for pos,alpha in alphas.items():
        if pos in used:
            continue
        adjs = [pos+unit for unit in UNIT_POS]
        match_pos = next(filter(lambda p : p in adjs,alphas))
        match_alpha = alphas[match_pos]
        matched.append((alpha + match_alpha if pos < match_pos else match_alpha + alpha,(pos,match_pos)))
        used.add(pos)
        used.add(match_pos)
    return matched

def distance(p1,p2):
    return abs(p1.row - p2.row) + abs(p1.col - p2.col)

def read_input(file):
    with open(file) as input:
        lines = input.read()[:-1].split('\n')
        paths = dict()
        alphas = dict()
        height = len(lines)
        width = len(lines[0])
        for row,line in enumerate(lines):
            for col,tile in enumerate(line):
                if tile.isalpha():
                    alphas[Pos(row,col)] = tile
                elif ispath(tile):
                    paths[Pos(row,col)] = tile
        alphas = match_alphas(alphas)
        freq = Counter(list(map(lambda l : l[0],alphas)))
        portals = defaultdict(list)
        for label,positions in alphas:
            port = next(filter(lambda p : any(map(lambda adj : adj in paths,adjacents(p))),positions))
            position = next(adj for adj in adjacents(port) if adj in paths)
            paths[position] = label
            if freq[label] == 2:
                portals[label].append(position)
        for label,positions in portals.items():
            inner = next(filter(lambda p : is_inner(p,width,height),positions))
            outer = next(filter(lambda p : is_outer(p,width,height),positions))
            paths[inner] = Portal(label,True)
            paths[outer] = Portal(label,False)
        return paths

def find_edges(pos,paths):
    edges = dict()
    history = defaultdict(lambda : inf)
    def aux(current,steps):
        mem = history[current]
        if mem < steps:
            return
        history[current] = steps
        tile = paths[current]
        if tile != "." and current != pos:
            edges[tile] = steps
        else:
            for adj in (adj for adj in adjacents(current) if adj in paths):
                aux(adj,steps+1)
    aux(pos,0)
    return edges

def make_node_map(paths):
    nodes = {tile:find_edges(pos,paths) for pos,tile in paths.items() if tile != "."}
    return nodes

def calc_steps(fr_,to_,node_map):
    pq = PriorityQueue()
    history = set()
    index = [0]
    def aux(current,level,steps):
        if current == to_:
            return steps
        if (level,current) not in history:
            history.add((level,current))
            for node,distance in node_map[current].items():
                if level == 0: # Outermost
                    if type(node) == Portal and node.inner:
                        pq.put((steps+distance+1,index[0],level+1,Portal(node.name,False)))
                        index[0] += 1
                    else:
                        pq.put((steps+distance,index[0],level,node))
                        index[0] += 1
                else:
                    if type(node) == Portal:
                        if node.inner:
                            pq.put((steps+distance+1,index[0],level+1,Portal(node.name,False)))
                            index[0] += 1
                        if not(node.inner):
                            pq.put((steps+distance+1,index[0],level-1,Portal(node.name,True)))
                            index[0] += 1

        s,_,l,n = pq.get()
        return aux(n,l,s)
    return aux(fr_,0,0)

def solve(file):
    return calc_steps("AA","ZZ",make_node_map(read_input(file)))
