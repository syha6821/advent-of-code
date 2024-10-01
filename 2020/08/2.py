from math import inf

def read_input(file):
    with open(file) as input:
        for line in input.read().strip().split('\n'):
            inst, n = line.split()
            yield inst,int(n)

def execute_with_change(changed,program):
    visited = set()
    line_num = 0
    accum = 0
    while True:
        if line_num == len(program):
            break
        if line_num in visited:
            return inf
        visited.add(line_num)
        inst,n = program[line_num]
        if line_num == changed:
            inst = "nop" if inst == "jmp" else "nop"
        if inst == "nop":
            line_num += 1
            continue
        elif inst == "acc":
            line_num += 1
            accum += n
            continue
        elif inst == "jmp":
            line_num += n
            continue
    return accum

def solve(file):
    program = list(read_input(file))
    for i,(inst,_) in enumerate(program):
        if inst == "nop" or inst == "jmp":
            result = execute_with_change(i,program)
            if result != inf:
                return result
