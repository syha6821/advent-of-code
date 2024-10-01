from collections import deque
from functools import reduce
from math import prod

def read_player(lines):
    return deque([int(line) for line in lines[1:]])

def read_input(file):
    with open(file) as input:
        p1,p2 = input.read().strip().split("\n\n")
        return read_player(p1.split('\n')),read_player(p2.split('\n'))

def do_game(p1,p2):
    while p1 and p2:
        p1_top = p1.popleft()
        p2_top = p2.popleft()
        winner = p1 if p1_top > p2_top else p2
        for card in reversed(sorted([p1_top,p2_top])):
            winner.append(card)
    return p1 if not p2 else p2

def solve(file):
    p1,p2 = read_input(file)
    winner = do_game(p1,p2)
    return reduce(lambda acc, t: acc + prod(t),zip(winner,range(len(winner),0,-1)),0)


