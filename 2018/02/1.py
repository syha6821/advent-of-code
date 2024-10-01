from collections import defaultdict,Counter
from math import prod

def read_input(file):
    with open(file) as input:
        return input.read().strip().split('\n')

def checksum(ids):
    freq = defaultdict(int)
    for id in ids:
        for fr in set(Counter(id).values()):
            if fr > 1:
                freq[fr] += 1
    return prod(freq.values())

def solve(file):
    return checksum(read_input(file))
