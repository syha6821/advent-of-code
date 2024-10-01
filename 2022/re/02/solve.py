ENCRYTED = {"A":"R",
            "B":"P",
            "C":"S",
            "X":"R",
            "Y":"P",
            "Z":"S"}

POINT = {"R":1,"P":2,"S":3,"L":0,"D":3,"W":6}
CHOICE = {"R":0,"P":1,"S":2}

def read_strategy(filepath):
    with open(filepath) as input:
        for line in input.readlines():
            yield line.split()

def game(op,me):
    op = ENCRYTED[op]
    me = ENCRYTED[me]
    if op == me:
        return "D"
    op = CHOICE[op]
    me = CHOICE[me]
    diff = abs(op - me)
    if diff == 1:
        if op < me:
            return "W"
        if op > me:
            return "L"
    if diff == 2:
        if op < me:
            return "L"
        if op > me:
            return "W"
    return "D"

def point(op,me):
    return POINT[ENCRYTED[me]] + POINT[game(op,me)]

def solve(filepath):
    return sum(point(*round) for round in read_strategy(filepath))
