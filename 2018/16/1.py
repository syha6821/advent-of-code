from copy import deepcopy

def addr(instruction,register):
    opcode,A,B,C = instruction
    register[C] = register[A] + register[B]

def addi(instruction,register):
    opcode,A,B,C = instruction
    register[C] = register[A] + B

def mulr(instruction,register):
    opcode,A,B,C = instruction
    register[C] = register[A] * register[B]

def muli(instruction,register):
    opcode,A,B,C = instruction
    register[C] = register[A] * B

def banr(instruction,register):
    opcode,A,B,C = instruction
    register[C] = register[A] & register[B]

def bani(instruction,register):
    opcode,A,B,C = instruction
    register[C] = register[A] & B

def borr(instruction,register):
    opcode,A,B,C = instruction
    register[C] = register[A] | register[B]

def bori(instruction,register):
    opcode,A,B,C = instruction
    register[C] = register[A] | B

def setr(instruction,register):
    opcode,A,B,C = instruction
    register[C] = register[A]

def seti(instruction,register):
    opcode,A,B,C = instruction
    register[C] = A

def gtir(instruction,register):
    opcode,A,B,C = instruction
    register[C] = int(A > register[B])

def gtri(instruction,register):
    opcode,A,B,C = instruction
    register[C] = int(register[A] > B)

def gtrr(instruction,register):
    opcode,A,B,C = instruction
    register[C] = int(register[A] > register[B])

def eqir(instruction,register):
    opcode,A,B,C = instruction
    register[C] = int(A == register[B])

def eqri(instruction,register):
    opcode,A,B,C = instruction
    register[C] = int(register[A] == B)

def eqrr(instruction,register):
    opcode,A,B,C = instruction
    register[C] = int(register[A] == register[B])

def read_input(file):
    samples = []
    with open(file) as input:
        while True:
            before = input.readline()
            if before.isspace():
                break
            before = eval(before.split(":")[1])
            instruction = list(map(int,input.readline().split()))
            after = eval(input.readline().split(":")[1])
            input.readline()
            samples.append([before,instruction,after])
    return samples

def solve(file):
    INSTRUCTIONS = [addr,addi,mulr,muli,banr,bani,borr,bori,setr,seti,gtir,gtri,gtrr,eqir,eqri,eqrr]
    samples = read_input(file)
    result = [0] * len(samples)
    for i,sample in enumerate(samples):
        before,instruction,after = sample
        for ins in INSTRUCTIONS:
            registers = deepcopy(before)
            ins(instruction,registers)
            if after == registers:
                result[i] += 1
    return len([r for r in result if r >= 3])
