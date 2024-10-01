from collections import namedtuple

Command = namedtuple("Command",["direction","unit"])

def read_commands(filename):
    with open(filename) as input:
        for line in input:
            direction, unit = line.strip().split()
            yield Command(direction,int(unit))

def solve(filename):
    commands = read_commands(filename)
    h = 0
    v = 0
    for command in commands:
        if command.direction == "forward":
            h += command.unit
        else:
            if command.direction == "down":
                v += command.unit
            if command.direction == "up":
                v -= command.unit
    return h * v
