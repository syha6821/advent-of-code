from itertools import repeat,chain,cycle,islice
from functools import reduce

def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip()))

def repeat_n(pattern,n):
    return reduce(lambda acc,num: chain(acc,repeat(num,n)) ,pattern,[])

def apply_pattern(signal,n,pattern):
    pattern = cycle(repeat_n(pattern,n))
    next(pattern)
    return abs(sum(s * p for s,p in zip(signal,pattern))) % 10

def phase(signal,pattern):
    return list(map(lambda n : apply_pattern(signal,n+1,pattern),range(len(signal))))

def solve(file):
    signal = read_input(file)
    pattern = [0,1,0,-1]
    return "".join(map(str,reduce(lambda acc,_ : phase(acc,pattern),range(100),signal)[:8]))
