from intcode import execute,make_memory
from functools import reduce
from itertools import product,chain
from collections import namedtuple,Counter
from copy import deepcopy
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
UNIT_POS = {U:Pos(-1,0),R:Pos(0,1),D:Pos(1,0),L:Pos(0,-1)}
DIRECTIONS = {Pos(-1,0):U,Pos(0,1):R,Pos(1,0):D,Pos(0,-1):L}

def read_program(file):
    with open(file) as input:
        return make_memory(list(map(int,input.read().strip().split(','))))

def neg(pos):
    return Pos(-pos.row,-pos.col)

def relative_direction(self,other):
    return DIRECTIONS[neg(self) + other]

def rotation(self,other):
    match self,other:
        case ("^",">") | (">","v") | ("v","<") | ("<","^"):
            return "R"
        case (">","^") | ("v",">") | ("<","v") | ("^","<"):
            return "L"
        case _ :
            return False

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

def make_path(image):
    scaffolds = Counter(image.values())['#']
    vaccum = next(pos for pos,elm in image.items() if elm in {'^','<','>','v'})
    direction = image[vaccum]
    history = set()
    path = []
    while scaffolds != len(history):
        if vaccum + UNIT_POS[direction] in image:
            vaccum += UNIT_POS[direction]
            path[-1] += 1
        else:
            for d in [U,R,L,D]:
                if vaccum + UNIT_POS[d] in image and vaccum + UNIT_POS[d] not in history:
                    vaccum += UNIT_POS[d]
                    path.append(rotation(direction,d))
                    direction = d
                    path.append(1)
                    break
        history.add(vaccum)
    return path

sample = ["R",8,"R",8,"R",4,"R",4,"R",8,"L",6,"L",2,"R",4,"R",4,"R",8,"R",8,"R",8,"L",6,"L",2]

def make_sample(line):
    line = line.split(',')
    return reduce(lambda acc,e : acc + [e if e.isalpha() else int(e)],line,[])

def remove_pattern(string,pattern):
    if string.startswith(pattern):
        string = string.removeprefix(pattern).strip(',')
        return remove_pattern(string,pattern)
    elif string.endswith(pattern):
        string = string.removesuffix(pattern)
        return remove_pattern(string,pattern).strip(',')
    else:
        return string

def remove_patterns(string,patterns):
    for pattern in patterns:
        if string.startswith(pattern):
            string = string.removeprefix(pattern).strip(',')
            return remove_patterns(string,patterns)
        elif string.endswith(pattern):
            string = string.removesuffix(pattern)
            return remove_patterns(string,patterns).strip(',')
    return string


def make_routine(moves):
    moves = reduce(lambda acc,e : acc + "," + str(e) ,moves,"")[1:]
    for a,b,c in product(range(1,21,1),range(1,21,1),range(1,21,1)):
        A = moves[:a]
        mvs = remove_patterns(moves,[A])
        B = mvs[-b:]
        mvs = remove_patterns(mvs,[A,B])
        C = mvs[:c]
        pattern = matching_pattern(moves,A,B,C)
        if pattern:
            yield A,B,C,pattern

def start(line,A,B,C):
    matching = [p for p in [A,B,C] if line.startswith(p)]
    if not matching:
        return False
    return matching[0]

def matching_pattern(line,A,B,C):
    patterns = {A:"A",B:"B",C:"C"}
    pattern = []
    while line:
        if len(pattern) * 2 - 1 > 20:
            return []
        head = start(line,A,B,C)
        if not head:
            return []
        pattern.append(patterns[head])
        line = line.removeprefix(head).strip(',')
    return ",".join(pattern)

def to_ascii(line):
    return list(map(ord,line + "\n"))

def solve(file):
    program = read_program(file)
    A,B,C,routine = next(make_routine(make_path(ascii(deepcopy(program)))))
    program[0] = 2
    outputs = []
    input = chain(*list(map(to_ascii,[routine,A,B,C,"n"])))
    execute(program,input = input,outputs = outputs)
    return outputs[-1]
