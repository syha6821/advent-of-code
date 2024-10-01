from intcode import execute,make_memory
from functools import reduce
from collections import namedtuple,Counter
from math import prod
import sys
sys.setrecursionlimit(10**9)

NEWLINE = 10
SCAFFOLD = 35
EMPTY = 46

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row,self.col+other.col)
U = '^'
R = '>'
D = 'v'
L = '<'
UNIT_POS = {U:Pos(0,-1),R:Pos(1,0),D:Pos(0,1),L:Pos(-1,0)}
DIRECTIONS = {Pos(0,-1):U,Pos(1,0):R,Pos(0,1):D,Pos(-1,0):L}

def read_program(file):
    with open(file) as input:
        return make_memory(list(map(int,input.read().strip().split(','))))

def neg(pos):
    return Pos(-pos.row,-pos.col)

def relative_direction(self,other):
    return DIRECTIONS[neg(self) + other]

def ascii(program):
    outputs = []
    execute(program,outputs=outputs)
    lines = reduce(lambda acc, n : acc + chr(n),outputs,"").split('\n')
    image = dict()
    for row,line in enumerate(lines):
        for col,elm in enumerate(line):
            if elm != ".":
                image[Pos(row,col)] = elm
    return image

def intersections(image):
    scaffolds = Counter(image.values())['#']
    vaccum = next(pos for pos,elm in image.items() if elm in {'^','<','>','v'})
    direction = image[vaccum]
    history = set()
    inters = set()
    while scaffolds != len(history):
        if vaccum + UNIT_POS[direction] in image:
            vaccum += UNIT_POS[direction]
        else:
            for d in [U,R,L,D]:
                if vaccum + UNIT_POS[d] in image and vaccum + UNIT_POS[d] not in history:
                    vaccum += UNIT_POS[d]
                    direction = d
                    break
        if vaccum in history:
            inters.add(vaccum)
        history.add(vaccum)
    return inters

def solve(file):
    program = read_program(file)
    image = ascii(program)
    inters = intersections(image)
    return sum(prod(inter) for inter in inters)
