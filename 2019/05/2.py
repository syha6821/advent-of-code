import sys
sys.path.insert(0,'..')
import intcode
from itertools import repeat

def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split(',')))

def solve(file):
    program = read_input(file)
    return intcode.execute(program,repeat(5))[-1]
