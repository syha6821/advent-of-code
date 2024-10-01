from collections import defaultdict,Counter,namedtuple
from itertools import product

Universe = namedtuple("Universe",["player_1","player_2"])
Player = namedtuple("Player",["pos","score"])

WIN_SCORE = 21
DICE = Counter(sum(d) for d in product(*[(1,2,3)]*3))

def read_input(filepath):
    with open(filepath) as input:
        return tuple(map(lambda line: int(line.strip().split(':')[1].strip()),input.read().strip().split('\n')))

def next_position(position,dice):
    return (((position - 1) + dice) % 10) + 1

def next_player(player,dice):
    next_pos = next_position(player.pos,dice)
    return Player(next_pos,player.score + next_pos)

def game(p1,p2):
    universes = {Universe(Player(p1,0),Player(p2,0)) : 1}
    def g(universes):
        win1,win2 = 0,0
        if not universes:
            return win1,win2
        else:
            next_universes = defaultdict(int)
            for (player_1,player_2),count in universes.items():
                for dv_1,dc_1 in DICE.items():
                    p1 = next_player(player_1,dv_1)
                    if p1.score >= WIN_SCORE:
                        win1 += count * dc_1
                        continue
                    for dv_2,dc_2 in DICE.items():
                        p2 = next_player(player_2,dv_2)
                        if p2.score >= WIN_SCORE:
                            win2 += count * dc_1 * dc_2
                            continue
                        next_universes[Universe(p1,p2)] += count * dc_1 * dc_2
            future = g(next_universes)
            return win1+future[0],win2+future[1]
    return g(universes)

def solve(filepath):
    return max(game(*read_input(filepath)))
