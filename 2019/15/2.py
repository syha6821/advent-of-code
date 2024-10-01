from intcode import execute,make_memory
from collections import namedtuple
import sys
from copy import deepcopy
sys.setrecursionlimit(10**9)

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row + other.row, self.col + other.col)
NORTH = 1
SOUTH = 2
WEST = 3
EAST = 4
DIRECTIONS = [NORTH,SOUTH,WEST,EAST]
UNIT_POS = {NORTH:Pos(-1,0),SOUTH:Pos(1,0),WEST:Pos(0,-1),EAST:Pos(0,1)}

WALL = 0
MOVED = 1
DESTINATION = 2

def read_program(file):
    with open(file) as input:
        return make_memory(list(map(int,input.read().strip().split(','))))

def make_map(program):
    m = dict()
    m[Pos(0,0)] = MOVED
    def aux(ips):
        outputs = []
        next_ips = []
        for ip,pos,prog in ips:
            for direction in DIRECTIONS:
                next_pos = pos + UNIT_POS[direction]
                next_prog = deepcopy(prog)
                if next_pos not in m:
                    next_ips.append((execute(next_prog,ip,input=iter([direction]),outputs=outputs,halt_on_output=True),next_pos,next_prog))
                    m[next_pos] = outputs[-1]
        if not next_ips:
            return m
        return aux([ip for ip,state in zip(next_ips,outputs) if state != WALL])
    return aux([(0,Pos(0,0),deepcopy(program))])

def draw_map(m):
    min_height = min(map(lambda p: p.row,m))
    max_height = max(map(lambda p: p.row,m))
    min_width = min(map(lambda p: p.col,m))
    max_width = max(map(lambda p: p.col,m))
    for row in range(min_height,max_height+1):
        for col in range(min_width,max_width+1):
            if Pos(row,col) not in m:
                print(".",end="")
                continue
            val = m[Pos(row,col)]
            print("." if val == MOVED else "#" if val == WALL else "O" if val == DESTINATION else "X",end="")
        print()

def fill(m):
    start = next(pos for pos,state in m.items() if state == DESTINATION)
    edges = [start]
    filled = set()
    step = 0
    while edges:
        step += 1
        next_edges = []
        for edge in edges:
            for direction in DIRECTIONS:
                next_edge = edge + UNIT_POS[direction]
                if m[next_edge] != WALL and next_edge not in filled:
                    next_edges.append(next_edge)
                    filled.add(next_edge)
        edges = next_edges
    return step - 1

def solve(file):
    return fill(make_map(read_program(file)))
