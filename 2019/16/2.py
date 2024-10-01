from itertools import accumulate
from functools import reduce
from operator import sub

def to_digits(string):
    return list(map(int,string))

def read_input(file):
    with open(file) as input:
        return to_digits(input.read().strip())

def phase(nums):
    sum_ = sum(nums)
    return list(map(lambda n : abs(n) % 10, accumulate(nums,sub,initial=sum_)))[:-1]

def final(signal):
    signal = signal * 10000
    offset = int("".join(map(str,signal[:7])))
    half = signal[offset:]
    return int("".join(map(str,reduce(lambda acc,_ : phase(acc),range(100),half)[:8])))

def solve(file):
    return final(read_input(file))
