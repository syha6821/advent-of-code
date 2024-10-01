from collections import namedtuple

Pos = namedtuple("Pos",["row","col"])
Pos.__add__ = lambda self,other : Pos(self.row+other.row,self.col+other.col)
Instruction = namedtuple("Instruction",["action","value"])
UNIT_POS = {"N":Pos(-1,0),"E":Pos(0,1),"S":Pos(1,0),"W":Pos(0,-1)}

def read_instructions(file):
    with open(file) as input:
        for line in input.read().strip().split("\n"):
            yield Instruction(line[0],int(line[1:]))


def rotate(pos,direction,degree):
    degree = degree % 360
    if degree == 0:
        return pos
    else:
        return rotate(Pos(pos.col,-pos.row),direction,degree + (-90 if direction == "R" else 90))

def sail(instructions):
    pos = Pos(0,0)
    waypoint = Pos(-1,10)
    for inst in instructions:
        if inst.action == "F":
            pos += Pos(waypoint.row * inst.value, waypoint.col * inst.value)
        elif inst.action == "L" or inst.action == "R":
            waypoint = rotate(waypoint,inst.action,inst.value)
        else:
            unit = UNIT_POS[inst.action]
            waypoint += Pos(unit.row * inst.value, unit.col * inst.value)
    return pos

def solve(file):
    return sum(map(abs,sail(list(read_instructions(file)))))
