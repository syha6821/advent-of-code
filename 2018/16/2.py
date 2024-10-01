from copy import deepcopy
from collections import defaultdict,deque

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
    insts = []
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

        input.readline()

        for line in input.readlines():
            insts.append(list(map(int,line.split())))

    return samples,insts

def solve(file):
    INSTRUCTIONS = [addr,addi,mulr,muli,banr,bani,borr,bori,setr,seti,gtir,gtri,gtrr,eqir,eqri,eqrr]
    samples,insts = read_input(file)
    guess = defaultdict(set)
    opcodes = dict()

    for sample in samples:
        before,instruction,after = sample
        for ins in INSTRUCTIONS:
            registers = deepcopy(before)
            ins(instruction,registers)
            if after == registers:
                guess[instruction[0]].add(ins)

    known = deque([])

    for num,poss in guess.items():
        if len(poss) == 1:
            known.append((num,next(iter(poss))))

    while len(opcodes) < 16:
        for _ in range(len(known)):
            n,opcode = known.popleft()
            opcodes[n] = opcode
            for num,poss in guess.items():
                poss.discard(opcode)
                if len(poss) == 1:
                    known.append((num,next(iter(poss))))

    register = [0,0,0,0]
    for inst in insts:
        opcodes[inst[0]](inst,register)

    return register[0]
