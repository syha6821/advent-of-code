from collections import defaultdict
from itertools import islice

def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split('\n')))

def connect(jolts):
    jolts.append(max(jolts)+3)
    jolts.append(0)
    jolts.sort()
    diff = defaultdict(int)
    for prev,current in zip(islice(jolts,0,len(jolts)-1),islice(jolts,1,len(jolts))):
        diff[current-prev] += 1
    return diff

def solve(file):
    diff = connect(read_input(file))
    return diff[1] * diff[3]
