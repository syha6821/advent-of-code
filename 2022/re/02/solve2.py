ENCRYTED = {"A":"R",
            "B":"P",
            "C":"S",
            "X":"L",
            "Y":"D",
            "Z":"W"}

POINT = {"R":1,"P":2,"S":3,"L":0,"D":3,"W":6}
CHOICE = {"R":0,"P":1,"S":2}
RCHOICE = {-1:"S",0:"R",1:"P",2:"S",3:"R"}

def read_strategy(filepath):
    with open(filepath) as input:
        for line in input.readlines():
            yield line.split()

def game(op,result):
    DIFF = {"W":1,"D":0,"L":-1}
    return RCHOICE[CHOICE[op]+DIFF[result]]

def point(op,result):
    return POINT[result] + POINT[game(op,result)]

def solve(filepath):
    return sum(point(ENCRYTED[round[0]],ENCRYTED[round[1]]) for round in read_strategy(filepath))
