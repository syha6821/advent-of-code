from operator import add,mul

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

def solve(file):
    program = read_input(file)
    program[1] = 12
    program[2] = 2
    return execute(program)[0]

