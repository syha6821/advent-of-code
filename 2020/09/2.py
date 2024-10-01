from collections import deque
from itertools import combinations,islice

LENGTH = 25

def read_nums(file):
    with open(file) as input:
        return list(map(int,input.read().strip().split('\n')))

def find_num(nums):
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

def solve(file):
    nums = read_nums(file)
    invalid = find_num(nums)
    for length in range(2,len(nums)+1):
        for a,b in zip(range(0,len(nums)),range(length,len(nums))):
            s = list(islice(nums,a,b))
            if sum(s) == invalid:
                return min(s) + max(s)
