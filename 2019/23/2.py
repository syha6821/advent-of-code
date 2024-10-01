from intcode2 import execute,make_memory
from copy import deepcopy
from itertools import chain

NAT = 255

def read_program(file):
    with open(file) as input:
        return make_memory(list(map(int,input.read().strip().split(','))))

def make_network(program,n):
    return {i:{"program":deepcopy(program),"ip":0,"queue":iter([i])} for i in range(n)}

def run(network):
    dest = 0
    nat = []
    last_y = -1
    idle = [False]*len(network)
    while True:
        if all(idle) and nat:
            network[0]["queue"] = chain(network[0]["queue"],nat)
            if last_y == nat[1]:
                return last_y
            else:
                last_y = nat[1]
            dest = 0

        nic = network[dest]
        outputs = []
        nic["ip"] = execute(nic["program"],ip = nic["ip"],outputs = outputs, input = nic["queue"],halt_on_output=True)
        d = dest
        if outputs:
            idle[d] = False
            dest = outputs[0]
            outputs = []
            nic["ip"] = execute(nic["program"],ip = nic["ip"],outputs = outputs, input = nic["queue"],halt_on_output=True)
            nic["ip"] = execute(nic["program"],ip = nic["ip"],outputs = outputs, input = nic["queue"],halt_on_output=True)
            x,y = outputs
            if dest == NAT:
                nat = [x,y]
                dest = d + 1
            else:
                network[dest]["queue"] = chain(network[dest]["queue"],[x,y])
        else:
            idle[d] = True
            dest = (dest + 1) % 50

def solve(file):
    return run(make_network(read_program(file),50))
