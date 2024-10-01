from intcode import execute,make_memory
from collections import Counter
from itertools import product
from copy import deepcopy

def read_input(file):
    with open(file) as input:
        return make_memory(list(map(int,input.read().strip().split(','))))

def scan(program,width,height):
    outputs = []
    for x,y in product(range(0,width),range(0,height)):
        execute(deepcopy(program),ip = 0,input = iter([x,y]),outputs = outputs,halt_on_output=True)
    return outputs

def solve(file):
    program = read_input(file)
    result = scan(program,50,50)
    return Counter(result)[1]
