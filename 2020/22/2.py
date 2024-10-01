from collections import deque,namedtuple
from functools import reduce
from math import prod
import sys
sys.setrecursionlimit(10000)

Player = namedtuple("Player",["num","deque"])

def read_player(lines):
    return Player(int(lines[0][7]),deque([int(line) for line in lines[1:]]))

def read_input(file):
    with open(file) as input:
        p1,p2 = input.read().strip().split("\n\n")
        return read_player(p1.split('\n')),read_player(p2.split('\n'))

def recursive_combat(p1,p2):
    def aux(p1,p2,p1_history,p2_history):
        if not p1.deque:
            return p2
        if not p2.deque:
            return p1
        if tuple(p1.deque) in p1_history and tuple(p2.deque) in p2_history:
            return p1
        else:
            p1_history.add(tuple(p1.deque))
            p2_history.add(tuple(p2.deque))
            pick1 = p1.deque.popleft()
            pick2 = p2.deque.popleft()
            if (len(p1.deque) >= pick1) and (len(p2.deque) >= pick2):
                sub_game_winner = aux(Player(1,deque(list(p1.deque)[:pick1])),Player(2,deque(list(p2.deque)[:pick2])),set(),set())
                if sub_game_winner.num == 1:
                    p1.deque.append(pick1)
                    p1.deque.append(pick2)
                if sub_game_winner.num == 2:
                    p2.deque.append(pick2)
                    p2.deque.append(pick1)
                return aux(p1,p2,p1_history,p2_history)
            else:
                winner = p1 if pick1 > pick2 else p2
                winner.deque.append(max(pick1,pick2))
                winner.deque.append(min(pick1,pick2))
                return aux(p1,p2,p1_history,p2_history)
    return aux(p1,p2,set(),set())

def score(player):
    return reduce(lambda acc, t: acc + prod(t),zip(player.deque,range(len(player.deque),0,-1)),0)

def solve(file):
    p1,p2 = read_input(file)
    return score(recursive_combat(p1,p2))
