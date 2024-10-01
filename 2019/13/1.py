import sys
sys.path.insert(0,'..')
import intcode

from itertools import batched
from collections import Counter
sys.setrecursionlimit(10**9)

EMPTY = 0
WALL = 1
BLOCK = 2
PADDLE = 3
BALL = 4

def read_program(file):
    with open(file) as input:
        return intcode.make_memory(list(map(int,input.read().strip().split(','))))

def solve(file):
    program = read_program(file)
    outputs = []
    intcode.execute(program,outputs=outputs)
    screen = list(map(lambda l : l[2],batched(outputs,3)))
    return Counter(screen)[BLOCK]
