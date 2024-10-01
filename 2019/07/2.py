import sys
sys.path.insert(0,'..')
import intcode

from copy import deepcopy
from itertools import permutations

def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split(',')))

def amplify(seq,program):
    amps = [deepcopy(program) for _ in range(5)]
    outputs = [[],[],[],[],[]]
    ips = [0] * 5
    while ips[-1] != intcode.FINISH:
        for i in range(5):
            ips[i] = intcode.execute(amps[i],
                                     ip=ips[i],
                                     input=iter([seq[i],(0 if not outputs[i-1] else outputs[i-1][-1])]) if ips[i] == 0 else iter([outputs[i-1][-1]]),
                                     outputs=outputs[i],
                                     halt_on_output=True)
    return outputs[-1][-1]

def solve(file):
    program = read_input(file)
    return max(amplify(seq,program) for seq in permutations([5,6,7,8,9]))
