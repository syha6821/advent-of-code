from math import floor

def read_input(file):
    with open(file) as input:
        return [int(n) for n in input.read().strip().split('\n')]

def fuel(n):
    return floor(n / 3) - 2

def solve(file):
    nums = read_input(file)
    return sum(map(fuel,nums))
