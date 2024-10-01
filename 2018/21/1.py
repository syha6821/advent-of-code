def parse_line(line):
    op,A,B,C = line.split()
    return [op,int(A),int(B),int(C)]

def read_input(file):
    with open(file) as input:
        ip = int(input.readline().split()[1])
        return ip,[parse_line(line) for line in input.readlines()]

def snapshot(register):
    return tuple(register)

def operate(r,instructions,IP):
    registers = [r,0,0,0,0,0]
    ip = registers[IP]
    history = set()
    prev = -1
    while True:
        image = snapshot(registers[:-1])
        opcode,A,B,C = instructions[ip]
        if ip == 28:
            # print(registers[3])
            if registers[3] in history:
                return prev
            history.add(registers[3])
            prev = registers[3]
        match opcode:
            case "addr":
                registers[C] = registers[A] + registers[B]
            case "addi":
                registers[C] = registers[A] + B
            case "mulr":
                registers[C] = registers[A] * registers[B]
            case "muli":
                registers[C] = registers[A] * B
            case "banr":
                registers[C] = registers[A] & registers[B]
            case "bani":
                registers[C] = registers[A] & B
            case "borr":
                registers[C] = registers[A] | registers[B]
            case "bori":
                registers[C] = registers[A] | B
            case "setr":
                registers[C] = registers[A]
            case "seti":
                registers[C] = A
            case "gtir":
                registers[C] = int(A > registers[B])
            case "gtri":
                registers[C] = int(registers[A] > B)
            case "gtrr":
                registers[C] = int(registers[A] > registers[B])
            case "eqir":
                registers[C] = int(A == registers[B])
            case "eqri":
                registers[C] = int(registers[A] == B)
            case "eqrr":
                registers[C] = int(registers[A] == registers[B])
        if not registers[IP] + 1 < len(instructions):
            break
        registers[IP] += 1
        ip = registers[IP]

    return registers

def solve(file):
    IP,instructions = read_input(file)
    n = 0
    return operate(1,instructions,IP)
