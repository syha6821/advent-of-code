from itertools import accumulate,cycle

def read_input(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split('\n')))

def solve(file):
    nums = read_input(file)
    history = set()
    for n in accumulate(cycle(nums),initial=0):
        if n in history:
            return n
        history.add(n)
