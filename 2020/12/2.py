from collections import namedtuple

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row,self.col+other.col)
Instruction = namedtuple("Instruction",["action","value"])
UNIT_POS = {"N":Pos(-1,0),"E":Pos(0,1),"S":Pos(1,0),"W":Pos(0,-1)}

def read_instructions(file):
    with open(file) as input:
        for line in input.read().strip().split("\n"):
            yield Instruction(line[0],int(line[1:]))

def move(pos,instruction):
    p = UNIT_POS[instruction.action]
    return pos + Pos(p.row * instruction.value, p.col * instruction.value)

def sail(instructions):
    head = 1
    waypoint = Pos(-1,19)
    directions = list(UNIT_POS.keys())
    pos = Pos(0,0)

    for inst in instructions:
        action = inst.action
        if action == "L":
            head = (head - inst.value // 90) % len(directions)
            action = directions[head]
            continue
        if action == "R":
            head = (head + inst.value // 90) % len(directions)
            action = directions[head]
            continue
        if action == "F":
            action = directions[head]
        pos = move(pos,Instruction(action,inst.value))
    return pos

def solve(file):
    return sum(map(abs,sail(read_instructions(file))))
