def read_input(filepath):
    with open(filepath) as input:
        return tuple(map(lambda line: int(line.strip().split(':')[1].strip()),input.read().strip().split('\n')))

def roll(turn):
    return ((turn-1)*3 + 1)*3 + 3

def next_location(location,dice):
    return (((location - 1) + dice) % 10) + 1

def game(p1,p2):
    point1 = 0
    point2 = 0
    turn = 1
    while point1 < 1000 and point2 < 1000:
        point = roll(turn)
        if turn % 2 == 1:
            p1 = next_location(p1,point)
            point1 += p1
        if turn % 2 == 0:
            p2 = next_location(p2,point)
            point2 += p2
        turn += 1
    return ((turn-1)*3) * (point1 if point1 < 1000 else point2)

def solve(filepath):
    return game(*read_input(filepath))
