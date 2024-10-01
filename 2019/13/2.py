import sys
sys.path.insert(0,'..')
import intcode

from itertools import batched,chain
from collections import defaultdict
sys.setrecursionlimit(10**9)

EMPTY = 0
WALL = 1
BLOCK = 2
PADDLE = 3
BALL = 4

def read_program(file):
    with open(file) as input:
        return intcode.make_memory(list(map(int,input.read().strip().split(','))))

def compare(x,y):
    return (x > y) - (x < y)

def solve(file):
    program = read_program(file)
    program[0] = 2
    ip = 0
    input = iter([])
    PADDLE_X = 0
    BALL_X = 0
    outputs = []
    while True:
        ip = intcode.execute(program,ip = ip,input=input,outputs=outputs,halt_on_output=True)
        if len(outputs) == 3:
            x,y,id = outputs
            outputs = []
            if (x,y) == (-1,0):
                print(id)
            elif id == PADDLE:
                PADDLE_X = x
            elif id == BALL:
                BALL_X = x
                move = compare(BALL_X,PADDLE_X)
                input = chain(input,[move])
