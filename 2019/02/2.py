from operator import add,mul
from copy import deepcopy
from itertools import product

ADD = 1
MUL = 2
QUIT = 99

operators = {ADD:add,MUL:mul}

def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split(',')))

def execute(program):
    def aux(pos):
        opt = program[pos]
        if opt == QUIT:
            return program
        else:
            op = operators[opt]
            program[program[pos+3]] = op(program[program[pos+1]],program[program[pos+2]])
            return aux(pos+4)
    return aux(0)

def program_of(program,noun,verb):
    program = deepcopy(program)
    program[1] = noun
    program[2] = verb
    return program

def find_pair(num,program):
    for noun,verb in product(range(0,100),range(0,100)):
        if num == execute(program_of(program,noun,verb))[0]:
            return noun,verb

def solve(file):
    program = read_input(file)
    noun,verb = find_pair(19690720,program)
    return 100 * noun + verb
