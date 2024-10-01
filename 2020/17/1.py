from itertools import product,repeat
from collections import namedtuple,Counter
from functools import reduce

Cube = namedtuple("Cube",["x","y","z"])
Cube.__add__ = lambda self,other : Cube(self.x+other.x, self.y+other.y, self.z + other.z)
UNIT_CUBE = list(map(lambda t: Cube(*t),product(*repeat([-1,0,1],3))))
UNIT_NEIBORS = list(filter(lambda c : c != Cube(0,0,0),UNIT_CUBE))
ACTIVE = "#"
INACTIVE = "."

def neighbors(cube):
    return list(map(lambda n : cube + n,UNIT_NEIBORS))

def inspect_neighbors(cube,pocket):
    result = Counter()
    for neighbor in neighbors(cube):
        if neighbor not in pocket or pocket[neighbor] == INACTIVE:
            result[INACTIVE] += 1
        else:
            result[ACTIVE] += 1
    return result

def count_actives(pocket):
    return len(list(cube for cube,state in pocket.items() if state == ACTIVE))

def ghosts(pocket):
    return reduce(lambda acc, cube: acc.union(n for n in neighbors(cube) if n not in pocket),(cube for cube,state in pocket.items() if state == ACTIVE),set())

def filled(pocket):
    return pocket | dict(zip(ghosts(pocket),repeat(INACTIVE)))

def cycle(pocket):
    after_cycle = dict()
    for cube,state in pocket.items():
        neighbors_state = inspect_neighbors(cube,pocket)
        if state == ACTIVE:
            if (neighbors_state[ACTIVE] in [2,3]):
                after_cycle[cube] = ACTIVE
            else:
                after_cycle[cube] = INACTIVE
        elif state == INACTIVE:
            if neighbors_state[ACTIVE] == 3:
                after_cycle[cube] = ACTIVE
            else:
                after_cycle[cube] = INACTIVE
    return filled(after_cycle)

def read_pocket(file):
    pocket = dict()
    with open(file) as input:
        for y,line in enumerate(input.read().strip().split('\n')):
            for x,state in enumerate(line):
                pocket[Cube(x,y,0)] = state
    return filled(pocket)

def solve(file):
    return count_actives(reduce(lambda acc,_ : cycle(acc),range(6),read_pocket(file)))
