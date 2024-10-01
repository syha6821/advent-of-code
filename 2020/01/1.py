from itertools import combinations
from math import prod

SUM = 2020

def read_input(filepath):
    with open(filepath) as input:
        return [int(line) for line in input.readlines()]

def find_comb(nums):
    for comb in combinations(nums,2):
        if sum(comb) == SUM:
            return comb
    return (0,0)

def solve(filepath):
    return prod(find_comb(read_input(filepath)))
