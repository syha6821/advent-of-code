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

def shortest_path(program):
    history = set()
    history.add(Pos(0,0))
    def aux(ips):
        outputs = []
        next_ips = []
        for ip,pos,prog in ips:
            for direction in DIRECTIONS:
                next_pos = pos + UNIT_POS[direction]
                next_prog = deepcopy(prog)
                if next_pos not in history:
                    history.add(next_pos)
                    next_ips.append((execute(next_prog,ip,input=iter([direction]),outputs=outputs,halt_on_output=True),next_pos,next_prog))
        if DESTINATION in outputs:
            return 1
        return 1 + aux([ip for ip,state in zip(next_ips,outputs) if state != WALL])
    return aux([(0,Pos(0,0),deepcopy(program))])
