from collections import namedtuple,defaultdict
from queue import PriorityQueue
from itertools import product,chain
import sys
sys.setrecursionlimit(10**9)

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row,self.col+other.col)
UNIT_POS = {"U":Pos(-1,0),"R":Pos(0,1),"D":Pos(1,0),"L":Pos(0,-1)}
WALL = "#"
ENTRANCE = "@"
EMPTY = "."
iskey = lambda c : c.islower()
isdoor = lambda c : c.isupper()
ispath = lambda c : c == EMPTY
key_of = lambda door : door.lower()

def read_input(file):
    with open(file) as input:
        input = input.read().strip().split('\n')
        height = len(input)
        width = len(input[0])
        positions = product(range(height),range(width))
        map_ = {Pos(*pos):elm for pos,elm in zip(positions ,chain(*input)) if elm != WALL}
    return map_

def find_nodes(map_):
    nodes = {v:k for k,v in map_.items() if v != EMPTY}
    return nodes

def find_adjacents(pos,map_):
    adjacents = dict()
    history = dict()
    def aux(current,distance):
        if current not in map_:
            return
        if current in history and history[current] <= distance:
            return
        history[current] = distance
        elm = map_[current]
        if ispath(elm) or elm == "@" or current == pos:
            for adj in (current + unit for unit in UNIT_POS.values()):
                aux(adj,distance+1)
            return
        else:
            if elm not in adjacents or adjacents[elm] > distance:
                adjacents[elm] = distance
            return
    aux(pos,0)
    return adjacents

def make_node_map(map_):
    nodes = find_nodes(map_)
    return {node:find_adjacents(pos,map_) for node,pos in nodes.items()}

def collect_keys(node_map):
    keys = [elm for elm in node_map if iskey(elm)]
    pq = PriorityQueue()
    history = defaultdict(list)
    def aux(current,found,steps):
        if len(found) == len(keys):
            return steps
        elif not(any(map(lambda fnd : found.issubset(fnd), history[current]))):
            history[current].append(found)
            for adj,distance in node_map[current].items():
                if (isdoor(adj) and key_of(adj) in found) and not(any(map(lambda fnd : found.issubset(fnd) ,history[adj]))):
                    pq.put((steps+distance,(adj,found)))
                elif iskey(adj):
                    if not(any(map(lambda fnd : found.issubset(fnd), history[adj]))):
                        new_found = found if adj in found else (found | {adj})
                        pq.put((steps+distance,(adj,new_found)))
        s,(c,f) = pq.get()
        return aux(c,f,s)
    return aux("@",set(),0)

def solve(file):
    return collect_keys(make_node_map(read_input(file)))
