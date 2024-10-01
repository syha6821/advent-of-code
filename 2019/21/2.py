from intcode import execute,make_memory
from itertools import chain
from sys import setrecursionlimit

setrecursionlimit(10**9)

def read_droid(file):
    with open(file) as input:
        return make_memory(list(map(int,input.read().strip().split(','))))

def encode(code):
    return list(map(ord,chain(code,"\n")))

def decode(code):
    return "".join(list(map(chr,code)))

def report(droid,program):
    outputs = []
    execute(droid,input = iter(program),outputs = outputs)
    return outputs

def solve(file):
    codes = ["NOT B T","NOT C J","OR T J","AND D J","AND H J","NOT A T","OR T J","RUN"]
    program = list(chain(*list(map(encode,codes))))
    output = report(read_droid(file),program)
    return output[-1]
