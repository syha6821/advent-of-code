def read_input(file):
    with open(file) as input:
        for line in input.read().strip().split('\n'):
            inst, n = line.split()
            yield inst,int(n)

def solve(file):
    program = list(read_input(file))
    visited = set()
    line_num = 0
    accum = 0
    while True:
        if line_num in visited:
            return accum
        visited.add(line_num)
        inst,n = program[line_num]
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


