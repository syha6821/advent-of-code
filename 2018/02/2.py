from itertools import combinations

def read_input(file):
    with open(file) as input:
        return input.read().strip().split('\n')

def is_correct(id1,id2):
    diff = 0
    for a,b in zip(id1,id2):
        if a != b:
            diff += 1
        if diff > 1:
            return False
    return True

def find_correct(ids):
    return next(filter(lambda i : is_correct(*i),combinations(ids,2)))

def find_diff(id1,id2):
    for i,(c1,c2) in enumerate(zip(id1,id2)):
        if c1 != c2:
            return i

def solve(file):
    ids = find_correct(read_input(file))
    id1,id2 = find_correct(ids)
    diff = find_diff(id1,id2)
    return id1[:diff] + id1[diff+1:]
