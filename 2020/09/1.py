from collections import deque
from itertools import combinations

LENGTH = 25

def read_nums(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split('\n')))

def solve(file):
    nums = read_nums(file)
    preamble = deque()
    for num in nums:
        if len(preamble) < LENGTH:
            preamble.append(num)
            continue
        if num not in map(sum,combinations(preamble,2)):
            return num
        if len(preamble) == LENGTH:
            preamble.popleft()
        preamble.append(num)
