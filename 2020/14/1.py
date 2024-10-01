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
    for i,b in mask.items():
        bits[i] = b
    return "".join(bits)

def execute(program):
    mem = dict()
    mask = dict()
    for p in program:
        if p[0] == "mask":
            mask = read_mask(p[1])
        else:
            mem[p[1][0]] = masking(p[1][1],mask)
    return list(map(lambda b : int(b,2),mem.values()))

def solve(file):
    return sum(execute(read_input(file)))
