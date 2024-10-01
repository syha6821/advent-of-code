from collections import Counter

def read_line(line):
    before,after = line.strip().split(":")
    nums, char = before.split()
    first,second = nums.split('-')
    password = after[1:]
    return int(first),int(second),char,password

def read_input(filepath):
    with open(filepath) as input:
        return [read_line(line) for line in input.readlines()]

def is_valid(least,most,char,password):
    freq = Counter(password)[char]
    return freq >= least and freq <= most

def solve(filepath):
    count = 0
    for info in read_input(filepath):
        count += is_valid(*info)
    return count
