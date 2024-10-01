from queue import PriorityQueue
from collections import namedtuple
from math import inf

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other: Pos(self.row+other.row, self.col+other.col)
UNIT_POS = {"U":Pos(-1,0),"R":Pos(0,1),"D":Pos(1,0),"L":Pos(0,-1)}

def read_cavern(filepath):
    cavern = dict()
    with open(filepath) as input:
        for row,line in enumerate(input.read().split('\n')):
            for col,level in enumerate(line.strip()):
                cavern[Pos(row,col)] = int(level)
    dest = Pos(max(pos.row for pos in cavern.keys()),max(pos.col for pos in cavern.keys()))
    return cavern,dest

def adjacents(pos):
    return (pos + unit for unit in UNIT_POS.values())

def lowest_risk(cavern,dest):
    current = Pos(0,0)
    known_risk = PriorityQueue()
    risk_sum_map = {pos:inf for pos in cavern}
    risk_sum_map[current] = 0
    while current != dest:
        current_risk = risk_sum_map[current]
        for pos in adjacents(current):
            if pos in cavern:
                risk = risk_sum_map[pos]
                calced_risk = cavern[pos] + current_risk
                if risk > calced_risk:
                    risk_sum_map[pos] = calced_risk
                    known_risk.put(pos,calced_risk)
        current = known_risk.get()
    return risk_sum_map[dest]
                    


