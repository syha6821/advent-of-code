import sys
sys.path.insert(0,'..')
import intcode

sys.setrecursionlimit(10**9)

def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split(',')))

def solve(file):
    program = intcode.make_memory(read_input(file))
    outputs = []
    intcode.execute(program,input=iter([2]),outputs=outputs)
    return outputs
