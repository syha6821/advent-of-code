import sys
sys.path.insert(0,'..')
import intcode

def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split(',')))

def solve(file):
    program = read_input(file)
    _,outputs = intcode.execute(program,1)
    return outputs[-1]
