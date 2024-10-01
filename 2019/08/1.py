from itertools import batched
from collections import Counter

def read_input(file):
    with open(file) as input:
        return input.read().strip()

def solve(file):
    data = read_input(file)
    width = 25
    height = 6
    layers = list(batched(data,width*height))
    fewest = min(layers,key=lambda layer: Counter(layer)['0'])
    cnt = Counter(fewest)
    return cnt['1'] * cnt['2']
