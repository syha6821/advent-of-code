import sys
sys.path.insert(0,'..')
import intcode

from functools import reduce
from copy import deepcopy
from itertools import repeat,permutations

def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split(',')))

def amp(seq,program):
    return reduce(lambda acc,setting: intcode.execute(deepcopy(program),iter([setting,acc]))[-1],seq,0)

def solve(file):
    program = read_input(file)
    return max(amp(seq,program) for seq in permutations([0,1,2,3,4]))
