from collections import defaultdict

CYCLE = 6
NEWBORN_CYCLE = 8

def read_fishes(filepath):
    with open(filepath) as input:
        fishes = defaultdict(int)
        for count in tuple(map(int,input.read().strip().split(','))):
            fishes[count] += 1
        return fishes

def after_n_days(n,fishes):
    # print(fishes)
    if n == 0:
        return sum(fishes.values())
    else:
        next_fishes = defaultdict(int)
        for left, count in fishes.items():
            if left == 0:
                next_fishes[CYCLE] += count
                next_fishes[NEWBORN_CYCLE] += count 
            else:
                next_fishes[left-1] += count
        return after_n_days(n-1,next_fishes)

