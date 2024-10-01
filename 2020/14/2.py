from copy import deepcopy

def read_input(file):
    program = []
    with open(file) as input:
        for line in input.read().strip().split('\n'):
            if line.startswith("mask"):
                program.append(("mask",line[7:]))
            else:
                mem,val = list(map(lambda e :e.strip(),line.split("=")))
                mem = mem[4:]
                mem = mem[:-1]
                program.append(("mem",(int(mem),int(val))))
    return program

def read_mask(mask):
    return dict(filter(lambda m : m[1] != 'X',zip(range(len(mask)),mask)))

def masking(val,mask):
    bits = list(bin(val)[2:].zfill(36))
    for i,b in enumerate(mask):
        if b != '0':
            bits[i] = b
    return "".join(bits)

def decode(bits):
    length = len(bits)
    result = []
    def aux(index,bits):
        if index == length:
            result.append("".join(bits))
        else:
            if bits[index] == 'X':
                one = deepcopy(bits)
                zero = deepcopy(bits)
                one[index] = '1'
                zero[index] = '0'
                aux(index+1,one)
                aux(index+1,zero)
            else:
                aux(index+1,bits)
    aux(0,list(bits))
    return list(map(lambda b: int(b,2),result))

def execute(program):
    mem = dict()
    mask = dict()
    for p in program:
        if p[0] == "mask":
            mask = p[1]
        else:
            for addr in decode(masking(p[1][0],mask)):
                mem[addr] = p[1][1]
    return mem

def solve(file):
    return execute(read_input(file))
