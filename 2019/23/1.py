from intcode2 import execute,make_memory
from copy import deepcopy
from itertools import chain

def read_program(file):
    with open(file) as input:
        return make_memory(list(map(int,input.read().strip().split(','))))

def make_network(program,n):
    return {i:{"program":deepcopy(program),"ip":0,"queue":iter([i])} for i in range(n)}

def run(network):
    dest = 0
    while True:
        nic = network[dest]
        outputs = []
        nic["ip"] = execute(nic["program"],ip = nic["ip"],outputs = outputs, input = nic["queue"],halt_on_output=True)
        if outputs:
            dest = outputs[-1]
            outputs = []
            nic["ip"] = execute(nic["program"],ip = nic["ip"],outputs = outputs, input = nic["queue"],halt_on_output=True)
            nic["ip"] = execute(nic["program"],ip = nic["ip"],outputs = outputs, input = nic["queue"],halt_on_output=True)
            x,y = outputs
            if dest == 255:
                return y
            network[dest]["queue"] = chain(network[dest]["queue"],[x,y])
        else:
            dest = (dest + 1) % 50

def solve(file):
    return run(make_network(read_program(file),50))
